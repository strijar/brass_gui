/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>

#include "waterfall.h"
#include "styles.h"
#include "radio.h"
#include "events.h"
#include "params.h"
#include "bands.h"
#include "band_info.h"
#include "meter.h"
#include "backlight.h"
#include "dsp.h"
#include "fpga/fft.h"
#include "msgs.h"

#define PX_BYTES    4

float                   waterfall_auto_min;
float                   waterfall_auto_max;

static lv_obj_t         *obj;
static lv_obj_t         *img;
static lv_obj_t         *finder;

static lv_coord_t       width;
static lv_coord_t       height;
static int32_t          width_hz = 100000;
static size_t           line_len;
static uint8_t          *line_buf = NULL;

static int              grid_min = -70;
static int              grid_max = -40;

static lv_img_dsc_t     *frame;
static lv_color_t       palette[256];
static int32_t          scroll_hor = 0;
static int32_t          scroll_hor_surplus = 0;

static void finder_event_cb(lv_event_t * e) {
    lv_obj_t *finder = lv_event_get_target(e);
    lv_msg_t *m = lv_event_get_msg(e);
    
    switch (lv_msg_get_id(m)) {
        case MSG_FILTER_CHANGED: {
            int32_t from, to;

            radio_filter_get(&from, &to);
            lv_finder_set_offsets(finder, from, to);
            lv_obj_invalidate(finder);
        } break;
        
        case MSG_FREQ_RX_CHANGED: {
            const uint64_t *freq = lv_msg_get_payload(m);
            
            lv_finder_set_value(finder, *freq);
            lv_obj_invalidate(finder);
        } break;

        case MSG_FREQ_FFT_CHANGED: {
            const uint64_t  *freq = lv_msg_get_payload(m);
            uint32_t        half = 50000 / params_mode.spectrum_factor;

            lv_finder_set_range(finder, *freq - half, *freq + half);
            lv_obj_invalidate(finder);
        } break;
        
        default:
            break;
    }
}

