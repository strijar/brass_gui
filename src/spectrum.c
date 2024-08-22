/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <pthread.h>

#include "styles.h"
#include "spectrum.h"
#include "radio.h"
#include "events.h"
#include "dsp.h"
#include "params.h"
#include "util.h"
#include "meter.h"
#include "rtty.h"
#include "recorder.h"
#include "msgs.h"
#include "widgets/lv_spectrum.h"
#include "widgets/lv_finder.h"

float                   spectrum_auto_min;
float                   spectrum_auto_max;

static lv_obj_t         *obj;
static lv_obj_t         *finder;

static int32_t          width_hz = 100000;
static uint16_t         spectrum_size = 800;

static int16_t          delta_surplus = 0;

static void tx_cb(lv_event_t * e) {
}

static void rx_cb(lv_event_t * e) {
}

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

lv_obj_t * spectrum_init(lv_obj_t * parent) {
    obj = lv_spectrum_create(parent);

    lv_obj_add_style(obj, &spectrum_style, LV_PART_MAIN);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_set_style_line_width(obj, 2, LV_PART_INDICATOR);
    lv_obj_set_style_line_color(obj, lv_color_hex(0xAAAAAA), LV_PART_INDICATOR);

    lv_obj_set_style_line_width(obj, 1, LV_PART_TICKS);
    lv_obj_set_style_line_color(obj, lv_color_hex(0x555555), LV_PART_TICKS);

    lv_obj_add_event_cb(obj, tx_cb, EVENT_RADIO_TX, NULL);
    lv_obj_add_event_cb(obj, rx_cb, EVENT_RADIO_RX, NULL);

    lv_spectrum_set_size(obj, 800, 480 / 3);
    lv_spectrum_clear_data(obj);

    /* Finder */

    finder = lv_finder_create(obj);
    
    lv_finder_set_cursor(finder, 1, 0);
    lv_obj_set_y(finder, 60);

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

void spectrum_data(float *data_buf, uint16_t size) {
    lv_spectrum_add_data(obj, data_buf);
    lv_spectrum_set_min(obj, spectrum_auto_min + 3.0f);
    lv_spectrum_set_max(obj, spectrum_auto_max + 10.0f);
    event_send(obj, LV_EVENT_REFRESH, NULL);
}

void spectrum_set_max(int db) {
    lv_spectrum_set_max(obj, db);
}

void spectrum_set_min(int db) {
    lv_spectrum_set_min(obj, db);
}

void spectrum_clear() {
    lv_spectrum_clear_data(obj);
}

void spectrum_change_freq(int16_t df) {
    uint16_t    div = width_hz / spectrum_size / params_mode.spectrum_factor;
    int16_t     surplus = df % div;
    int32_t     delta = df / div;

    if (surplus) {
        delta_surplus += surplus;
    } else {
        delta_surplus = 0;
    }

    if (abs(delta_surplus) > div) {
        delta += delta_surplus / div;
        delta_surplus = delta_surplus % div;
    }

    if (delta == 0) {
        return;
    }

    lv_spectrum_scroll_data(obj, delta);
}

void spectrum_update_range() {
    width_hz = 100000 / params_mode.spectrum_factor;
    spectrum_clear();
}
