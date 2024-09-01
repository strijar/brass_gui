/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

#include "main_screen.h"
#include "styles.h"
#include "spectrum.h"
#include "waterfall.h"
#include "util.h"
#include "radio.h"
#include "events.h"
#include "msg.h"
#include "msg_tiny.h"
#include "dsp.h"
#include "params.h"
#include "bands.h"
#include "clock.h"
#include "info.h"
#include "meter.h"
#include "band_info.h"
#include "tx_info.h"
#include "mfk.h"
#include "vol.h"
#include "main.h"
#include "pannel.h"
#include "rtty.h"
#include "screenshot.h"
#include "keyboard.h"
#include "dialog.h"
#include "dialog_settings.h"
#include "dialog_freq.h"
#include "dialog_msg_cw.h"
#include "dialog_msg_voice.h"
#include "dialog_swrscan.h"
#include "dialog_ft8.h"
#include "dialog_gps.h"
#include "dialog_qth.h"
#include "dialog_recorder.h"
#include "dialog_callsign.h"
#include "backlight.h"
#include "buttons.h"
#include "recorder.h"
#include "voice.h"
#include "python/python.h"
#include "msgs.h"

static uint16_t     spectrum_height = (480 / 3);
static uint16_t     freq_height = 36;
static lv_obj_t     *obj;
static bool         freq_lock = false;
static bool         mode_lock = false;
static bool         band_lock = false;

static lv_obj_t     *freq[3];
static lv_obj_t     *waterfall;
static lv_obj_t     *msg;
static lv_obj_t     *msg_tiny;
static lv_obj_t     *meter;
static lv_obj_t     *tx_info;

static void freq_shift(int16_t diff);
static void next_freq_step(bool up);
static uint64_t freq_update();

void mem_load(uint16_t id) {
    params_memory_load(id);

    if (params_bands_find(params_band.vfo_x[params_band.vfo].freq_rx, &params.freq_band)) {
        if (params.freq_band.type != 0) {
            params.band = params.freq_band.id;
        } else {
            params.band = -1;
        }
    } else {
        params.band = -1;
    }

    radio_vfo_set();
    radio_mode_set();

    radio_load_atu();
    info_params_set();
    pannel_visible();

    dsp_auto_clear();
    freq_update();

    if (strlen(params_band.label) > 0) {
        msg_set_text_fmt("%s", params_band.label);
    } else if (id <= MEM_NUM) {
        msg_set_text_fmt("Loaded from memory %i", id);
    }
}

void mem_save(uint16_t id) {
    params_memory_save(id);
    
    if (id <= MEM_NUM) {
        msg_set_text_fmt("Saved in memory %i", id);
    }
}

/* * */

static uint64_t freq_update() {
    uint64_t    f;
    radio_vfo_t vfo = params_band.vfo;
    uint32_t    color = freq_lock ? 0xBBBBBB : 0xFFFFFF;
    uint16_t    mhz, khz, hz;

    if (params_band.split && radio_get_state() == RADIO_TX) {
        vfo = (vfo == RADIO_VFO_A) ? RADIO_VFO_B : RADIO_VFO_A;
    }

    f = radio_current_freq_fft();

    int32_t half = 50000 / params_mode.spectrum_factor;

    split_freq(f - half, &mhz, &khz, &hz);
    lv_label_set_text_fmt(freq[0], "#%03X %i.%03i", color, mhz, khz);

    split_freq(f + half, &mhz, &khz, &hz);
    lv_label_set_text_fmt(freq[2], "#%03X %i.%03i", color, mhz, khz);

    f = radio_current_freq_rx();

    split_freq(f, &mhz, &khz, &hz);

    if (params.mag_freq.x) {
        if (mhz < 100) {
            msg_tiny_set_text_fmt("%i.%03i.%03i", mhz, khz, hz);
        } else {
            msg_tiny_set_text_fmt("%i.%03i", mhz, khz);
        }
    }

    if (params_band.split) {
        uint16_t    mhz2, khz2, hz2;
        uint64_t    f2 = params_band.vfo_x[(vfo == RADIO_VFO_A) ? RADIO_VFO_B : RADIO_VFO_A].freq_rx;

        split_freq(f2, &mhz2, &khz2, &hz2);
        
        lv_label_set_text_fmt(freq[1], "#%03X %i.%03i.%03i / %i.%03i.%03i", color, mhz, khz, hz, mhz2, khz2, hz2);
    } else {
        lv_label_set_text_fmt(freq[1], "#%03X %i.%03i.%03i", color, mhz, khz, hz);
    }
    
    return f;
}

