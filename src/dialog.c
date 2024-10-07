/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "dialog.h"
#include "styles.h"
#include "main_screen.h"
#include "keyboard.h"
#include "events.h"
#include "main.h"

static lv_obj_t     *obj;
static dialog_t     *current_dialog = NULL;

void dialog_construct(dialog_t *dialog, lv_obj_t *parent) {
    if (dialog && !dialog->run) {
        main_screen_keys_enable(false);
        dialog->construct_cb(parent);
        
        dialog->run = true;
    }

    current_dialog = dialog;    
}

void dialog_destruct() {
    if (current_dialog && current_dialog->run) {
        current_dialog->run = false;

        main_screen_keys_enable(true);
        main_screen_dialog_deleted_cb();
        
        if (current_dialog->destruct_cb) {
            current_dialog->destruct_cb();
        }

        if (current_dialog->obj) {
            lv_obj_del(current_dialog->obj);
            current_dialog->obj = NULL;
        }

        current_dialog = NULL;
    }
}

void dialog_send(lv_event_code_t event_code, void *param) {
    if (dialog_is_run()) {
        lv_obj_send_event(current_dialog->obj, event_code, param);
    }
}

bool dialog_is_run() {
    return (current_dialog != NULL) && current_dialog->run;
}

lv_obj_t * dialog_init(lv_obj_t *parent) {
    obj = lv_obj_create(parent);

    lv_obj_remove_style_all(obj);
    lv_obj_add_style(obj, &dialog_style, 0);

    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    return obj;
}

void dialog_item(dialog_t *dialog, lv_obj_t *obj) {
    lv_obj_add_style(obj, &dialog_item_style, LV_STATE_DEFAULT);
    lv_obj_add_style(obj, &dialog_item_focus_style, LV_STATE_FOCUSED);
    lv_obj_add_style(obj, &dialog_item_edited_style, LV_STATE_EDITED);

    lv_obj_set_style_bg_opa(obj, LV_OPA_TRANSP, LV_PART_CURSOR);
    lv_obj_set_style_text_color(obj, lv_color_white(), LV_PART_CURSOR);
    lv_obj_set_style_text_color(obj, lv_color_black(), LV_PART_CURSOR | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(obj, 128, LV_PART_CURSOR | LV_STATE_EDITED);

    lv_obj_set_style_border_width(obj, 2, LV_STATE_FOCUS_KEY | LV_PART_INDICATOR);
    lv_obj_set_style_border_color(obj, lv_color_white(), LV_STATE_FOCUS_KEY | LV_PART_INDICATOR);

    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    
    lv_group_add_obj(keyboard_group, obj);
    
    if (dialog->key_cb) {
        lv_obj_add_event_cb(obj, dialog->key_cb, LV_EVENT_KEY, NULL);
    }
}

void dialog_audio_samples(float complex *samples, size_t n) {
    if (dialog_is_run() && current_dialog->audio_cb) {
        current_dialog->audio_cb(samples, n);
    }
}

void dialog_rotary(int32_t diff) {
    if (dialog_is_run() && current_dialog->rotary_cb) {
        current_dialog->rotary_cb(diff);
    }
}
