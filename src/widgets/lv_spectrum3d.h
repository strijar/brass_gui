/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#ifndef LV_SPECTRUM3D_H
#define LV_SPECTRUM3D_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_obj_t            obj;

    uint16_t            depth;
    uint16_t            data_size;
    uint8_t             *data_buf;
    uint8_t             *line_buf;
    lv_coord_t          *top_buf;

    lv_color_t          palette[256];

    int16_t             min;
    int16_t             max;
    int32_t             span;
    int16_t             scroll_surplus;
    int32_t             scroll;
} lv_spectrum3d_t;

extern const lv_obj_class_t lv_spectrum3d_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * lv_spectrum3d_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

void lv_spectrum3d_set_grad(lv_obj_t * obj, lv_grad_dsc_t * grad);

void lv_spectrum3d_set_data_size(lv_obj_t * obj, uint16_t size, uint16_t depth);
void lv_spectrum3d_set_max(lv_obj_t * obj, int16_t db);
void lv_spectrum3d_set_min(lv_obj_t * obj, int16_t db);
void lv_spectrum3d_set_span(lv_obj_t * obj, int32_t hz);

void lv_spectrum3d_clear_data(lv_obj_t * obj);
void lv_spectrum3d_scroll_data(lv_obj_t * obj, int32_t df);
void lv_spectrum3d_add_data(lv_obj_t * obj, float * data, uint16_t cnt);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