static bool check_cross_band(uint64_t freq) {
    uint8_t spectrum_factor = params_mode.spectrum_factor;

    if (params_bands_find(freq, &params.freq_band)) {
        if (params.freq_band.type != 0) {
            if (params.freq_band.id != params.band) {
                bands_activate(&params.freq_band, false);
                
                if (params_mode.spectrum_factor != spectrum_factor) {
                    main_screen_update_range();
                }
                
                info_params_set();
                pannel_visible();
                return true;
            }
        } else {
            params.band = -1;
        }
    } else {
        params.band = -1;
    }

    return false;
}

static void next_freq_step(bool up) {
    params_lock();
    
    switch (params_mode.freq_step) {
        case 10:
            params_mode.freq_step = up ? 100 : 5000;
            break;
            
        case 100:
            params_mode.freq_step = up ? 500 : 10;
            break;
            
        case 500:
            params_mode.freq_step = up ? 1000 : 100;
            break;
            
        case 1000:
            params_mode.freq_step = up ? 5000 : 500;
            break;
            
        case 5000:
            params_mode.freq_step = up ? 10 : 1000;
            break;
            
        default:
            break;
    }

    params_unlock(&params_mode.durty.freq_step);
    msg_set_text_fmt("Freq step: %i Hz", params_mode.freq_step);
    voice_say_text_fmt("Frequency step %i herz", params_mode.freq_step);
}

static void apps_disable() {
    dialog_destruct();

    rtty_set_state(RTTY_OFF);
    pannel_visible();
}

void main_screen_dialog_deleted_cb() {
    buttons_unload_page();
    buttons_load_page(PAGE_VOL_1);
}

void main_screen_app(uint8_t page_app) {
    apps_disable();
    buttons_unload_page();
    buttons_load_page(page_app);

    switch (page_app) {
        case PAGE_RTTY:
            rtty_set_state(RTTY_RX);
            pannel_visible();
            voice_say_text_fmt("Teletype window");
            break;
            
        case PAGE_SETTINGS:
            dialog_construct(dialog_settings, obj);
            voice_say_text_fmt("Settings window");
            break;

        case PAGE_SWRSCAN:
            dialog_construct(dialog_swrscan, obj);
            voice_say_text_fmt("SWR scan window");
            break;

        case PAGE_FT8:
            dialog_construct(dialog_ft8, obj);
            voice_say_text_fmt("FT8 window");
            break;

        case PAGE_GPS:
            dialog_construct(dialog_gps, obj);
            voice_say_text_fmt("GPS window");
            break;

        case PAGE_RECORDER:
            dialog_construct(dialog_recorder, obj);
            voice_say_text_fmt("Audio recorder window");
            break;
            
        default:
            break;
    }
}

void main_screen_action(press_action_t action) {
    switch (action) {
        case ACTION_NONE:
            break;

        case ACTION_SCREENSHOT:
            screenshot_take();
            break;

        case ACTION_RECORDER:
            if (recorder_is_on()) {
                recorder_set_on(false);
                voice_say_text_fmt("Audio recorder off");
            } else {
                voice_say_text_fmt("Audio recorder on");
                recorder_set_on(true);
            }
            break;

        case ACTION_MUTE:
            radio_change_mute();
            break;

        case ACTION_VOICE_MODE:
            voice_change_mode();
            break;

        case ACTION_STEP_UP:
            next_freq_step(true);
            break;

        case ACTION_STEP_DOWN:
            next_freq_step(false);
            break;
            
        case ACTION_APP_RTTY:
            main_screen_app(PAGE_RTTY);
            break;
            
        case ACTION_APP_FT8:
            main_screen_app(PAGE_FT8);
            break;
            
        case ACTION_APP_SWRSCAN:
            main_screen_app(PAGE_SWRSCAN);
            break;
            
        case ACTION_APP_GPS:
            main_screen_app(PAGE_GPS);
            break;
            
        case ACTION_APP_SETTINGS:
            main_screen_app(PAGE_SETTINGS);
            break;

        case ACTION_APP_RECORDER:
            main_screen_app(PAGE_RECORDER);
            break;

        case ACTION_APP_QTH:
            dialog_construct(dialog_qth, obj);
            voice_say_text_fmt("QTH window");
            break;

        case ACTION_APP_CALLSIGN:
            dialog_construct(dialog_callsign, obj);
            voice_say_text_fmt("Callsign window");
            break;
    }
}

