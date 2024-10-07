/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */
 
#include <stdio.h>

#include "tx_info.h"
#include "styles.h"
#include "events.h"
#include "msg_tiny.h"
#include "params.h"
#include "main.h"

#define NUM_PWR_ITEMS   6
#define NUM_VSWR_ITEMS  5

static const float      min_pwr = 0.0f;
static const float      max_pwr = 10.0f;

static const float      min_swr = 1.0f;
static const float      max_swr = 5.0f;

static float            pwr = 10.0f;
static float            vswr = 5.0f;
static float            alc;

static lv_obj_t         *obj;
static lv_grad_dsc_t    grad;

typedef struct {
    char    *label;
    float   val;
} item_t;

static item_t pwr_items[NUM_PWR_ITEMS] = {
    { .label = "PWR",   .val = 0.0f },
    { .label = "2",     .val = 2.0f },
    { .label = "4",     .val = 4.0f },
    { .label = "6",     .val = 6.0f },
    { .label = "8",     .val = 8.0f },
    { .label = "10",    .val = 10.0f }
};

static item_t vswr_items[NUM_VSWR_ITEMS] = {
    { .label = "SWR",   .val = 1.0f },
    { .label = "2",     .val = 2.0f },
    { .label = "3",     .val = 3.0f },
    { .label = "4",     .val = 4.0f },
    { .label = ">5",    .val = 5.0f }
};

static void tx_info_draw_cb(lv_event_t * e) {
    lv_obj_t            *obj = lv_event_get_target(e);
    lv_layer_t          *layer = lv_event_get_layer(e);
    lv_draw_rect_dsc_t  rect_dsc;
    lv_draw_label_dsc_t label_dsc;
    lv_area_t           area;
    lv_point_t          label_size;
    uint32_t            count;
    
    lv_coord_t x1 = lv_obj_get_x(obj) + 7;
    lv_coord_t y1 = lv_obj_get_y(obj) + 17;

    lv_coord_t w = lv_obj_get_width(obj);
    lv_coord_t h = lv_obj_get_height(obj) - 1;

    uint8_t     slice = 10;
    lv_coord_t  len = 300;

    /* PWR rects */

    lv_draw_rect_dsc_init(&rect_dsc);

    rect_dsc.bg_opa = LV_OPA_80;
    
    count = len * (pwr - min_pwr) / (max_pwr - min_pwr) / slice;

    area.y1 = y1 - slice / 2;
    area.y2 = y1 + 32;

    for (uint16_t i = 0; i < count; i++) {
        rect_dsc.bg_color = lv_color_hex(0xAAAAAA);
        
        area.x1 = x1 + 30 + i * slice;
        area.x2 = area.x1 + slice - 3;

        lv_draw_rect(layer, &rect_dsc, &area);
    }

    /* SWR rects */

    lv_draw_rect_dsc_init(&rect_dsc);

    rect_dsc.bg_opa = LV_OPA_80;
    
    count = len * (vswr - min_swr) / (max_swr - min_swr) / slice;

    area.y1 = y1 - slice / 2 + 54;
    area.y2 = y1 + 32 + 54;

    for (uint16_t i = 0; i < count; i++) {
        float s = i * (max_swr - min_swr) / (len / slice) + min_swr;
    
        if (s <= 2.0f) {
            rect_dsc.bg_color = lv_color_hex(0xAAAAAA);
        } else if (s <= 3.0f) {
            rect_dsc.bg_color = lv_color_hex(0xAAAA00);
        } else {
            rect_dsc.bg_color = lv_color_hex(0xAA0000);
        }
        
        area.x1 = x1 + 30 + i * slice;
        area.x2 = area.x1 + slice - 3;

        lv_draw_rect(layer, &rect_dsc, &area);
    }

    /* PWR Labels */
    
    lv_draw_label_dsc_init(&label_dsc);
    
    label_dsc.color = lv_color_white();
    label_dsc.font = font_tx_info;

    area.x1 = x1;
    area.x2 = x1 + 20;

    area.y1 = y1 + 5;
    area.y2 = area.y1 + 18;
    
    for (uint8_t i = 0; i < NUM_PWR_ITEMS; i++) {
        char    *label = pwr_items[i].label;
        float   val = pwr_items[i].val;

        lv_txt_get_size(&label_size, label, label_dsc.font, 0, 0, LV_COORD_MAX, 0);

        area.x1 = x1 + 30 + len * (val - min_pwr) / (max_pwr - min_pwr) - (label_size.x / 2);
        area.x2 = area.x1 + label_size.x;

        label_dsc.text = label;

        lv_draw_label(layer, &label_dsc, &area);
    }

    /* SWR Labels */

    area.x1 = x1;
    area.x2 = x1 + 20;

    area.y1 = y1 + 60;
    area.y2 = y1 + 32 + 60;

    for (uint8_t i = 0; i < NUM_VSWR_ITEMS; i++) {
        char    *label = vswr_items[i].label;
        float   val = vswr_items[i].val;

        lv_txt_get_size(&label_size, label, label_dsc.font, 0, 0, LV_COORD_MAX, 0);

        area.x1 = x1 + 30 + len * (val - min_swr) / (max_swr - min_swr) - (label_size.x / 2);
        area.x2 = area.x1 + label_size.x;
        label_dsc.text = label;

        lv_draw_label(layer, &label_dsc, &area);
    }

}

static void tx_cb(lv_event_t * e) {
    pwr = 0;
    vswr = 0;
    alc = 0;

    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(obj);
}

static void rx_cb(lv_event_t * e) {
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

lv_obj_t * tx_info_init(lv_obj_t *parent) {
    obj = lv_obj_create(parent);

    lv_obj_add_style(obj, &tx_info_style, 0);
    
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(obj, tx_cb, EVENT_RADIO_TX, NULL);
    lv_obj_add_event_cb(obj, rx_cb, EVENT_RADIO_RX, NULL);
    lv_obj_add_event_cb(obj, tx_info_draw_cb, LV_EVENT_DRAW_MAIN_END, NULL);

    grad.dir = LV_GRAD_DIR_VER;
    grad.stops_count = 4;

    grad.stops[0].color = lv_color_lighten(bg_color, 200);
    grad.stops[1].color = bg_color;
    grad.stops[2].color = bg_color;
    grad.stops[3].color = lv_color_darken(bg_color, 200);
    
    grad.stops[0].frac  = 0;
    grad.stops[1].frac  = 128 - 10;
    grad.stops[2].frac  = 128 + 10;
    grad.stops[3].frac  = 255;
   
    return obj;
}

void tx_info_update(float p, float s, float a) {
    pwr = p;
    alc = alc * 0.9f + (10.0f - a) * 0.1f;

    if (s <= max_swr) {
        vswr = s;
    } else {
        vswr = max_swr;
    }

    lv_obj_invalidate(obj);
    
    if (params.mag_alc.x) {
        msg_tiny_set_text_fmt("ALC: %.1f", alc);
    }
}
