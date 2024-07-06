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

#define FLOW_RESTART_TIMOUT     300

static lv_obj_t                 *main_obj;

static radio_state_t            state = RADIO_RX;
static bool                     mute = false;

static void update_agc_time();

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

void radio_vfo_set() {
    uint64_t shift;
    uint64_t freq = params_band.vfo_x[params_band.vfo].freq_rx;

    radio_check_freq(freq, &shift);
    control_set_rx_freq(freq - shift);
    control_set_fft_freq(freq - shift);

    /*
    for (int i = 0; i < 2; i++) {
        x6100_control_vfo_mode_set(i, params_band.vfo_x[i].mode);
        x6100_control_vfo_agc_set(i, params_band.vfo_x[i].agc);
        x6100_control_vfo_pre_set(i, params_band.vfo_x[i].pre);
        x6100_control_vfo_att_set(i, params_band.vfo_x[i].att);
        
        radio_check_freq(params_band.vfo_x[i].freq, &shift);
        x6100_control_vfo_freq_set(i, params_band.vfo_x[i].freq - shift);
        params_band.vfo_x[i].shift = (shift != 0);
    }

    x6100_control_vfo_set(params_band.vfo);
    x6100_control_split_set(params_band.split);
    */
    params_bands_find(freq, &params.freq_band);
}

static void update_filter() {
    dsp_set_filter(params_mode.filter_low, params_mode.filter_high, params_mode.filter_transition, 40);
}

void radio_mode_set() {
    radio_mode_t    mode = radio_current_mode();

    update_filter();
    update_agc_time();

    dsp_set_spectrum_factor(params_mode.spectrum_factor);
}

void radio_init(lv_obj_t *obj) {
    main_obj = obj;

    control_init();
    dsp_set_spectrum_factor(params_mode.spectrum_factor);

    radio_vfo_set();
    radio_mode_set();
    radio_load_atu();
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
    params_band.vfo_x[params_band.vfo].freq_rx = freq;
    params_band.vfo_x[params_band.vfo].shift = (shift != 0);
    params_unlock(&params_band.vfo_x[params_band.vfo].durty.freq_rx);

    control_set_rx_freq(freq - shift);
    radio_load_atu();
}

void radio_set_freq_fft(uint64_t freq) {
    uint64_t shift = 0;
    
    if (!radio_check_freq(freq, &shift)) {
        LV_LOG_ERROR("Freq %llu incorrect", freq);
        return;
    }

    params_lock();
    params_band.vfo_x[params_band.vfo].freq_fft = freq;
    params_unlock(&params_band.vfo_x[params_band.vfo].durty.freq_fft);

    control_set_fft_freq(freq - shift);
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
    bool vfoa = (params_band.vfo == RADIO_VFO_A);

    params_lock();
    
    params_band.vfo_x[params_band.vfo].pre = !params_band.vfo_x[params_band.vfo].pre;
    params_unlock(&params_band.vfo_x[params_band.vfo].durty.pre);

    voice_say_text_fmt("Preamplifier %s", params_band.vfo_x[params_band.vfo].pre ? "On" : "Off");
    return params_band.vfo_x[params_band.vfo].pre;
}

bool radio_change_att() {
    params_lock();
    
    params_band.vfo_x[params_band.vfo].att = !params_band.vfo_x[params_band.vfo].att;
    params_unlock(&params_band.vfo_x[params_band.vfo].durty.att);

    voice_say_text_fmt("Attenuator %s", params_band.vfo_x[params_band.vfo].att ? "On" : "Off");
    return params_band.vfo_x[params_band.vfo].att;
}

