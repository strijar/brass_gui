/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "dialog.h"
#include "dialog_freq.h"
#include "styles.h"
#include "dsp.h"
#include "events.h"
#include "util.h"
#include "keyboard.h"
#include "bands/bands.h"
#include "pannel.h"
#include "main_screen.h"
#include "msg.h"

static lv_obj_t *text;

static void construct_cb(lv_obj_t *parent);
static void key_cb(lv_event_t * e);

static dialog_t             dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = NULL,
    .audio_cb = NULL,
    .buttons = true,
    .key_cb = key_cb
};

dialog_t                    *dialog_freq = &dialog;

static void construct_cb(lv_obj_t *parent) {
    lv_obj_t *obj = lv_obj_create(parent);

    lv_obj_remove_style_all(obj);

    lv_obj_add_style(obj, &msg_tiny_style, 0);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    dialog.obj = obj;

    text = lv_textarea_create(dialog.obj);

    lv_obj_remove_style(text, NULL, LV_STATE_ANY | LV_PART_MAIN);

    lv_obj_set_style_text_color(text, lv_color_white(), 0);
    lv_obj_set_style_bg_color(text, lv_color_white(), LV_PART_CURSOR);
    lv_obj_set_style_bg_opa(text, 255, LV_PART_CURSOR);

    lv_textarea_set_one_line(text, true);
    lv_textarea_set_accepted_chars(text, "0123456789.");
    lv_textarea_set_max_length(text, 9);
    lv_textarea_set_placeholder_text(text, "Freq in MHz");

    lv_obj_clear_flag(text, LV_OBJ_FLAG_SCROLLABLE);

    lv_group_add_obj(keyboard_group, text);
    lv_obj_add_event_cb(text, key_cb, LV_EVENT_KEY, NULL);

    lv_obj_set_x(text, 0);
    lv_obj_set_y(text, 0);
    lv_obj_set_height(text, 60);
    lv_obj_set_width(text, 250);
    lv_obj_center(text);
}

static void enter_freq() {
    const char* str = lv_textarea_get_text(text);

    if (strlen(str) == 0) {
        voice_say_text_fmt("Frequency window has been closed");
        return;
    }

    uint64_t    f = atof(str) * 1000000L;

    if ((f > 500000 && f < 62000000) || (f > 144000000 && f < 146000000) || (f > 430000000 && f < 440000000)) {
        main_screen_set_freq(f);
        voice_say_text_fmt("Frequency has been set %s", str);
    } else {
        msg_set_text_fmt("Incorrect freq");
        voice_say_text_fmt("Incorrect frequency");
    }
}

static void key_cb(lv_event_t * e) {
    uint32_t key = *((uint32_t *)lv_event_get_param(e));

    switch (key) {
        case '0' ... '9':
            voice_delay_say_text_fmt("%c", (char) key);
            break;

        case '.':
            voice_delay_say_text_fmt("point");
            break;

        case LV_KEY_BACKSPACE:
            voice_delay_say_text_fmt("backspace");
            break;

        case LV_KEY_ESC:
            voice_say_text_fmt("Frequency window has been closed");
            dialog_destruct();
            break;

        case HKEY_FINP:
        case LV_KEY_ENTER:
            enter_freq();
            dialog_destruct();
            break;

        default:
            dialog_key_cb(e);
            break;
    }
}
