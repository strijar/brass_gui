/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "util.h"
#include "radio.h"
#include "dsp.h"
#include "main_screen.h"
#include "waterfall.h"
#include "hkey.h"
#include "params.h"
#include "tx_info.h"
#include "meter.h"
#include "events.h"
#include "clock.h"
#include "info.h"
#include "dialog_swrscan.h"
#include "voice.h"
#include "fpga/control.h"
#include "msg.h"
#include "msgs.h"
#include "settings/modes.h"

#define FLOW_RESTART_TIMOUT     300

static lv_obj_t                 *main_obj;

static radio_state_t            state = RADIO_RX;

bool radio_tick() {
/*
    if (x6100_flow_read(pack)) {
        prev_time = now_time;

        static uint8_t delay = 0;

        if (delay++ > 10) {
            delay = 0;
            clock_update_power(pack->vext * 0.1f, pack->vbat*0.1f, pack->batcap);
        }

        dsp_samples(pack->samples, RADIO_SAMPLES);

        switch (state) {
            case RADIO_RX:
                if (pack->flag.tx) {
                    state = RADIO_TX;
                    event_send(main_obj, EVENT_RADIO_TX, NULL);
                }
                break;

            case RADIO_TX:
                if (!pack->flag.tx) {
                    state = RADIO_RX;
                    event_send(main_obj, EVENT_RADIO_RX, NULL);
                } else {
                    tx_info_update(pack->tx_power * 0.1f, pack->vswr * 0.1f, pack->alc_level * 0.1f);
                }
                break;

            case RADIO_ATU_START:
                radio_lock();
                x6100_control_atu_tune(true);
                radio_unlock();
                state = RADIO_ATU_WAIT;
                break;
                
            case RADIO_ATU_WAIT:
                if (pack->flag.tx) {
                    event_send(main_obj, EVENT_RADIO_TX, NULL);
                    state = RADIO_ATU_RUN;
                }
                break;
                
            case RADIO_ATU_RUN:
                if (!pack->flag.tx) {
                    params_atu_save(pack->atu_params);
                    radio_lock();
                    x6100_control_atu_tune(false);
                    radio_unlock();
                    event_send(main_obj, EVENT_RADIO_RX, NULL);
                    
                    if (params.atu) {
                        radio_lock();
                        x6100_control_cmd(x6100_atu_network, pack->atu_params);
                        radio_unlock();
                        params.atu_loaded = true;
                        event_send(main_obj, EVENT_ATU_UPDATE, NULL);
                    }
                    state = RADIO_RX;
                } else {
                    tx_info_update(pack->tx_power * 0.1f, pack->vswr * 0.1f, pack->alc_level * 0.1f);
                }
                break;

            case RADIO_SWRSCAN:
                dialog_swrscan_update(pack->vswr * 0.1f);
                break;
                
            case RADIO_POWEROFF:
                x6100_control_poweroff();
                state = RADIO_OFF;
                break;
                
            case RADIO_OFF:
                break;
        }
        
        hkey_put(pack->hkey);
    } else {
        if (d > FLOW_RESTART_TIMOUT) {
            LV_LOG_WARN("Flow reset");
            prev_time = now_time;
            x6100_flow_restart();
            dsp_reset();
        }
        return true;
    }
    */
    return false;
}

void radio_freq_update() {
    uint64_t shift;
    uint64_t freq = op_work->rx;

    radio_check_freq(freq, &shift);
    control_set_rx_freq(freq - shift);
    control_set_tx_freq(op_work->tx - shift);
    control_set_fft_freq(op_work->fft - shift);
}

static void radio_msg_cb(void *s, lv_msg_t *m) {
    switch (lv_msg_get_id(m)) {
        case MSG_PTT: {
            const int *on = lv_msg_get_payload(m);

            if (*on) {
                if (band_settings && band_settings->tx) {
                    state = RADIO_TX;
                    lv_msg_send(MSG_TX, NULL);
                } else {
                    msg_set_text_fmt("TX not permitted");
                }
            } else {
                state = RADIO_RX;
                lv_msg_send(MSG_RX, NULL);
            }
        } break;

        default:
            break;
    }
}

