/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "info.h"
#include "styles.h"
#include "params.h"
#include "dsp/agc.h"
#include "settings/modes.h"

typedef enum {
    INFO_SPLIT = 0,
    INFO_MODE,
    INFO_AGC,
    INFO_PRE,
    INFO_ATT,
    INFO_ATU
} info_items_t;

static lv_obj_t     *obj;
static lv_obj_t     *items[6];

static bool         mode_lock = false;

lv_obj_t * info_init(lv_obj_t * parent) {
    obj = lv_obj_create(parent);

    lv_obj_add_style(obj, &info_style, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_left(obj, 0, 0);
    
    uint8_t index = 0;
    
    for (uint8_t y = 0; y < 2; y++)
        for (uint8_t x = 0; x < 3; x++) {
            lv_obj_t *item = lv_label_create(obj);
            
            lv_obj_add_style(item, &info_item_style, 0);
            lv_obj_set_pos(item, x * 58 + 15, y * 24 + 5);
            lv_obj_set_style_text_align(item, LV_TEXT_ALIGN_CENTER, 0);
            
            lv_obj_set_style_text_color(item, lv_color_white(), 0);
            lv_obj_set_size(item, 56, 22);

            items[index] = item;
            index++;
        }

    lv_label_set_text(items[INFO_PRE], "PRE");
    lv_label_set_text(items[INFO_ATT], "ATT");
   
    info_params_set(); 
    return obj;
}

void info_atu_update() {
    lv_label_set_text_fmt(items[INFO_ATU], "ATU%i", params.ant);

    if (!params.atu) {
        lv_obj_set_style_text_color(items[INFO_ATU], lv_color_white(), 0);
        lv_obj_set_style_bg_color(items[INFO_ATU], lv_color_black(), 0);
        lv_obj_set_style_bg_opa(items[INFO_ATU], LV_OPA_0, 0);
    } else {
        if (op_work->shift) {
            lv_obj_set_style_text_color(items[INFO_ATU], lv_color_hex(0xAAAAAA), 0);
            lv_obj_set_style_bg_opa(items[INFO_ATU], LV_OPA_20, 0);
        } else {
            lv_obj_set_style_text_color(items[INFO_ATU], params.atu_loaded ? lv_color_black() : lv_color_hex(0xFF0000), 0);
            lv_obj_set_style_bg_opa(items[INFO_ATU], LV_OPA_50, 0);
        }
        lv_obj_set_style_bg_color(items[INFO_ATU], lv_color_white(), 0);
    }
}

const char* info_params_split() {
    char            *str;

    switch (op_work->split) {
        case SPLIT_NONE:
            str = "RX/TX";
            break;

        case SPLIT_RX:
            str = "RX";
            break;

        case SPLIT_TX:
            str = "TX";
            break;

        default:
            str = "?";
            break;
    }

    return str;
}

const char* info_params_mode() {
    radio_mode_t    mode = op_work->mode;
    char            *str;

    switch (mode) {
        case RADIO_MODE_LSB:
            str = "LSB";
            break;

        case RADIO_MODE_USB:
            str = "USB";
            break;

        case RADIO_MODE_CW:
            str = "CW";
            break;

        case RADIO_MODE_CWR:
            str = "CW-R";
            break;

        case RADIO_MODE_AM:
            str = "AM";
            break;

        case RADIO_MODE_NFM:
            str = "NFM";
            break;

        case RADIO_MODE_RTTY:
            str = "RTTY";
            break;

        case RADIO_MODE_OLIVIA:
            str = "OLIV";
            break;

        default:
            str = "?";
            break;
    }

    return str;
}

const char* info_params_agc() {
    char        *str;

    switch (op_mode->agc) {
        case AGC_OFF:
            str = "OFF";
            break;

        case AGC_LONG:
            str = "LONG";
            break;

        case AGC_SLOW:
            str = "SLOW";
            break;

        case AGC_MED:
            str = "MED";
            break;

        case AGC_FAST:
            str = "FAST";
            break;

        case AGC_CUSTOM:
            str = "CUST";
            break;

        default:
            str = "?";
            break;
    }

    return str;
}

bool info_params_att() {
    return op_work->att == radio_att_on;
}

bool info_params_pre() {
    return op_work->pre == radio_pre_on;
}

void info_params_set() {
    lv_label_set_text(items[INFO_SPLIT], info_params_split());
    lv_label_set_text(items[INFO_MODE], info_params_mode());
    lv_label_set_text(items[INFO_AGC], info_params_agc());

    if (mode_lock) {
        lv_obj_set_style_text_color(items[INFO_MODE], lv_color_hex(0xAAAAAA), 0);
    } else {
        lv_obj_set_style_text_color(items[INFO_MODE], lv_color_white(), 0);
    }

    if (info_params_att()) {
        lv_obj_set_style_text_color(items[INFO_ATT], lv_color_black(), 0);
        lv_obj_set_style_bg_color(items[INFO_ATT], lv_color_white(), 0);
        lv_obj_set_style_bg_opa(items[INFO_ATT], LV_OPA_50, 0);
    } else {
        lv_obj_set_style_text_color(items[INFO_ATT], lv_color_white(), 0);
        lv_obj_set_style_bg_color(items[INFO_ATT], lv_color_black(), 0);
        lv_obj_set_style_bg_opa(items[INFO_ATT], LV_OPA_0, 0);
    }

    if (info_params_pre()) {
        lv_obj_set_style_text_color(items[INFO_PRE], lv_color_black(), 0);
        lv_obj_set_style_bg_color(items[INFO_PRE], lv_color_white(), 0);
        lv_obj_set_style_bg_opa(items[INFO_PRE], LV_OPA_50, 0);
    } else {
        lv_obj_set_style_text_color(items[INFO_PRE], lv_color_white(), 0);
        lv_obj_set_style_bg_color(items[INFO_PRE], lv_color_black(), 0);
        lv_obj_set_style_bg_opa(items[INFO_PRE], LV_OPA_0, 0);
    }

    info_atu_update();
}

void info_lock_mode(bool lock) {
    mode_lock = lock;
    info_params_set();
}