static void main_screen_keypad_cb(lv_event_t * e) {
    event_keypad_t *keypad = lv_event_get_param(e);

    switch (keypad->key) {
        case KEYPAD_PRE:
            if (keypad->state == KEYPAD_RELEASE) {
                radio_change_pre();
                info_params_set();
                
                if (params.mag_info.x) {
                    msg_tiny_set_text_fmt("Pre: %s", info_params_pre() ? "On" : "Off");
                }
            } else if (keypad->state == KEYPAD_LONG) {
                radio_change_att();
                info_params_set();

                if (params.mag_info.x) {
                    msg_tiny_set_text_fmt("Att: %s", info_params_att() ? "On" : "Off");
                }
            }
            break;
            
        case KEYPAD_BAND_UP:
            if (keypad->state == KEYPAD_RELEASE) {
                if (!band_lock) {
                    bands_change(true);
                    dialog_send(EVENT_FREQ_UPDATE, NULL);
                }
                dialog_send(EVENT_BAND_UP, NULL);
            }
            break;
            
        case KEYPAD_BAND_DOWN:
            if (keypad->state == KEYPAD_RELEASE) {
                if (!band_lock) {
                    bands_change(false);
                    dialog_send(EVENT_FREQ_UPDATE, NULL);
                }
                dialog_send(EVENT_BAND_DOWN, NULL);
            }
            break;

        case KEYPAD_MODE:
            if (mode_lock) {
                break;
            }
        
            if (keypad->state == KEYPAD_RELEASE) {
                radio_change_mode(RADIO_MODE_NEXT);
            } else if (keypad->state == KEYPAD_LONG) {
                radio_change_mode(RADIO_MODE_SUBSET);
            }

            params_mode_load();
            radio_mode_set();
            info_params_set();
            pannel_visible();

            if (params.mag_info.x) {
                msg_tiny_set_text_fmt("%s", info_params_mode());
            }
            break;
        
        case KEYPAD_FST:
            if (keypad->state == KEYPAD_RELEASE) {
                next_freq_step(true);
            } else if (keypad->state == KEYPAD_LONG) {
                next_freq_step(false);
            }
            break;

        case KEYPAD_ATU:
            if (keypad->state == KEYPAD_RELEASE) {
                radio_change_atu();
                info_params_set();

                if (params.mag_info.x) {
                    msg_tiny_set_text_fmt("ATU: %s", params.atu ? "On" : "Off");
                }
            } else if (keypad->state == KEYPAD_LONG) {
                radio_start_atu();
            }
            break;

        case KEYPAD_F1:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_press(0, false);
            } else if (keypad->state == KEYPAD_LONG) {
                buttons_press(0, true);
            }
            break;

        case KEYPAD_F2:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_press(1, false);
            } else if (keypad->state == KEYPAD_LONG) {
                buttons_press(1, true);
            }
            break;

        case KEYPAD_F3:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_press(2, false);
            } else if (keypad->state == KEYPAD_LONG) {
                buttons_press(2, true);
            }
            break;

        case KEYPAD_F4:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_press(3, false);
            } else if (keypad->state == KEYPAD_LONG) {
                buttons_press(3, true);
            }
            break;

        case KEYPAD_F5:
            if (keypad->state == KEYPAD_RELEASE) {
                buttons_press(4, false);
            } else if (keypad->state == KEYPAD_LONG) {
                buttons_press(4, true);
            }
            break;

        case KEYPAD_GEN:
            if (keypad->state == KEYPAD_RELEASE) {
                apps_disable();
                mfk_set_mode(MFK_MIN_LEVEL);
                buttons_unload_page();
                buttons_load_page(PAGE_VOL_1);
                voice_say_text_fmt("General menu keys");
            } else if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_gen);
            }
            break;

        case KEYPAD_APP:
            if (keypad->state == KEYPAD_RELEASE) {
                apps_disable();
                buttons_unload_page();
                buttons_load_page(PAGE_APP_1);
                voice_say_text_fmt("Application menu keys");
            } else if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_app);
            }
            break;

        case KEYPAD_KEY:
            if (keypad->state == KEYPAD_RELEASE) {
                apps_disable();
                buttons_unload_page();
                buttons_load_page(PAGE_KEY_1);
                voice_say_text_fmt("CW parameters");
            } else if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_key);
            }
            break;

        case KEYPAD_MSG:
            if (keypad->state == KEYPAD_RELEASE) {
                switch (radio_current_mode()) {
                    case radio_mode_cw:
                    case radio_mode_cwr:
                        apps_disable();
                        buttons_unload_page();

                        pannel_hide();
                        dialog_construct(dialog_msg_cw, obj);
                        buttons_load_page(PAGE_MSG_CW_1);
                        voice_say_text_fmt("CW messages window");
                        break;
                        
                    case radio_mode_lsb:
                    case radio_mode_usb:
                    case radio_mode_am:
                    case radio_mode_nfm:
                        apps_disable();
                        buttons_unload_page();

                        pannel_hide();
                        dialog_construct(dialog_msg_voice, obj);
                        buttons_load_page(PAGE_MSG_VOICE_1);
                        voice_say_text_fmt("Voice messages window");
                        break;
                        
                    default:
                        msg_tiny_set_text_fmt("Not used in this mode");
                        break;
                }
            } else if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_msg);
            }
            break;

        case KEYPAD_DFN:
            if (keypad->state == KEYPAD_RELEASE) {
                apps_disable();
                buttons_unload_page();
                buttons_load_page(PAGE_DFN_1);
                voice_say_text_fmt("DNF parameters");
            } else if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_dfn);
            }
            break;

        case KEYPAD_DFL:
            if (keypad->state == KEYPAD_LONG) {
                main_screen_action(params.long_dfl);
            }
            break;

        case KEYPAD_POWER:
            if (keypad->state == KEYPAD_RELEASE) {
                backlight_switch();
            } else if (keypad->state == KEYPAD_LONG) {
                voice_say_text_fmt("Power off");
                msg_set_text_fmt("Power off");
                radio_poweroff();
            }
            break;

        case KEYPAD_PTT:
            switch (keypad->state) {
                case KEYPAD_PRESS:
                    radio_set_ptt(true);

                    switch (radio_current_mode()) {
                        case radio_mode_cw:
                        case radio_mode_cwr:
                            radio_set_morse_key(true);
                            break;
                    }
                    break;
                    
                case KEYPAD_RELEASE:
                case KEYPAD_LONG_RELEASE:
                    switch (radio_current_mode()) {
                        case radio_mode_cw:
                        case radio_mode_cwr:
                            radio_set_morse_key(false);
                            break;
                    }

                    radio_set_ptt(false);
                    break;
            }
            break;

        default:
            LV_LOG_WARN("Unsuported key");
            break;
    }
}

