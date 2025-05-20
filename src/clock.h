/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include "lvgl/lvgl.h"
#include "settings/options.h"

lv_obj_t * clock_init(lv_obj_t * parent);
void clock_update_power(float ext, float bat, uint8_t cap);

void clock_set_view(clock_view_t x);
void clock_set_time_timeout(uint8_t sec);
void clock_set_power_timeout(uint8_t sec);
void clock_set_tx_timeout(uint8_t sec);
