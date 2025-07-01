/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "dialog.h"
#include "styles.h"
#include "main_screen.h"
#include "keyboard.h"
#include "events.h"
#include "main.h"
#include "buttons.h"

static lv_obj_t     *obj;
static dialog_t     *current_dialog = NULL;

void dialog_construct(dialog_t *dialog, lv_obj_t *parent) {
    if (dialog && !dialog->run) {
        main_screen_keys_enable(false);
        dialog->construct_cb(parent);

        if (!dialog->buttons) {
            buttons_visible(false);
        }

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

        if (!current_dialog->buttons) {
            buttons_visible(true);
        }

        current_dialog = NULL;
    }
}

void dialog_send(lv_event_code_t event_code, void *param) {
    if (dialog_is_run()) {
        lv_event_send(current_dialog->obj, event_code, param);
    }
}

bool dialog_keypad(event_keypad_t *keypad) {
    if (dialog_is_run() && current_dialog->keypad_cb) {
        return current_dialog->keypad_cb(keypad);
    }

    return false;
}

bool dialog_modulate_state() {
    if (dialog_is_run() && current_dialog->modulate_state_cb) {
        return current_dialog->modulate_state_cb();
    }

    return false;
}

size_t dialog_modulate(float complex *data, size_t max_size, radio_mode_t mode) {
    if (current_dialog->modulate_cb) {
        return current_dialog->modulate_cb(data, max_size, mode);
    }

    return 0;
}

void dialog_bands_change(bool up) {
    if (dialog_is_run() && current_dialog->bands_change_cb) {
        current_dialog->bands_change_cb(up);
    }
}

bool dialog_is_run() {
    return (current_dialog != NULL) && current_dialog->run;
}

void dialog_init(lv_obj_t *parent, dialog_t *dialog) {
    obj = lv_obj_create(parent);

    lv_obj_remove_style_all(obj);
    lv_obj_add_style(obj, &dialog_style, 0);

    if (!dialog->buttons) {
        lv_obj_add_style(obj, &dialog_no_buttons_style, 0);
    }

    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    dialog->obj = obj;
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

void dialog_key_cb(lv_event_t * e) {
    uint32_t    key = *((uint32_t *)lv_event_get_param(e));

    switch (key) {
        case HKEY_FINP:
             lv_group_set_editing(keyboard_group, !lv_group_get_editing((const lv_group_t*) keyboard_group));
             break;

        case LV_KEY_ESC:
            dialog_destruct();
            break;

        case KEY_VOL_LEFT_EDIT:
        case KEY_VOL_LEFT_SELECT:
            dsp_change_vol(-1);
            break;

        case KEY_VOL_RIGHT_EDIT:
        case KEY_VOL_RIGHT_SELECT:
            dsp_change_vol(1);
            break;
    }
}
