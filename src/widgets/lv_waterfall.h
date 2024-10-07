/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#ifndef LV_WATERFALL_H
#define LV_WATERFALL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_waterfall_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

void lv_waterfall_set_palette(lv_obj_t * obj, lv_color_t * palette, uint16_t cnt);
void lv_waterfall_set_size(lv_obj_t * obj, lv_coord_t w, lv_coord_t h);

void lv_waterfall_clear_data(lv_obj_t * obj);
void lv_waterfall_add_data(lv_obj_t * obj, float * data, uint16_t cnt);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