void radio_filter_get(int32_t *from_freq, int32_t *to_freq) {
    radio_mode_t    mode = radio_current_mode();

    switch (mode) {
        case radio_mode_lsb:
        case radio_mode_lsb_dig:
            *from_freq = -params_mode.filter_high;
            *to_freq = -params_mode.filter_low;
            break;
            
        case radio_mode_usb:
        case radio_mode_usb_dig:
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

void radio_set_mode(radio_vfo_t vfo, radio_mode_t mode) {
    params_band.vfo_x[vfo].mode = mode;
    params_unlock(&params_band.vfo_x[vfo].durty.mode);
}

void radio_restore_mode(radio_mode_t mode) {
    radio_vfo_t vfo = params_band.vfo;

    params_lock();
    params_band.vfo_x[vfo].mode = mode;
    params_unlock(&params_band.vfo_x[vfo].durty.mode);
}

void radio_change_mode(radio_mode_t select) {
    params_lock();

    radio_mode_t    mode = radio_current_mode();

    switch (select) {
        case RADIO_MODE_AM:
            switch (mode) {
                case radio_mode_am:
                    mode = radio_mode_nfm;
                    voice_say_text_fmt("N F M modulation");
                    break;
                    
                case radio_mode_nfm:
                    mode = radio_mode_am;
                    voice_say_text_fmt("A M modulation");
                    break;
                    
                default:
                    mode = radio_mode_am;
                    voice_say_text_fmt("A M modulation");
                    break;
            }
            break;
            
        case RADIO_MODE_CW:
            switch (mode) {
                case radio_mode_cw:
                    mode = radio_mode_cwr;
                    voice_say_text_fmt("CWR modulation");
                    break;
                    
                case radio_mode_cwr:
                    mode = radio_mode_cw;
                    voice_say_text_fmt("CW modulation");
                    break;
                    
                default:
                    mode = radio_mode_cw;
                    voice_say_text_fmt("CW modulation");
                    break;
            }
            break;
            
        case RADIO_MODE_SSB:
            switch (mode) {
                case radio_mode_lsb:
                    mode = radio_mode_lsb_dig;
                    voice_say_text_fmt("LSB digital modulation");
                    break;
                    
                case radio_mode_lsb_dig:
                    mode = radio_mode_usb;
                    voice_say_text_fmt("USB modulation");
                    break;
                    
                case radio_mode_usb:
                    mode = radio_mode_usb_dig;
                    voice_say_text_fmt("USB digital modulation");
                    break;
                    
                case radio_mode_usb_dig:
                    mode = radio_mode_lsb;
                    voice_say_text_fmt("LSB modulation");
                    break;
                    
                default: 
                    mode = radio_mode_lsb;
                    voice_say_text_fmt("LSB modulation");
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
    radio_set_mode(params_band.vfo, mode);
}

radio_mode_t radio_current_mode() {
    return params_band.vfo_x[params_band.vfo].mode;
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

static void update_agc_time() {
    radio_agc_t     agc = params_band.vfo_x[params_band.vfo].agc;
    radio_mode_t    mode = radio_current_mode();
    uint16_t        agc_time = 500;

    switch (agc) {
        case radio_agc_off:
            agc_time = 1000;
            break;
            
        case radio_agc_slow:
            agc_time = 1000;
            break;
            
        case radio_agc_fast:
            agc_time = 100;
            break;
            
        case radio_agc_auto:
            switch (mode) {
                case radio_mode_lsb:
                case radio_mode_lsb_dig:
                case radio_mode_usb:
                case radio_mode_usb_dig:
                    agc_time = 500;
                    break;
                    
                case radio_mode_cw:
                case radio_mode_cwr:
                    agc_time = 100;
                    break;
                    
                case radio_mode_am:
                case radio_mode_nfm:
                    agc_time = 1000;
                    break;
            }
            break;
    }
}

void radio_change_agc() {
    params_lock();

    radio_agc_t     agc = params_band.vfo_x[params_band.vfo].agc;
    
    switch (agc) {
        case radio_agc_off:
            agc = radio_agc_slow;
            voice_say_text_fmt("Auto gain slow mode");
            break;
            
        case radio_agc_slow:
            agc = radio_agc_fast;
            voice_say_text_fmt("Auto gain fast mode");
            break;
            
        case radio_agc_fast:
            agc = radio_agc_auto;
            voice_say_text_fmt("Auto gain auto mode");
            break;
            
        case radio_agc_auto:
            agc = radio_agc_off;
            voice_say_text_fmt("Auto gain off");
            break;
    }

    update_agc_time();

    params_band.vfo_x[params_band.vfo].agc = agc;
    params_unlock(&params_band.vfo_x[params_band.vfo].durty.agc);
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
        if (params_band.vfo_x[params_band.vfo].shift) {
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

uint16_t radio_change_key_speed(int16_t d) {
    if (d == 0) {
        return params.key_speed;
    }
    
    params_lock();
    params.key_speed = limit(params.key_speed + d, 5, 50);
    params_unlock(&params.durty.key_speed);

    return params.key_speed;
}

radio_key_mode_t radio_change_key_mode(int16_t d) {
    if (d == 0) {
        return params.key_mode;
    }

    params_lock();

    switch (params.key_mode) {
        case radio_key_manual:
            params.key_mode = d > 0 ? radio_key_auto_left : radio_key_auto_right;
            break;
            
        case radio_key_auto_left:
            params.key_mode = d > 0 ? radio_key_auto_right : radio_key_manual;
            break;
            
        case radio_key_auto_right:
            params.key_mode = d > 0 ? radio_key_manual : radio_key_auto_left;
            break;
    }

    params_unlock(&params.durty.key_mode);

    return params.key_mode;
}

radio_iambic_mode_t radio_change_iambic_mode(int16_t d) {
    if (d == 0) {
        return params.iambic_mode;
    }

    params_lock();

    params.iambic_mode = (params.iambic_mode == radio_iambic_a) ? radio_iambic_b : radio_iambic_a;

    params_unlock(&params.durty.iambic_mode);

    return params.iambic_mode;
}

uint16_t radio_change_key_tone(int16_t d) {
    if (d == 0) {
        return params.key_tone;
    }

    params_lock();

    params.key_tone += (d > 0) ? 10 : -10;

    if (params.key_tone < 400) {
        params.key_tone = 400;
    } else if (params.key_tone > 1200) {
        params.key_tone = 1200;
    }

    params_unlock(&params.durty.key_tone);

    return params.key_tone;
}

uint16_t radio_change_key_vol(int16_t d) {
    if (d == 0) {
        return params.key_vol;
    }

    params_lock();

    params.key_vol = limit(params.key_vol + d, 0, 32);
    params_unlock(&params.durty.key_vol);

    return params.key_vol;
}

bool radio_change_key_train(int16_t d) {
    if (d == 0) {
        return params.key_train;
    }

    params_lock();
    params.key_train = !params.key_train;
    params_unlock(&params.durty.key_train);

    return params.key_train;
}

uint16_t radio_change_qsk_time(int16_t d) {
    if (d == 0) {
        return params.qsk_time;
    }

    params_lock();

    int16_t x = params.qsk_time;
    
    if (d > 0) {
        x += 10;
    } else {
        x -= 10;
    }
    
    params.qsk_time = limit(x, 0, 1000);
    params_unlock(&params.durty.qsk_time);

    return params.qsk_time;
}

uint8_t radio_change_key_ratio(int16_t d) {
    if (d == 0) {
        return params.key_ratio;
    }

    params_lock();

    int16_t x = params.key_ratio;

    if (d > 0) {
        x += 5;
    } else {
        x -= 5;
    }

    params.key_ratio = limit(x, 25, 45);
    params_unlock(&params.durty.key_ratio);

    return params.key_ratio;
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

radio_vfo_t radio_set_vfo(radio_vfo_t vfo) {
    params_lock();
    params_band.vfo = vfo;
    params_unlock(&params_band.durty.vfo);
}

radio_vfo_t radio_change_vfo() {
    radio_vfo_t vfo = (params_band.vfo == RADIO_VFO_A) ? RADIO_VFO_B : RADIO_VFO_A;

    radio_set_vfo(vfo);
    voice_say_text_fmt("V F O %s", (params_band.vfo == RADIO_VFO_A) ? "A" : "B");
    
    return params_band.vfo;
}

void radio_change_split() {
    params_lock();
    params_band.split = !params_band.split;
    params_unlock(&params_band.durty.split);
    
    voice_say_text_fmt("Split %s", params_band.split ? "On" : "Off");
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

bool radio_change_agc_hang(int16_t d) {
    if (d == 0) {
        return params.agc_hang;
    }

    params_lock();
    params.agc_hang = !params.agc_hang;
    params_unlock(&params.durty.agc_hang);

    return params.agc_hang;
}

int8_t radio_change_agc_knee(int16_t d) {
    if (d == 0) {
        return params.agc_knee;
    }

    params_lock();
    params.agc_knee = limit(params.agc_knee + d, -100, 0);
    params_unlock(&params.durty.agc_knee);

    return params.agc_knee;
}

uint8_t radio_change_agc_slope(int16_t d) {
    if (d == 0) {
        return params.agc_slope;
    }

    params_lock();
    params.agc_slope = limit(params.agc_slope + d, 0, 10);
    params_unlock(&params.durty.agc_slope);

    return params.agc_slope;
}

void radio_set_ptt(bool tx) {
}

int16_t radio_change_rit(int16_t d) {
    if (d == 0) {
        return params.rit;
    }
    
    params_lock();
    params.rit = limit(align_int(params.rit + d * 10, 10), -1500, +1500);
    params_unlock(&params.durty.rit);

    return params.rit;
}

int16_t radio_change_xit(int16_t d) {
    if (d == 0) {
        return params.xit;
    }
    
    params_lock();
    params.xit = limit(align_int(params.xit + d * 10, 10), -1500, +1500);
    params_unlock(&params.durty.xit);

    return params.xit;
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