void radio_init(lv_obj_t *obj) {
    main_obj = obj;

    control_init();
    dsp_set_spectrum_factor(op_mode->spectrum_factor);
    settings_mode_update(op_work->mode);

    radio_freq_update();
    radio_load_atu();

    lv_msg_subsribe(MSG_PTT, radio_msg_cb, NULL);
}

radio_state_t radio_get_state() {
    return state;
}

void radio_set_freq_rx(uint64_t freq) {
    uint64_t shift = 0;

    if (!radio_check_freq(freq, &shift)) {
        LV_LOG_ERROR("Freq %llu incorrect", freq);
        return;
    }

    op_work->rx = freq;
    op_work->shift = (shift != 0);

    control_set_rx_freq(freq - shift);
    radio_load_atu();

    lv_msg_send(MSG_FREQ_RX_CHANGED, &op_work->rx);
}

void radio_set_freq_tx(uint64_t freq) {
    uint64_t shift = 0;

    if (!radio_check_freq(freq, &shift)) {
        LV_LOG_ERROR("Freq %llu incorrect", freq);
        return;
    }

    op_work->tx = freq;
    op_work->shift = (shift != 0);

    control_set_tx_freq(freq - shift);
    radio_load_atu();

    lv_msg_send(MSG_FREQ_TX_CHANGED, &op_work->tx);
}

uint64_t radio_set_freqs(uint64_t rx, uint64_t tx) {
    uint64_t    ret = 0;

    switch (op_work->split) {
        case SPLIT_NONE:
            radio_set_freq_rx(rx);
            radio_set_freq_tx(tx);
            ret = rx;
            break;

        case SPLIT_RX:
            radio_set_freq_rx(rx);
            ret = rx;
            break;

        case SPLIT_TX:
            radio_set_freq_tx(tx);
            ret = tx;
    }

    voice_say_freq(ret);
    return ret;
}

void radio_set_freq_fft(uint64_t freq) {
    uint64_t shift = 0;

    if (!radio_check_freq(freq, &shift)) {
        LV_LOG_ERROR("Freq %llu incorrect", freq);
        return;
    }

    op_work->fft = freq;

    control_set_fft_freq(freq - shift);
    lv_msg_send(MSG_FREQ_FFT_CHANGED, &op_work->fft);
}

bool radio_check_freq(uint64_t freq, uint64_t *shift) {
    if (freq >= 1000000 && freq <= 55000000) {
        if (shift != NULL) {
            *shift = 0;
        }
        return true;
    }
    
    for (uint8_t i = 0; i < TRANSVERTER_NUM; i++)
        if (freq >= params_transverter[i].from && freq <= params_transverter[i].to) {
            if (shift != NULL) {
                *shift = params_transverter[i].shift;
            }
            return true;
        }

    return false;
}

split_mode_t radio_change_split(int16_t d) {
    if (d == 0) {
        return op_work->split;
    }

    op_work->split = limit(op_work->split + d, 0, 2);

    return op_work->split;
}

uint16_t radio_change_moni(int16_t df) {
    if (df == 0) {
        return params.moni;
    }
    
    params_lock();
    params.moni = limit(params.moni + df, 0, 100);
    params_unlock(&params.durty.moni);

    return params.moni;
}

uint16_t radio_change_sql(int16_t df) {
    if (df == 0) {
        return params.sql;
    }
    
    params_lock();
    params.sql = limit(params.sql + df, 0, 100);
    params_unlock(&params.durty.sql);

    return params.sql;
}

bool radio_change_pre() {
    params_lock();

    op_work->pre = !op_work->pre;

    voice_say_text_fmt("Preamplifier %s", op_work->pre ? "On" : "Off");
    return op_work->pre;
}

bool radio_change_att() {
    op_work->att = !op_work->att;

    voice_say_text_fmt("Attenuator %s", op_work->att ? "On" : "Off");
    return op_work->att;
}

