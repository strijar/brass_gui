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
#include "audio_adc.h"
#include "msgs.h"

#define FLOW_RESTART_TIMOUT     300

static lv_obj_t                 *main_obj;

static radio_state_t            state = RADIO_RX;
static bool                     mute = false;

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

void radio_freq_set() {
    uint64_t shift;
    uint64_t freq = params_band.freq_rx;

    radio_check_freq(freq, &shift);
    control_set_rx_freq(freq - shift);
    control_set_tx_freq(params_band.freq_tx - shift);
    control_set_fft_freq(params_band.freq_fft - shift);

    params_bands_find(freq, &params.freq_band);
}

static void update_filter() {
    dsp_set_filter(params_mode.filter_low, params_mode.filter_high, params_mode.filter_transition, 40);
    lv_msg_send(MSG_FILTER_CHANGED, NULL);
}

void radio_mode_set() {
    radio_mode_t    mode = radio_current_mode();

    update_filter();
    dsp_set_rx_agc(params_mode.agc);

    dsp_set_spectrum_factor(params_mode.spectrum_factor);
}

static void radio_msg_cb(void *s, lv_msg_t *m) {
    switch (lv_msg_get_id(m)) {
        case MSG_PTT: {
            const int *on = lv_msg_get_payload(m);

            state = *on ? RADIO_TX : RADIO_RX;
        } break;

        default:
            break;
    }
}

void radio_init(lv_obj_t *obj) {
    main_obj = obj;

    control_init();
    dsp_set_spectrum_factor(params_mode.spectrum_factor);

    radio_freq_set();
    radio_mode_set();
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

    params_lock();
    params_band.freq_rx = freq;
    params_band.shift = (shift != 0);
    params_unlock(&params_band.durty.freq_rx);

    control_set_rx_freq(freq - shift);
    radio_load_atu();

    lv_msg_send(MSG_FREQ_RX_CHANGED, &params_band.freq_rx);
}

void radio_set_freq_tx(uint64_t freq) {
    uint64_t shift = 0;
    
    if (!radio_check_freq(freq, &shift)) {
        LV_LOG_ERROR("Freq %llu incorrect", freq);
        return;
    }

    params_lock();
    params_band.freq_tx = freq;
    params_band.shift = (shift != 0);
    params_unlock(&params_band.durty.freq_tx);

    control_set_tx_freq(freq - shift);
    radio_load_atu();

    lv_msg_send(MSG_FREQ_TX_CHANGED, &params_band.freq_tx);
}

uint64_t radio_set_freqs(uint64_t rx, uint64_t tx) {
    uint64_t ret = 0;

    switch (params_band.split) {
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

    params_lock();
    params_band.freq_fft = freq;
    params_unlock(&params_band.durty.freq_fft);

    control_set_fft_freq(freq - shift);
    lv_msg_send(MSG_FREQ_FFT_CHANGED, &params_band.freq_fft);
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
        return params_band.split;
    }

    params_lock();
    params_band.split = limit(params_band.split + d, 0, 2);
    params_unlock(&params_band.durty.split);
    
    return params_band.split;
}

