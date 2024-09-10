/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "bands.h"
#include "params.h"
#include "radio.h"
#include "info.h"
#include "waterfall.h"
#include "main_screen.h"
#include "pannel.h"
#include "voice.h"

void bands_activate(band_t *band, bool touch_freq) {
    params_lock();
    
    if (touch_freq) {
        params_band_save();
    }

    params.band = band->id;
    params_band_load(touch_freq);
    params_unlock(&params.durty.band);

    if (touch_freq) {
        radio_set_freq_rx(params_band.freq_rx);
        radio_set_freq_tx(params_band.freq_tx);
        radio_set_freq_fft(params_band.freq_fft);
        band_info_update(params_band.freq_fft);
    }

    radio_mode_set();
    radio_load_atu();
}

void bands_change(bool up) {
    band_t band = { .name = NULL };

    params_band_freq_rx_set(params_band.freq_rx);
    params_band_freq_fft_set(params_band.freq_fft);
    
    if (params_bands_find_next(params_band.freq_rx, up, &band)) {
        bands_activate(&band, true);
        main_screen_band_changed();
            
        voice_say_text_fmt("Band %s", band.name);
    }
}
