/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdlib.h>
#include <string.h>
#include "lv_waterfall.h"
#include "lvgl/src/core/lv_obj_class_private.h"
#include "lvgl/src/core/lv_obj_private.h"
#include "lvgl/src/misc/cache/instance/lv_image_cache.h"

struct lv_waterfall_t {
    lv_obj_t        obj;

    lv_obj_t        *img;
    lv_draw_buf_t   *draw_buf;

    uint32_t        line_len;
    uint8_t         *line_buf;

    lv_color_t      palette[256];

    int16_t         min;
    int16_t         max;
    int32_t         span;
    int16_t         scroll_surplus;
    int32_t         scroll;
};

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

    if (grad == NULL || grad->stops_count == 0) return;

    uint8_t stop = 0;
    for (uint16_t i = 0; i < 256; i++) {
        if (i <= grad->stops[0].frac) {
            waterfall->palette[i] = grad->stops[0].color;
            continue;
        }
        while (stop + 1 < grad->stops_count && i > grad->stops[stop + 1].frac) stop++;

        if (stop + 1 == grad->stops_count) {
            waterfall->palette[i] = grad->stops[stop].color;
        } else {
            const lv_grad_stop_t *from = &grad->stops[stop];
            const lv_grad_stop_t *to = &grad->stops[stop + 1];
            uint8_t range = to->frac - from->frac;
            uint8_t mix = range == 0 ? 255 : (uint8_t) (((i - from->frac) * 255U) / range);
            waterfall->palette[i] = lv_color_mix(to->color, from->color, mix);
        }
    }
}

void lv_waterfall_set_data_size(lv_obj_t * obj, uint16_t size) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_obj_update_layout(obj);

    lv_waterfall_t  *waterfall = (lv_waterfall_t *)obj;
    lv_coord_t      height = lv_obj_get_height(obj);

    if (waterfall->img != NULL) {
        lv_obj_delete(waterfall->img);
        waterfall->img = NULL;
    }
    if (waterfall->draw_buf != NULL) lv_draw_buf_destroy(waterfall->draw_buf);

    waterfall->draw_buf = lv_draw_buf_create(size, height, LV_COLOR_FORMAT_XRGB8888, 0);
    if (waterfall->draw_buf == NULL) return;
    memset(waterfall->draw_buf->data, 0, waterfall->draw_buf->data_size);

    waterfall->line_len = waterfall->draw_buf->header.stride;
    waterfall->line_buf = lv_realloc(waterfall->line_buf, waterfall->line_len);

    waterfall->img = lv_image_create(obj);

    lv_obj_align(waterfall->img, LV_ALIGN_CENTER, 0, 0);
    lv_image_set_src(waterfall->img, waterfall->draw_buf);
    lv_image_cache_drop(waterfall->draw_buf);
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

    if (waterfall->draw_buf == NULL) return;
    memset(waterfall->draw_buf->data, 0, waterfall->draw_buf->data_size);
    lv_image_cache_drop(waterfall->draw_buf);
    lv_obj_invalidate(waterfall->img);
}

int32_t lv_waterfall_scroll_data(lv_obj_t * obj, int32_t df) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    uint16_t    div = waterfall->span / lv_obj_get_width(obj);
    if (div == 0 || waterfall->draw_buf == NULL) return 0;
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
        lv_draw_buf_t   *dsc = waterfall->draw_buf;

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
        lv_draw_buf_flush_cache(dsc, NULL);
        lv_image_cache_drop(dsc);
        lv_obj_invalidate(waterfall->img);
    }

    return px * div;
}

void lv_waterfall_add_data(lv_obj_t * obj, float * data, uint16_t cnt) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_waterfall_t  *waterfall = (lv_waterfall_t *)obj;
    lv_draw_buf_t   *dsc = waterfall->draw_buf;

    if (dsc == NULL || waterfall->max == waterfall->min) return;

    uint32_t    line_len = waterfall->line_len;
    uint8_t     *ptr = dsc->data + (dsc->header.h - 2) * line_len;

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

        ((uint32_t *) dsc->data)[x] = lv_color_to_u32(waterfall->palette[id]);
    }

    lv_draw_buf_flush_cache(dsc, NULL);
    lv_image_cache_drop(dsc);
    lv_obj_invalidate(waterfall->img);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_waterfall_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj) {
    LV_UNUSED(class_p);
    LV_TRACE_OBJ_CREATE("begin");

    lv_waterfall_t * waterfall = (lv_waterfall_t *)obj;

    waterfall->img = NULL;
    waterfall->draw_buf = NULL;
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

    if (waterfall->draw_buf) lv_draw_buf_destroy(waterfall->draw_buf);
    if (waterfall->line_buf) lv_free(waterfall->line_buf);
}