static void main_screen_hkey_cb(lv_event_t * e) {
    event_hkey_t *hkey = lv_event_get_param(e);

    switch (hkey->key) {
        case HKEY_1:
        case HKEY_2:
        case HKEY_3:
        case HKEY_4:
        case HKEY_5:
        case HKEY_6:
        case HKEY_7:
        case HKEY_8:
            if (hkey->state == HKEY_RELEASE) {
                mem_load(hkey->key - HKEY_1 + 1);
                voice_say_text_fmt("Memory %i loaded", hkey->key - HKEY_1 + 1);
            } else if (hkey->state == HKEY_LONG) {
                mem_save(hkey->key - HKEY_1 + 1);
                voice_say_text_fmt("Memory %i stored", hkey->key - HKEY_1 + 1);
            }
            break;
            
        case HKEY_SPCH:
            if (hkey->state == HKEY_RELEASE) {
                freq_lock = !freq_lock;
                freq_update();
                voice_say_text_fmt("Frequency %s", freq_lock ? "locked" : "unlocked");
            }
            break;
            
        case HKEY_TUNER:
            if (hkey->state == HKEY_RELEASE) {
                radio_change_atu();
                info_params_set();
            } else if (hkey->state == HKEY_LONG) {
                radio_start_atu();
            }
            break;

        case HKEY_UP:
            if (hkey->state == HKEY_RELEASE) {
                if (!freq_lock) {
                    freq_shift(+1);
                }
            } else if (hkey->state == HKEY_LONG) {
                if (!band_lock) {
                    bands_change(true);
                    dialog_send(EVENT_FREQ_UPDATE, NULL);
                }
                dialog_send(EVENT_BAND_UP, NULL);
            }
            break;

        case HKEY_DOWN:
            if (hkey->state == HKEY_RELEASE) {
                if (!freq_lock) {
                    freq_shift(-1);
                }
            } else if (hkey->state == HKEY_LONG) {
                if (!band_lock) {
                    bands_change(false);
                    dialog_send(EVENT_FREQ_UPDATE, NULL);
                }
                dialog_send(EVENT_BAND_DOWN, NULL);
            }
            break;
        
        case HKEY_F1:
            if (hkey->state == HKEY_RELEASE) {
                main_screen_action(params.press_f1);
            } else if (hkey->state == HKEY_LONG) {
                main_screen_action(params.long_f1);
            }
            break;

        case HKEY_F2:
            if (hkey->state == HKEY_RELEASE) {
                main_screen_action(params.press_f2);
            } else if (hkey->state == HKEY_LONG) {
                main_screen_action(params.long_f2);
            }
            break;
        
        default:
            break;
    }
}

