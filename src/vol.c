/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "vol.h"
#include "msg.h"
#include "radio.h"
#include "main.h"
#include "params.h"
#include "voice.h"
#include "dsp.h"
#include "info.h"
#include "settings/options.h"

static vol_mode_t   vol_mode = VOL_VOL;

void vol_update(int16_t diff, bool voice) {
    int32_t     i;
    float       f;
    char        *str;
    bool        b;

    uint32_t    color = vol->mode == VOL_EDIT ? 0xFFFFFF : 0xBBBBBB;

    switch (vol_mode) {
        case VOL_VOL:
            i = dsp_change_vol(diff);
            msg_set_text_fmt("#%3X Volume: %i", color, i);
            
            if (diff) {
                voice_say_int("Audio level", i);
            } else if (voice) {
                voice_say_text_fmt("Audio level");
            }
            break;
            
        case VOL_PWR:
            f = radio_change_pwr(diff);
            msg_set_text_fmt("#%3X Power: %0.1f W", color, f);

            if (diff) {
                voice_say_float("Transmit power", f);
            } else if (voice) {
                voice_say_text_fmt("Transmit power");
            }
            break;

        case VOL_VOICE_LANG:
            str = voice_change(diff);
            msg_set_text_fmt("#%3X Voice: %s", color, str);

            if (diff) {
                voice_say_lang();
            } else if (voice) {
                voice_say_text_fmt("Voice selector");
            }
            break;

        case VOL_VOICE_RATE:
            i = params_uint8_change(&params.voice_rate, diff);
            msg_set_text_fmt("#%3X Voice rate: %i", color, i);
            
            if (diff == 0 && voice) {
                voice_say_text_fmt(params.voice_rate.voice);
            }
            break;

        case VOL_VOICE_PITCH:
            i = params_uint8_change(&params.voice_pitch, diff);
            msg_set_text_fmt("#%3X Voice pitch: %i", color, i);

            if (diff == 0 && voice) {
                voice_say_text_fmt(params.voice_pitch.voice);
            }
            break;

        case VOL_VOICE_VOLUME:
            i = params_uint8_change(&params.voice_volume, diff);
            msg_set_text_fmt("#%3X Voice volume: %i", color, i);

            if (diff == 0 && voice) {
                voice_say_text_fmt(params.voice_volume.voice);
            }
            break;

        case VOL_FREQ_MODE:
            i = params_uint8_change(&params.freq_mode, diff);
            
            switch (i) {
                case FREQ_MODE_JOIN:
                    str = "join";
                    break;

                case FREQ_MODE_SLIDE:
                    str = "slide";
                    break;
                    
                case FREQ_MODE_RX_ONLY:
                    str = "RX only";
                    break;
                    
                case FREQ_MODE_FFT_ONLY:
                    str = "spectrum only";
                    break;
            }
            
            msg_set_text_fmt("#%3X Freq mode: %s", color, str);

            if (diff) {
                voice_say_text("Frequency mode", str);
            } else if (voice) {
                voice_say_text_fmt("Frequency mode");
            }
            break;

        case VOL_SPLIT:
            i = radio_change_split(diff);
            
            switch (i) {
                case SPLIT_NONE:
                    str = "RX/TX";
                    break;
                    
                case SPLIT_RX:
                    str = "RX";
                    break;
                    
                case SPLIT_TX:
                    str = "TX";
                    break;
            }
            msg_set_text_fmt("#%3X Split: %s", color, str);

            if (diff) {
                info_params_set();
                voice_say_text("Split mode", str);
            } else if (voice) {
                voice_say_text_fmt("Split mode selector");
            }
            break;
            
        default:
            break;
    }
}

void vol_press(int16_t dir) {
    while (true) {
        if (dir > 0) {
            if (vol_mode == VOL_LAST-1) {
                vol_mode = 0;
            } else {
                vol_mode++;
            }
        } else {
            if (vol_mode == 0) {
                vol_mode = VOL_LAST-1;
            } else {
                vol_mode--;
            }
        }

        if (options->control.vol & (1 << vol_mode)) {
            break;
        }
    }

    vol_update(0, true);
}

void vol_set_mode(vol_mode_t mode) {
    vol_mode = mode;
}
