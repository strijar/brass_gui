/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include "styles.h"
#include "finder.h"
#include "radio.h"
#include "params.h"
#include "widgets/lv_finder.h"

lv_obj_t         *spectrum_finder;
lv_obj_t         *waterfall_finder;

void finder_init(lv_obj_t * spectrum, lv_obj_t * waterfall) {
    spectrum_finder = lv_finder_create(spectrum);
    
    lv_finder_set_cursor(spectrum_finder, 1, 0);
    lv_obj_set_y(spectrum_finder, 40);

    lv_obj_add_style(spectrum_finder, &rx_finder_style, LV_PART_MAIN);

    lv_obj_set_style_bg_color(spectrum_finder, bg_color, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(spectrum_finder, LV_OPA_50, LV_PART_INDICATOR);

    lv_obj_set_style_line_width(spectrum_finder, 1, LV_PART_INDICATOR);
    lv_obj_set_style_line_color(spectrum_finder, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_line_opa(spectrum_finder, LV_OPA_50, LV_PART_INDICATOR);

    /* * */

    waterfall_finder = lv_finder_create(waterfall);
    
    lv_finder_set_cursor(waterfall_finder, 1, 0);

    lv_obj_add_style(waterfall_finder, &rx_finder_style, LV_PART_MAIN);

    lv_obj_set_style_bg_color(waterfall_finder, bg_color, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(waterfall_finder, LV_OPA_50, LV_PART_INDICATOR);

    lv_obj_set_style_line_width(waterfall_finder, 1, LV_PART_INDICATOR);
    lv_obj_set_style_line_color(waterfall_finder, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_line_opa(waterfall_finder, LV_OPA_50, LV_PART_INDICATOR);

    /* * */
    
    finder_mode_changed();
}

void finder_mode_changed() {
    int32_t from, to;

    radio_filter_get(&from, &to);

    lv_finder_set_offsets(spectrum_finder, from, to);
    lv_finder_set_offsets(waterfall_finder, from, to);
}

void finder_set_range(uint64_t min_freq, uint64_t max_freq) {
    lv_finder_set_range(spectrum_finder, min_freq, max_freq);
    lv_finder_set_range(waterfall_finder, min_freq, max_freq);

    lv_obj_invalidate(spectrum_finder);
    lv_obj_invalidate(waterfall_finder);
}

void finder_set_rx(uint64_t freq) {
    lv_finder_set_value(spectrum_finder, freq);
    lv_finder_set_value(waterfall_finder, freq);

    lv_obj_invalidate(spectrum_finder);
    lv_obj_invalidate(waterfall_finder);
}

void finder_update_rx() {
    uint64_t freq = params_band.vfo_x[params_band.vfo].freq_rx;

    lv_finder_set_value(spectrum_finder, freq);
    lv_finder_set_value(waterfall_finder, freq);

    lv_obj_invalidate(spectrum_finder);
    lv_obj_invalidate(waterfall_finder);
}

void finder_update_range() {
    uint64_t freq = params_band.vfo_x[params_band.vfo].freq_fft;
    uint32_t half = 50000 / params_mode.spectrum_factor;

    lv_finder_set_range(spectrum_finder, freq - half, freq + half);
    lv_finder_set_range(waterfall_finder, freq - half, freq + half);

    lv_obj_invalidate(spectrum_finder);
    lv_obj_invalidate(waterfall_finder);
}