static void main_screen_radio_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);

    if (params_band.split) {
        freq_update();
    }
    
    lv_event_send(meter, code, NULL);
    lv_event_send(tx_info, code, NULL);
    
    dialog_send(code, NULL);
}

static void main_screen_update_cb(lv_event_t * e) {
    freq_update();
    info_params_set();

    dsp_auto_clear();
}

static void main_screen_atu_update_cb(lv_event_t * e) {
    info_atu_update();
}

static uint16_t freq_accel(uint16_t diff) {
    if (diff < 3) {
        return 1;
    }

    switch (params.freq_accel.x) {
        case FREQ_ACCEL_NONE:
            return 1;
            
        case FREQ_ACCEL_LITE:
            return (diff < 6) ? 5 : 10;
            
        case FREQ_ACCEL_STRONG:
            return (diff < 6) ? 10 : 30;
    }
}

static void freq_shift(int16_t diff) {
    if (freq_lock) {
        return;
    }
    
    uint64_t    prev_freq_rx = radio_current_freq_rx();
    uint64_t    prev_freq_fft = radio_current_freq_fft();
    
    int32_t     df = diff * params_mode.freq_step * freq_accel(abs(diff));

    uint64_t    freq_rx = align_long(prev_freq_rx + df, abs(df));
    uint64_t    freq_fft = align_long(prev_freq_fft + df, abs(df));
    int32_t     freq_delta = freq_rx - freq_fft;
    int32_t     freq_shift = 0;
    int32_t     half = 45000 / params_mode.spectrum_factor;
    
    switch (params.freq_mode.x) {
        case FREQ_MODE_JOIN:
            radio_set_freq_rx(freq_rx);
            radio_set_freq_fft(freq_rx);
            freq_shift = freq_rx - prev_freq_rx;
            lv_msg_send(MSG_FREQ_FFT_SHIFT, &freq_shift);

            band_info_update(freq_rx);

            check_cross_band(freq_rx);
            voice_say_freq(freq_rx);
            break;
            
        case FREQ_MODE_SLIDE:
            if (freq_delta < -half) {
                freq_fft += freq_delta + half - df;
                freq_shift = freq_fft - prev_freq_fft;
            } else if (freq_delta > half) {
                freq_fft += freq_delta - half - df;
                freq_shift = freq_fft - prev_freq_fft;
            } else {
                freq_shift = 0;
            }
            
            if (freq_shift != 0) {
                radio_set_freq_fft(freq_fft);
                lv_msg_send(MSG_FREQ_FFT_SHIFT, &freq_shift);
            }

            radio_set_freq_rx(freq_rx);
            check_cross_band(freq_rx);
            band_info_update(prev_freq_fft);
            voice_say_freq(freq_rx);
            break;

        case FREQ_MODE_RX_ONLY:
            radio_set_freq_rx(freq_rx);
            check_cross_band(freq_rx);
            voice_say_freq(freq_rx);
            break;
            
        case FREQ_MODE_FFT_ONLY:
            radio_set_freq_fft(freq_fft);
            freq_shift = freq_fft - prev_freq_fft;
            lv_msg_send(MSG_FREQ_FFT_SHIFT, &freq_shift);
            band_info_update(freq_fft);
            break;
            
        default:
            break;
    }

    freq_update();
    dialog_send(EVENT_FREQ_UPDATE, NULL);
}

