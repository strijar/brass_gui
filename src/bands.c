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
#include "spectrum.h"
#include "waterfall.h"
#include "main_screen.h"
#include "pannel.h"
#include "voice.h"

void bands_activate(band_t *band, uint64_t *freq) {
    params_lock();
    params_band_save();
    params.band = band->id;
    params_band_load();
    params_unlock(&params.durty.band);

    if (freq) {
        params_band_freq_set(*freq);
    }

    radio_set_freq_rx(params_band.vfo_x[params_band.vfo].freq_rx);
    radio_set_freq_fft(params_band.vfo_x[params_band.vfo].freq_rx); // ???

    radio_mode_set();
    radio_load_atu();

    spectrum_mode_changed();
    spectrum_band_changed();
    waterfall_band_changed();
}

void bands_change(bool up) {
    band_t band = { .name = NULL };
    
    if (params_bands_find_next(params_band.vfo_x[params_band.vfo].freq_rx, up, &band)) {
        bands_activate(&band, NULL);
        main_screen_band_changed();
            
        voice_say_text_fmt("Band %s", band.name);
    }
}
