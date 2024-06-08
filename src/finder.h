/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include "lvgl/lvgl.h"

extern lv_obj_t *spectrum_finder;
extern lv_obj_t *waterfall_finder;

void finder_init(lv_obj_t * spectrum, lv_obj_t * waterfall);

void finder_mode_changed();
void finder_set_range(uint64_t min_freq, uint64_t max_freq);
void finder_set_rx(uint64_t freq);
void finder_update_rx();
void finder_update_range();
