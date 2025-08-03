/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "meter.h"
#include "styles.h"
#include "events.h"
#include "msgs.h"
#include "main.h"

#define NUM_ITEMS   7

static int16_t          min_db = S1;
static int16_t          max_db = S9_40;

static uint8_t          meter_height = 40;
static int16_t          meter_db = S1;
static float            auto_min = S1;

static lv_obj_t         *obj;

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

static void meter_draw_cb(lv_event_t * e) {
    lv_obj_t            *obj = lv_event_get_target(e);
    lv_draw_ctx_t       *draw_ctx = lv_event_get_draw_ctx(e);
    lv_draw_rect_dsc_t  rect_dsc;
    lv_draw_label_dsc_t label_dsc;
    lv_area_t           area;

    lv_coord_t x1 = obj->coords.x1 + 18;
    lv_coord_t y1 = obj->coords.y1;

    lv_coord_t w = lv_obj_get_width(obj);
    lv_coord_t h = lv_obj_get_height(obj);

    uint8_t     slice_db = 3;
    uint8_t     slice = 10;
    lv_coord_t  len = slice * (max_db - min_db) / slice_db;

    /* Rects */

    lv_draw_rect_dsc_init(&rect_dsc);

    rect_dsc.bg_opa = LV_OPA_80;

    uint32_t count = slice_db * slice * (meter_db - min_db) / (max_db - min_db);

    area.y1 = y1;
    area.y2 = area.y1 + h;

    int16_t db = s_items[0].db;

    for (uint16_t i = 0; i < count; i++) {
        if (db <= auto_min) {
            rect_dsc.bg_color = lv_color_hex(0x2E3442);
        } else if (db < S9) {
            rect_dsc.bg_color = lv_color_hex(0x3F526C);
        } else if (db < S9_20) {
            rect_dsc.bg_color = lv_color_hex(0x5D769A);
        } else {
            rect_dsc.bg_color = lv_color_hex(0xFFC940);
        }

        area.x1 = x1 + i * slice;
        area.x2 = area.x1 + slice - 3;

        lv_draw_rect(draw_ctx, &rect_dsc, &area);

        db += slice_db;
    }

    /* Labels */

    lv_draw_label_dsc_init(&label_dsc);

    label_dsc.color = lv_color_white();
    label_dsc.font = font_meter;

    lv_point_t label_size;

    for (uint8_t i = 0; i < NUM_ITEMS; i++) {
        char    *label = s_items[i].label;
        int16_t db = s_items[i].db;

        lv_txt_get_size(&label_size, label, label_dsc.font, 0, 0, LV_COORD_MAX, 0);

        area.x1 = x1 + len * (db  - min_db) / (max_db - min_db) - (label_size.x / 2);
        area.y1 = y1 + h / 2 - label_size.y / 2;
        area.x2 = area.x1 + label_size.x;
        area.y2 = area.y2 + label_size.y;

        lv_draw_label(draw_ctx, &label_dsc, &area, label, NULL);
    }
}

static void meter_msg_cb(lv_event_t * e) {
    lv_msg_t *m = lv_event_get_msg(e);

    switch (lv_msg_get_id(m)) {
        case MSG_SPECTRUM_AUTO: {
            const msgs_auto_t *msg = lv_msg_get_payload(m);

            auto_min = msg->min;
        } break;
    }
}

static void rx_msg_cb(void *s, lv_msg_t *m) {
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

static void tx_msg_cb(void *s, lv_msg_t *m) {
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

lv_obj_t * meter_init(lv_obj_t * parent) {
    obj = lv_obj_create(parent);

    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_style(obj, &meter_style, 0);

    lv_obj_set_height(obj, meter_height);

    lv_obj_add_event_cb(obj, meter_draw_cb, LV_EVENT_DRAW_MAIN_END, NULL);

    lv_obj_add_event_cb(obj, meter_msg_cb, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(MSG_SPECTRUM_AUTO, obj, NULL);
    lv_msg_subsribe(MSG_RX, rx_msg_cb, NULL);
    lv_msg_subsribe(MSG_TX, tx_msg_cb, NULL);

    return obj;
}

void meter_update(int16_t db, float beta) {
    if (db < min_db) {
        db = min_db;
    } else if (db > max_db) {
        db = max_db;
    }

    meter_db = meter_db * beta + db * (1.0f - beta);
    lv_obj_invalidate(obj);
}