static void main_screen_rotary_cb(lv_event_t * e) {
    int32_t     diff = lv_event_get_param(e);
    
    freq_shift(diff);
    dialog_rotary(diff);
}

static void main_screen_key_cb(lv_event_t * e) {
    uint32_t key = *((uint32_t *)lv_event_get_param(e));

    switch (key) {
        case '-':
            if (!freq_lock) {
                freq_shift(-1);
            }
            break;
            
        case '=':
            if (!freq_lock) {
                freq_shift(+1);
            }
            break;

        case '_':
            next_freq_step(false);
            break;

        case '+':
            next_freq_step(true);
            break;

        case KEY_VOL_LEFT_EDIT:
        case '[':
            vol_update(-1, false);
            break;
            
        case KEY_VOL_RIGHT_EDIT:
        case ']':
            vol_update(+1, false);
            break;

        case KEY_VOL_LEFT_SELECT:
        case '{':
            vol_press(-1);
            break;
            
        case KEY_VOL_RIGHT_SELECT:
        case '}':
            vol_press(+1);
            break;
            
        case KEYBOARD_F9:
            buttons_unload_page();
            buttons_load_page(PAGE_SETTINGS);
            
            dialog_construct(dialog_settings, obj);
            break;
            
        case LV_KEY_LEFT:
            switch (mfk_state) {
                case MFK_STATE_EDIT:
                    mfk_update(-1, false);
                    break;
                    
                case MFK_STATE_SELECT:
                    mfk_press(-1);
                    break;
            }
            break;
            
        case LV_KEY_RIGHT:
            switch (mfk_state) {
                case MFK_STATE_EDIT:
                    mfk_update(+1, false);
                    break;
                    
                case MFK_STATE_SELECT:
                    mfk_press(+1);
                    break;
            }
            break;

        case LV_KEY_ESC:
            if (!dialog_is_run()) {
                switch (vol->mode) {
                    case VOL_EDIT:
                        vol->mode = VOL_SELECT;
                        voice_say_text_fmt("Selection mode");
                        break;
                        
                    case VOL_SELECT:
                        vol->mode = VOL_EDIT;
                        voice_say_text_fmt("Edit mode");
                        break;
                }
                vol_update(0, false);
            }
            break;

        case KEYBOARD_PRINT:
        case KEYBOARD_PRINT_SCR:
            screenshot_take();
            break;
            
        case KEYBOARD_SCRL_LOCK:
            freq_lock = !freq_lock;
            freq_update();
            break;

        case KEYBOARD_PGUP:
            if (!band_lock) {
                bands_change(true);
                dialog_send(EVENT_FREQ_UPDATE, NULL);
            }
            dialog_send(EVENT_BAND_UP, NULL);
            break;

        case KEYBOARD_PGDN:
            if (!band_lock) {
                bands_change(false);
                dialog_send(EVENT_FREQ_UPDATE, NULL);
            }
            dialog_send(EVENT_BAND_DOWN, NULL);
            break;
            
        case HKEY_FINP:
            if (!freq_lock) {
                voice_say_text_fmt("Enter frequency");
                dialog_construct(dialog_freq, obj);
            }
            break;
            
        default:
            break;
    }
}

static void main_screen_pressed_cb(lv_event_t * e) {
    switch (mfk_state) {
        case MFK_STATE_EDIT:
            mfk_state = MFK_STATE_SELECT;
            voice_say_text_fmt("Selection mode");
            break;
            
        case MFK_STATE_SELECT:
            mfk_state = MFK_STATE_EDIT;
            voice_say_text_fmt("Edit mode");
            break;
    }
    mfk_update(0, false);
}

static void keys_enable_cb(lv_timer_t *t) {
    lv_group_add_obj(keyboard_group, obj);
    lv_group_set_editing(keyboard_group, true);
}