void radio_filter_get(int32_t *from_freq, int32_t *to_freq) {
    radio_mode_t    mode = op_work->mode;

    switch (mode) {
        case RADIO_MODE_LSB:
            *from_freq = -op_mode->filter.high;
            *to_freq = -op_mode->filter.low;
            break;

        case RADIO_MODE_USB:
        case RADIO_MODE_RTTY:
        case RADIO_MODE_OLIVIA:
            *from_freq = op_mode->filter.low;
            *to_freq = op_mode->filter.high;
            break;

        case RADIO_MODE_CW:
            *from_freq = op_mode->filter.low;
            *to_freq = op_mode->filter.high;
            break;

        case RADIO_MODE_CWR:
            *from_freq = -op_mode->filter.high;
            *to_freq = -op_mode->filter.low;
            break;

        case RADIO_MODE_AM:
        case RADIO_MODE_NFM:
            *from_freq = -op_mode->filter.high;
            *to_freq = op_mode->filter.high;
            break;

        default:
            *from_freq = 0;
            *to_freq = 0;
    }
}

void radio_change_mode(radio_change_mode_t select) {
    radio_mode_t    mode = op_work->mode;

    switch (select) {
        case RADIO_MODE_NEXT:
            switch (mode) {
                case RADIO_MODE_CW:
                case RADIO_MODE_CWR:
                    mode = RADIO_MODE_LSB;
                    voice_say_text_fmt("L S B modulation");
                    break;

                case RADIO_MODE_LSB:
                case RADIO_MODE_USB:
                    mode = RADIO_MODE_AM;
                    voice_say_text_fmt("A M modulation");
                    break;

                case RADIO_MODE_AM:
                    mode = RADIO_MODE_NFM;
                    voice_say_text_fmt("N F M modulation");
                    break;

                case RADIO_MODE_NFM:
                    mode = RADIO_MODE_RTTY;
                    voice_say_text_fmt("R T T Y modulation");
                    break;

                case RADIO_MODE_RTTY:
                    mode = RADIO_MODE_OLIVIA;
                    voice_say_text_fmt("C W modulation");
                    break;

                case RADIO_MODE_OLIVIA:
                    mode = RADIO_MODE_CW;
                    voice_say_text_fmt("Olivia modulation");
                    break;
            }
            break;

        case RADIO_MODE_SUBSET:
            switch (mode) {
                case RADIO_MODE_CW:
                    mode = RADIO_MODE_CWR;
                    voice_say_text_fmt("C W R modulation");
                    break;

                case RADIO_MODE_CWR:
                    mode = RADIO_MODE_CW;
                    voice_say_text_fmt("C W modulation");
                    break;

                case RADIO_MODE_LSB:
                    mode = RADIO_MODE_USB;
                    voice_say_text_fmt("U S B modulation");
                    break;

                case RADIO_MODE_USB:
                    mode = RADIO_MODE_LSB;
                    voice_say_text_fmt("L S B modulation");
                    break;
            }
            break;

        default:
            break;
    }

    op_work_set_mode(mode);
}

uint32_t radio_change_filter_low(int32_t df) {
    if (df == 0) {
        return op_mode->filter.low;
    }

    radio_mode_t    mode = op_work->mode;

    if (mode == RADIO_MODE_AM || mode == RADIO_MODE_NFM) {
        return 0;
    }

    op_mode->filter.low = limit(align_int(op_mode->filter.low + df * 50, 50), 0, op_mode->filter.high - 100);
    dsp_set_filter(&op_mode->filter);

    return op_mode->filter.low;
}

uint32_t radio_change_filter_high(int32_t df) {
    if (df == 0) {
        return op_mode->filter.high;
    }

    radio_mode_t    mode = op_work->mode;

    op_mode->filter.high = limit(align_int(op_mode->filter.high + df * 50, 50), op_mode->filter.low + 100, 6000);
    dsp_set_filter(&op_mode->filter);

    return op_mode->filter.high;
}