void radio_change_mute() {
    mute = !mute;
    // x6100_control_rxvol_set(mute ? 0 : params.vol);
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

uint16_t radio_change_rfg(int16_t df) {
    if (df == 0) {
        return params.rfg;
    }
    
    params_lock();
    params.rfg = limit(params.rfg + df, 0, 100);
    params_unlock(&params.durty.rfg);

    return params.rfg;
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
    
    params_band.pre = !params_band.pre;
    params_unlock(&params_band.durty.pre);

    voice_say_text_fmt("Preamplifier %s", params_band.pre ? "On" : "Off");
    return params_band.pre;
}

bool radio_change_att() {
    params_lock();
    
    params_band.att = !params_band.att;
    params_unlock(&params_band.durty.att);

    voice_say_text_fmt("Attenuator %s", params_band.att ? "On" : "Off");
    return params_band.att;
}

void radio_filter_get(int32_t *from_freq, int32_t *to_freq) {
    radio_mode_t    mode = radio_current_mode();

    switch (mode) {
        case radio_mode_lsb:
            *from_freq = -params_mode.filter_high;
            *to_freq = -params_mode.filter_low;
            break;
            
        case radio_mode_usb:
            *from_freq = params_mode.filter_low;
            *to_freq = params_mode.filter_high;
            break;

        case radio_mode_cw:
            *from_freq = params_mode.filter_low;
            *to_freq = params_mode.filter_high;
            break;
            
        case radio_mode_cwr:
            *from_freq = -params_mode.filter_high;
            *to_freq = -params_mode.filter_low;
            break;

        case radio_mode_am:
        case radio_mode_nfm:
            *from_freq = -params_mode.filter_high;
            *to_freq = params_mode.filter_high;
            break;
            
        default:
            *from_freq = 0;
            *to_freq = 0;
    }
}

void radio_set_mode(radio_mode_t mode) {
    params_band.mode = mode;
    params_unlock(&params_band.durty.mode);
    lv_msg_send(MSG_MODE_CHANGED, &params_band.mode);
}

void radio_restore_mode(radio_mode_t mode) {
    params_lock();
    params_band.mode = mode;
    params_unlock(&params_band.durty.mode);
}

void radio_change_mode(radio_mode_t select) {
    params_lock();

    radio_mode_t    mode = radio_current_mode();

    switch (select) {
        case RADIO_MODE_NEXT:
            switch (mode) {
                case radio_mode_cw:
                case radio_mode_cwr:
                    mode = radio_mode_lsb;
                    voice_say_text_fmt("L S B modulation");
                    break;

                case radio_mode_lsb:
                case radio_mode_usb:
                    mode = radio_mode_am;
                    voice_say_text_fmt("A M modulation");
                    break;

                case radio_mode_am:
                    mode = radio_mode_nfm;
                    voice_say_text_fmt("N F M modulation");
                    break;
                    
                case radio_mode_nfm:
                    mode = radio_mode_cw;
                    voice_say_text_fmt("C W modulation");
                    break;
            }
            break;
            
        case RADIO_MODE_SUBSET:
            switch (mode) {
                case radio_mode_cw:
                    mode = radio_mode_cwr;
                    voice_say_text_fmt("C W R modulation");
                    break;

                case radio_mode_cwr:
                    mode = radio_mode_cw;
                    voice_say_text_fmt("C W modulation");
                    break;

                case radio_mode_lsb:
                    mode = radio_mode_usb;
                    voice_say_text_fmt("U S B modulation");
                    break;

                case radio_mode_usb:
                    mode = radio_mode_lsb;
                    voice_say_text_fmt("L S B modulation");
                    break;
            }
            break;
            
        case RADIO_MODE_USB:
            mode = radio_mode_usb;
            break;

        case RADIO_MODE_LSB:
            mode = radio_mode_lsb;
            break;
        
        default:
            break;
    }

    params_mode_save();
    radio_set_mode(mode);
}

radio_mode_t radio_current_mode() {
    return params_band.mode;
}

uint32_t radio_change_filter_low(int32_t df) {
    if (df == 0) {
        return params_mode.filter_low;
    }

    radio_mode_t    mode = radio_current_mode();
    
    if (mode == radio_mode_am || mode == radio_mode_nfm) {
        return 0;
    }

    params_lock();

    params_mode.filter_low = align_int(params_mode.filter_low + df * 50, 50);
    
    if (params_mode.filter_low < 0) {
        params_mode.filter_low = 0;
    } else if (params_mode.filter_low > params_mode.filter_high - 100) {
        params_mode.filter_low = params_mode.filter_high - 100;
    }
    params_unlock(&params_mode.durty.filter_low);

    update_filter();

    return params_mode.filter_low;
}

uint32_t radio_change_filter_high(int32_t df) {
    if (df == 0) {
        return params_mode.filter_high;
    }

    radio_mode_t    mode = radio_current_mode();

    params_lock();
    params_mode.filter_high = align_int(params_mode.filter_high + df * 50, 50);

    if (params_mode.filter_high < 600) {
        params_mode.filter_high = 600;
    } else if (params_mode.filter_high < params_mode.filter_low + 100) {
        params_mode.filter_high = params_mode.filter_low + 100;
    }
    params_unlock(&params_mode.durty.filter_high);

    update_filter();

    return params_mode.filter_high;
}

uint32_t radio_change_filter_transition(int32_t df) {
    if (df == 0) {
        return params_mode.filter_transition;
    }

    params_lock();
    params_mode.filter_transition = align_int(params_mode.filter_transition + df * 2, 2);

    if (params_mode.filter_transition < 50) {
        params_mode.filter_transition = 50;
    } else if (params_mode.filter_transition > 200) {
        params_mode.filter_transition = 200;
    }
    params_unlock(&params_mode.durty.filter_transition);

    update_filter();

    return params_mode.filter_transition;
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

    // x6100_control_vfo_mode_set(params_band.vfo, radio_mode_am);
    // x6100_control_txpwr_set(5.0f);
    // x6100_control_swrscan_set(true);
        
    return true;
}

void radio_stop_swrscan() {
    if (state == RADIO_SWRSCAN) {
        // x6100_control_swrscan_set(false);
        // x6100_control_txpwr_set(params.pwr);
        state = RADIO_RX;
    }
}

void radio_load_atu() {
    if (params.atu) {
        if (params_band.shift) {
            info_atu_update();

            return;
        }
    
        uint32_t atu = params_atu_load(&params.atu_loaded);

        if (state != RADIO_SWRSCAN) {
            info_atu_update();
        }
    }
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

radio_mic_sel_t radio_change_mic(int16_t d) {
    if (d == 0) {
        return params.mic;
    }
    
    params_lock();
    
    switch (params.mic) {
        case radio_mic_builtin:
            params.mic = d > 0 ? radio_mic_handle : radio_mic_auto;
            break;
            
        case radio_mic_handle:
            params.mic = d > 0 ? radio_mic_auto : radio_mic_builtin;
            break;
            
        case radio_mic_auto:
            params.mic = d > 0 ? radio_mic_builtin : radio_mic_handle;
            break;
    }
    
    params_unlock(&params.durty.mic);
    
    return params.mic;
}

uint8_t radio_change_hmic(int16_t d) {
    if (d == 0) {
        return params.hmic;
    }

    params_lock();
    params.hmic = limit(params.hmic + d, 0, 50);
    params_unlock(&params.durty.hmic);
    
    return params.hmic;
}

uint8_t radio_change_imic(int16_t d) {
    if (d == 0) {
        return params.imic;
    }

    params_lock();
    params.imic = limit(params.imic + d, 0, 35);
    params_unlock(&params.durty.imic);
    
    return params.imic;
}

void radio_poweroff() {
    if (params.charger == RADIO_CHARGER_SHADOW) {
    }

    state = RADIO_POWEROFF;
}

radio_charger_t radio_change_charger(int16_t d) {
    if (d == 0) {
        return params.charger;
    }

    params_lock();
    
    switch (params.charger) {
        case RADIO_CHARGER_OFF:
            params.charger = d > 0 ? RADIO_CHARGER_ON : RADIO_CHARGER_SHADOW;
            break;
            
        case RADIO_CHARGER_ON:
            params.charger = d > 0 ? RADIO_CHARGER_SHADOW : RADIO_CHARGER_OFF;
            break;
            
        case RADIO_CHARGER_SHADOW:
            params.charger = d > 0 ? RADIO_CHARGER_OFF : RADIO_CHARGER_ON;
            break;
    }
    
    params_unlock(&params.durty.charger);
    
    return params.charger;
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

void radio_set_ptt(bool tx) {
}

void radio_set_line_in(uint8_t d) {
    params_lock();
    params.line_in = d;
    params_unlock(&params.durty.line_in);
}

void radio_set_line_out(uint8_t d) {
    params_lock();
    params.line_out = d;
    params_unlock(&params.durty.line_out);
}

void radio_set_morse_key(bool on) {
}
