/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <unistd.h>
#include <stdint.h>

#include "lvgl/lvgl.h"

extern float waterfall_auto_min;
extern float waterfall_auto_max;

lv_obj_t * waterfall_init(lv_obj_t * parent);
void waterfall_set_height(lv_coord_t h);
void waterfall_update_band(uint64_t f);

/* From thread */

void waterfall_data(float *data_buf, size_t size);
