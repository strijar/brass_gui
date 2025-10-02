/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdlib.h>
#include "lv_waterfall.h"

/*********************
 *      DEFINES
 *********************/
#define MY_CLASS &lv_waterfall_class

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void lv_waterfall_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_waterfall_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj);

/**********************
 *  STATIC VARIABLES
 **********************/

const lv_obj_class_t lv_waterfall_class  = {
    .constructor_cb = lv_waterfall_constructor,
    .destructor_cb = lv_waterfall_destructor,
    .base_class = &lv_obj_class,
    .instance_size = sizeof(lv_waterfall_t),
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_waterfall_create(lv_obj_t * parent) {
    LV_LOG_INFO("begin");
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);

    return obj;
}

/*=====================
 * Setter functions
 *====================*/

void lv_waterfall_set_grad(lv_obj_t * obj, lv_grad_dsc_t * grad) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    for (int i = 0; i < 256; i++) {
        waterfall->palette[i] = lv_gradient_calculate(grad, 256, i);
    }
}

void lv_waterfall_set_data_size(lv_obj_t * obj, uint16_t size) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_obj_update_layout(obj);

    lv_waterfall_t  *waterfall = (lv_waterfall_t *)obj;
    lv_coord_t      height = lv_obj_get_height(obj);

    waterfall->dsc = lv_img_buf_alloc(size, height, LV_IMG_CF_TRUE_COLOR);
    memset(waterfall->dsc->data, 0, waterfall->dsc->data_size);

    waterfall->line_len = waterfall->dsc->data_size / height;
    waterfall->line_buf = lv_mem_realloc(waterfall->line_buf, waterfall->line_len);

    waterfall->img = lv_img_create(obj);

    lv_obj_align(waterfall->img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(waterfall->img, waterfall->dsc);
    lv_img_cache_invalidate_src(waterfall->dsc);
}

void lv_waterfall_set_max(lv_obj_t * obj, int16_t db) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    waterfall->max = db;
}

void lv_waterfall_set_min(lv_obj_t * obj, int16_t db) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    waterfall->min = db;
}

void lv_waterfall_set_span(lv_obj_t * obj, int32_t hz) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    waterfall->span = hz;
}

void lv_waterfall_clear_data(lv_obj_t * obj) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    memset(waterfall->dsc->data, 0, waterfall->dsc->data_size);
    lv_img_cache_invalidate_src(waterfall->dsc);
}

int32_t lv_waterfall_scroll_data(lv_obj_t * obj, int32_t df) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    uint16_t    div = waterfall->span / lv_obj_get_width(waterfall);
    int16_t     surplus = df % div;

    waterfall->scroll += df / div;

    if (surplus) {
        waterfall->scroll_surplus += surplus;
    } else {
        waterfall->scroll_surplus = 0;
    }

    if (abs(waterfall->scroll_surplus) > div) {
        waterfall->scroll += waterfall->scroll_surplus / div;
        waterfall->scroll_surplus %= div;
    }

    /* Scroll */

    int16_t px = waterfall->scroll;

    if (px) {
        lv_img_dsc_t    *dsc = waterfall->dsc;

        if (abs(px) > dsc->header.w) {
            lv_waterfall_clear_data(obj);
            return 0;
        }

        uint8_t         *ptr = dsc->data;
        uint32_t        line_len = waterfall->line_len;
        uint8_t         *line_buf = waterfall->line_buf;
        uint16_t        offset = abs(px) * 4;
        uint16_t        tail = (dsc->header.w - abs(px)) * 4;

        for (int y = 0; y < dsc->header.h; y++) {
            if (px > 0) {
                memset(line_buf + tail, 0, offset);
                memcpy(line_buf, ptr + offset, tail);
                memcpy(ptr, line_buf, line_len);
            } else {
                memset(line_buf, 0, offset);
                memcpy(line_buf + offset, ptr, tail);
                memcpy(ptr, line_buf, line_len);
            }

            ptr += line_len;
        }

        waterfall->scroll = 0;
    }

    return px * div;
}

void lv_waterfall_add_data(lv_obj_t * obj, float * data, uint16_t cnt) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t  *waterfall = (lv_waterfall_t *)obj;
    lv_img_dsc_t    *dsc = waterfall->dsc;

    if (!dsc || !waterfall->palette) {
        return;
    }

    uint32_t    line_len = waterfall->line_len;
    uint8_t     *ptr = dsc->data + dsc->data_size - line_len * 2;

    /* Scroll down */

    for (uint16_t y = 0; y < dsc->header.h - 1; y++) {
        memcpy(ptr + line_len, ptr, line_len);
        ptr -= line_len;
    }

    /* Paint */

    for (uint32_t x = 0; x < dsc->header.w; x++) {
        uint32_t    index = x * cnt / dsc->header.w;
        float       d = data[index];
        float       v = (d - waterfall->min) / (waterfall->max - waterfall->min);

        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 1.0f) {
            v = 1.0f;
        }

        uint8_t id = v * 255;

        lv_img_buf_set_px_color(dsc, x, 0, waterfall->palette[id]);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_waterfall_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj) {
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    waterfall->img = NULL;
    waterfall->line_len = 0;
    waterfall->line_buf = NULL;
    waterfall->min = -40;
    waterfall->max = 0;
    waterfall->span = 100000;
    waterfall->scroll_surplus = 0;
    waterfall->scroll = 0;

    LV_TRACE_OBJ_CREATE("finished");
}

static void lv_waterfall_destructor(const lv_obj_class_t * class_p, lv_obj_t * obj) {
    LV_UNUSED(class_p);
    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    if (waterfall->palette) lv_mem_free(waterfall->palette);
    if (waterfall->line_buf) lv_mem_free(waterfall->line_buf);
}