void main_screen_keys_enable(bool value) {
    if (value) {
        lv_timer_t *timer = lv_timer_create(keys_enable_cb, 100, NULL);
        lv_timer_set_repeat_count(timer, 1);
    } else {
        lv_group_remove_obj(obj);
        lv_group_set_editing(keyboard_group, false);
    }
}

void main_screen_lock_freq(bool lock) {
    freq_lock = lock;
    freq_update();
}

void main_screen_lock_band(bool lock) {
    band_lock = lock;
}

void main_screen_lock_mode(bool lock) {
    mode_lock = lock;
    info_lock_mode(lock);
}

void main_screen_set_freq(uint64_t freq) {
    if (params_bands_find(freq, &params.freq_band)) {
        if (params.freq_band.type != 0) {
            if (params.freq_band.id != params.band) {
                bands_activate(&params.freq_band, false);
                info_params_set();
                pannel_visible();
            }
        }
    }

    radio_set_freq_rx(freq);
    radio_set_freq_fft(freq);
    event_send(lv_scr_act(), EVENT_SCREEN_UPDATE, NULL);
}

lv_obj_t * main_screen() {
    uint16_t y = 0;

    obj = python_main_screen_get();

    lv_obj_add_event_cb(obj, main_screen_rotary_cb, EVENT_ROTARY, NULL);
    lv_obj_add_event_cb(obj, main_screen_keypad_cb, EVENT_KEYPAD, NULL);
    lv_obj_add_event_cb(obj, main_screen_hkey_cb, EVENT_HKEY, NULL);
    lv_obj_add_event_cb(obj, main_screen_radio_cb, EVENT_RADIO_TX, NULL);
    lv_obj_add_event_cb(obj, main_screen_radio_cb, EVENT_RADIO_RX, NULL);
    lv_obj_add_event_cb(obj, main_screen_update_cb, EVENT_SCREEN_UPDATE, NULL);
    lv_obj_add_event_cb(obj, main_screen_atu_update_cb, EVENT_ATU_UPDATE, NULL);

    lv_obj_add_event_cb(obj, main_screen_key_cb, LV_EVENT_KEY, NULL);
    lv_obj_add_event_cb(obj, main_screen_pressed_cb, LV_EVENT_PRESSED, NULL);

    main_screen_keys_enable(true);
    
    y += spectrum_height;
    
    lv_obj_t *f;

    f = lv_label_create(obj);
    lv_obj_add_style(f, &freq_style, 0);
    lv_obj_set_pos(f, 0, y);
    lv_label_set_recolor(f, true);
    freq[0] = f;

    f = lv_label_create(obj);
    lv_obj_add_style(f, &freq_main_style, 0);
    lv_obj_set_pos(f, 800/2 - 500/2, y);
    lv_label_set_recolor(f, true);
    freq[1] = f;

    f = lv_label_create(obj);
    lv_obj_add_style(f, &freq_style, 0);
    lv_obj_set_pos(f, 800 - 150, y);
    lv_label_set_recolor(f, true);
    freq[2] = f;

    y += freq_height;

    waterfall = waterfall_init(obj);

    lv_obj_set_y(waterfall, y);
    waterfall_set_height(480 - y);
    
    buttons_init(obj);
    buttons_load_page(PAGE_VOL_1);

    pannel_init(obj);
    msg = msg_init(obj);
    msg_tiny = msg_tiny_init(obj);

    clock_init(obj);
    info_init(obj);
    
    meter = meter_init(obj);
    tx_info = tx_info_init(obj);

    
    main_screen_band_changed();
    
    uint64_t freq;
    
    freq = radio_current_freq_rx();
    lv_msg_send(MSG_FREQ_RX_CHANGED, &freq);

    freq = radio_current_freq_fft();
    lv_msg_send(MSG_FREQ_FFT_CHANGED, &freq);

    msg_set_text_fmt("TRX Brass de R1CBU " VERSION);
    msg_set_timeout(2000);
    
    return obj;
}

void main_screen_band_changed() {
    uint64_t freq = freq_update();

    info_params_set();
    pannel_visible();

    band_info_update_range();

    dsp_auto_clear();
}

void main_screen_update_range() {
    params_band.vfo_x[params_band.vfo].freq_fft = params_band.vfo_x[params_band.vfo].freq_rx;
    radio_set_freq_fft(params_band.vfo_x[params_band.vfo].freq_fft);

    band_info_update_range();
    freq_update();
}