uint32_t radio_change_filter_transition(int32_t df) {
    if (df == 0) {
        return op_mode->filter.transition;
    }

    op_mode->filter.transition = limit(align_int(op_mode->filter.transition + df * 2, 2), 50, 200);
    dsp_set_filter(&op_mode->filter);

    return op_mode->filter.transition;
}

void radio_change_atu() {
    params_lock();
    params.atu = !params.atu;
    params_unlock(&params.durty.atu);

    radio_load_atu();
    voice_say_text_fmt("Auto tuner %s", params.atu ? "On" : "Off");
}

void radio_start_atu() {
    if (state == RADIO_RX) {
        state = RADIO_ATU_START;
    }
}

bool radio_start_swrscan() {
    if (state != RADIO_RX) {
        return false;
    }

    state = RADIO_SWRSCAN;
    return true;
}

void radio_stop_swrscan() {
    if (state == RADIO_SWRSCAN) {
        state = RADIO_RX;
    }
}

void radio_load_atu() {
/* FIXME
    if (params.atu) {
        if (op_work->shift) {
            info_atu_update();

            return;
        }

        uint32_t atu = params_atu_load(&params.atu_loaded);

        if (state != RADIO_SWRSCAN) {
            info_atu_update();
        }
    }
*/
}

float radio_change_pwr(int16_t d) {
    if (d == 0) {
        return params.pwr;
    }
    
    params_lock();
    params.pwr += d * 0.1f;
    
    if (params.pwr > 10.0f) {
        params.pwr = 10.0f;
    } else if (params.pwr < 0.1f) {
        params.pwr = 0.1f;
    }
    
    params_unlock(&params.durty.pwr);

    return params.pwr;
}

void radio_poweroff() {
    state = RADIO_POWEROFF;
}

bool radio_change_dnf(int16_t d) {
    if (d == 0) {
        return params.dnf;
    }

    params_lock();
    params.dnf = !params.dnf;
    params_unlock(&params.durty.dnf);
    
    return params.dnf;
}

uint16_t radio_change_dnf_center(int16_t d) {
    if (d == 0) {
        return params.dnf_center;
    }

    params_lock();
    params.dnf_center = limit(params.dnf_center + d * 50, 100, 3000);
    params_unlock(&params.durty.dnf_center);
    
    return params.dnf_center;
}

uint16_t radio_change_dnf_width(int16_t d) {
    if (d == 0) {
        return params.dnf_width;
    }

    params_lock();
    params.dnf_width = limit(params.dnf_width + d * 5, 10, 100);
    params_unlock(&params.durty.dnf_width);
    
    return params.dnf_width;
}

bool radio_change_nb(int16_t d) {
    if (d == 0) {
        return params.nb;
    }

    params_lock();
    params.nb = !params.nb;
    params_unlock(&params.durty.nb);
    
    return params.nb;
}

uint8_t radio_change_nb_level(int16_t d) {
    if (d == 0) {
        return params.nb_level;
    }

    params_lock();
    params.nb_level = limit(params.nb_level + d * 5, 0, 100);
    params_unlock(&params.durty.nb_level);
    
    return params.nb_level;
}

uint8_t radio_change_nb_width(int16_t d) {
    if (d == 0) {
        return params.nb_width;
    }

    params_lock();
    params.nb_width = limit(params.nb_width + d * 5, 0, 100);
    params_unlock(&params.durty.nb_width);
    
    return params.nb_width;
}

bool radio_change_nr(int16_t d) {
    if (d == 0) {
        return params.nr;
    }

    params_lock();
    params.nr = !params.nr;
    params_unlock(&params.durty.nr);
    
    return params.nr;
}

uint8_t radio_change_nr_level(int16_t d) {
    if (d == 0) {
        return params.nr_level;
    }

    params_lock();
    params.nr_level = limit(params.nr_level + d * 5, 0, 60);
    params_unlock(&params.durty.nr_level);
    
    return params.nr_level;
}

void radio_set_ptt(bool on) {
}

void radio_set_morse_key(bool on) {
}