lv_obj_t * waterfall_init(lv_obj_t * parent) {
    obj = lv_obj_create(parent);
    
    lv_obj_add_style(obj, &waterfall_style, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    /* Finder */

    finder = lv_finder_create(obj);
    
    lv_finder_set_cursor(finder, 1, 0);

    lv_obj_add_style(finder, &rx_finder_style, LV_PART_MAIN);

    lv_obj_set_style_bg_color(finder, bg_color, LV_PART_INDICATOR);
    lv_obj_set_style_bg_opa(finder, LV_OPA_50, LV_PART_INDICATOR);

    lv_obj_set_style_line_width(finder, 1, LV_PART_INDICATOR);
    lv_obj_set_style_line_color(finder, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_line_opa(finder, LV_OPA_50, LV_PART_INDICATOR);

    lv_obj_add_event_cb(finder, finder_event_cb, LV_EVENT_MSG_RECEIVED, NULL);
    lv_msg_subsribe_obj(MSG_FILTER_CHANGED, finder, NULL);
    lv_msg_subsribe_obj(MSG_FREQ_RX_CHANGED, finder, NULL);
    lv_msg_subsribe_obj(MSG_FREQ_FFT_CHANGED, finder, NULL);


    return obj;
}

static void scroll_down() {
    uint8_t     *ptr = frame->data + frame->data_size - line_len * 2;

    for (int y = 0; y < height-1; y++) {
        memcpy(ptr + line_len, ptr, line_len);
        ptr -= line_len;
    }
}

static void scroll_right(int16_t px) {
    uint8_t     *ptr = frame->data;
    uint16_t    offset = px * PX_BYTES;
    uint16_t    tail = (width - px) * PX_BYTES;
    
    for (int y = 0; y < height; y++) {
        memset(line_buf + tail, 0, offset);
        memcpy(line_buf, ptr + offset, tail);
        memcpy(ptr, line_buf, line_len);
        
        ptr += line_len;
    }
}

static void scroll_left(int16_t px) {
    uint8_t     *ptr = frame->data;
    uint16_t    offset = px * PX_BYTES;
    uint16_t    tail = (width - px) * PX_BYTES;
    
    for (int y = 0; y < height; y++) {
        memset(line_buf, 0, offset);
        memcpy(line_buf + offset, ptr, tail);
        memcpy(ptr, line_buf, line_len);
        
        ptr += line_len;
    }
}

void waterfall_data(float *data_buf, size_t size) {
    if (scroll_hor) {
        return;
    }

    scroll_down();

    float min = params.waterfall_auto_min.x ? waterfall_auto_min + 3.0f : grid_min;
    float max = params.waterfall_auto_max.x ? waterfall_auto_max + 3.0f : grid_max;

    for (size_t x = 0; x < width; x++) {
        float       v = (data_buf[x] - min) / (max - min);
        
        if (v < 0.0f) {
            v = 0.0f;
        } else if (v > 1.0f) {
            v = 1.0f;
        }
        
        uint8_t id = v * 255;
        
        lv_img_buf_set_px_color(frame, x, 0, palette[id]);
    }
    
    event_send(img, LV_EVENT_REFRESH, NULL);
}

static void do_scroll_cb(lv_event_t * event) {
    if (scroll_hor == 0) {
        return;
    }

    int16_t px = (abs(scroll_hor) / 4) + 1;

    if (scroll_hor > 0) {
        scroll_right(px);
        scroll_hor -= px;
    } else {
        scroll_left(px);
        scroll_hor += px;
    }
    
    event_send(img, LV_EVENT_REFRESH, NULL);
}

void waterfall_set_height(lv_coord_t h) {
    lv_obj_set_height(obj, h);
    lv_obj_update_layout(obj);

    lv_obj_set_height(finder, h - 62);
    lv_obj_update_layout(finder);

    width = 2047;
    height = lv_obj_get_height(obj);

    frame = lv_img_buf_alloc(width, height, LV_IMG_CF_TRUE_COLOR);
    
    if (!frame) {
        LV_LOG_ERROR("Frame alloc");
    }

    line_len = frame->data_size / frame->header.h;
    line_buf = malloc(line_len);
    
    if (!line_buf) {
        LV_LOG_ERROR("Line buf alloc");
    }
    
    styles_waterfall_palette(palette, 256);

    img = lv_img_create(obj);

    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_src(img, frame);
    lv_obj_add_event_cb(img, do_scroll_cb, LV_EVENT_DRAW_POST, NULL);

    lv_obj_move_foreground(finder);
    band_info_init(obj);
}

void waterfall_clear() {
    memset(frame->data, 0, frame->data_size);
    scroll_hor = 0;
    scroll_hor_surplus = 0;
}

void waterfall_change_max(int16_t d) {
    int16_t x = params_band.grid_max + d;

    if (x > S9_40) {
        x = S9_40;
    } else if (x < S8) {
        x = S8;
    }

    params_lock();
    params_band.grid_max = x;
    params_unlock(&params_band.durty.grid_max);

    grid_max = x;
}

void waterfall_change_min(int16_t d) {
    int16_t x = params_band.grid_min + d;

    if (x > S7) {
        x = S7;
    } else if (x < S_MIN) {
        x = S_MIN;
    }

    params_lock();
    params_band.grid_min = x;
    params_unlock(&params_band.durty.grid_min);

    grid_min = x;
}

void waterfall_change_freq(int16_t df) {
    uint16_t    div = width_hz / 800;
    int16_t     surplus = df % div;

    scroll_hor += df / div;
    
    if (surplus) {
        scroll_hor_surplus += surplus;
    } else {
        scroll_hor_surplus = 0;
    }
    
    if (abs(scroll_hor_surplus) > div) {
        scroll_hor += scroll_hor_surplus / div;
        scroll_hor_surplus = scroll_hor_surplus % div;
    }

    if (scroll_hor) {
        lv_obj_invalidate(img);
    }
}

void waterfall_update_range() {
    width_hz = 100000 / params_mode.spectrum_factor;
    waterfall_clear();
}
