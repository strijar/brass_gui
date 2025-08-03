/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

/*********************
 *      INCLUDES
 *********************/

#include <stdlib.h>
#include "lv_smeter.h"

/*********************
 *      DEFINES
 *********************/

#define MY_CLASS    &lv_smeter_class
#define NUM_ITEMS   7

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void lv_smeter_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj);
static void lv_smeter_event(const lv_obj_class_t * class_p, lv_event_t * e);

/**********************
 *  STATIC VARIABLES
 **********************/

typedef struct {
    char    *label;
    int16_t db;
} s_item_t;

static s_item_t s_items[NUM_ITEMS] = {
    { .label = "S1",    .db = S1 },
    { .label = "3",     .db = S3 },
    { .label = "5",     .db = S5 },
    { .label = "7",     .db = S7 },
    { .label = "9",     .db = S9 },
    { .label = "+20",   .db = S9_20 },
    { .label = "+40",   .db = S9_40 }
};

const lv_obj_class_t lv_smeter_class  = {
    .constructor_cb = lv_smeter_constructor,
    .base_class = &lv_obj_class,
    .event_cb = lv_smeter_event,
    .instance_size = sizeof(lv_smeter_t),
};

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * lv_smeter_create(lv_obj_t * parent) {
    lv_obj_t * obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);

    return obj;
}

/*=====================
 * Setter functions
 *====================*/

void lv_smeter_set_value(lv_obj_t * obj, int16_t db) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_smeter_t * meter = (lv_smeter_t *)obj;

    meter->value = db;
    lv_obj_invalidate(obj);
}

void lv_smeter_set_part(lv_obj_t * obj, uint8_t index, int16_t db) {
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_smeter_t * meter = (lv_smeter_t *)obj;

    meter->part[index] = db;
    lv_obj_invalidate(obj);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void lv_smeter_constructor(const lv_obj_class_t * class_p, lv_obj_t * obj) {
    LV_UNUSED(class_p);

    lv_smeter_t * meter = (lv_smeter_t *)obj;

    meter->value = S_MIN;
    meter->slice_db = 3;
    meter->slice_width = 10;
    meter->slice_pad = 3;

    meter->min = S1;
    meter->max = S9_40;

    meter->part[0] = S_MIN;
    meter->part[1] = S9;
    meter->part[2] = S9_20;
}

static void lv_smeter_event(const lv_obj_class_t * class_p, lv_event_t * e) {
    LV_UNUSED(class_p);

    lv_res_t res = lv_obj_event_base(MY_CLASS, e);

    if (res != LV_RES_OK) return;

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t        *obj = lv_event_get_target(e);

    if (code == LV_EVENT_DRAW_MAIN_END) {
        lv_smeter_t         *meter = (lv_smeter_t *) obj;
        lv_draw_ctx_t       *draw_ctx = lv_event_get_draw_ctx(e);
        lv_draw_rect_dsc_t  rect_dsc;
        lv_draw_label_dsc_t label_dsc;
        lv_area_t           area;

        lv_coord_t  x1 = obj->coords.x1 + 18;
        lv_coord_t  y1 = obj->coords.y1;

        lv_coord_t  w = lv_obj_get_width(obj);
        lv_coord_t  h = lv_obj_get_height(obj);

        lv_coord_t  len = meter->slice_width * (meter->max - meter->min) / meter->slice_db;

        /* Rects */

        area.x1 = x1;
        area.y1 = y1;
        area.y2 = area.y1 + h;

        int16_t db = s_items[0].db;

        lv_draw_rect_dsc_init(&rect_dsc);

        while (db <= meter->value) {
            if (db <= meter->part[0]) {
                lv_obj_init_draw_rect_dsc(obj, LV_PART_METER_1, &rect_dsc);
            } else if (db < meter->part[1]) {
                lv_obj_init_draw_rect_dsc(obj, LV_PART_METER_2, &rect_dsc);
            } else if (db < meter->part[2]) {
                lv_obj_init_draw_rect_dsc(obj, LV_PART_METER_3, &rect_dsc);
            } else {
                lv_obj_init_draw_rect_dsc(obj, LV_PART_METER_4, &rect_dsc);
            }

            area.x2 = area.x1 + meter->slice_width - meter->slice_pad;

            lv_draw_rect(draw_ctx, &rect_dsc, &area);

            db += meter->slice_db;
            area.x1 += meter->slice_width;
        }

        /* Labels */

        lv_obj_init_draw_label_dsc(obj, LV_PART_MAIN, &label_dsc);

        lv_point_t label_size;

        for (uint8_t i = 0; i < NUM_ITEMS; i++) {
            char    *label = s_items[i].label;
            int16_t db = s_items[i].db;

            lv_txt_get_size(&label_size, label, label_dsc.font, 0, 0, LV_COORD_MAX, 0);

            area.x1 = x1 + len * (db - meter->min) / (meter->max - meter->min) - (label_size.x / 2);
            area.y1 = y1 + h / 2 - label_size.y / 2;
            area.x2 = area.x1 + label_size.x;
            area.y2 = area.y2 + label_size.y;

            lv_draw_label(draw_ctx, &label_dsc, &area, label, NULL);
        }
    }
}
