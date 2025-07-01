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
#include "dialog_msg_cw.h"
#include "styles.h"
#include "events.h"
#include "util.h"
#include "pannel.h"
#include "keyboard.h"
#include "textarea_window.h"
#include "cw_encoder.h"
#include "msg.h"
#include "buttons.h"
#include "main_screen.h"
#include "dsp.h"
#include "settings/options.h"

static uint32_t         *ids = NULL;

static lv_obj_t         *table;
static int16_t          table_rows = 0;

static void init();
static void construct_cb(lv_obj_t *parent);
static void destruct_cb();
static void key_cb(lv_event_t * e);
static void send_stop_cb(lv_event_t * e);
static void beacon_stop_cb(lv_event_t * e);

static button_item_t button_send_stop = { .label = "Send\nStop", .press = send_stop_cb };
static button_item_t button_beacon_stop = { .label = "Beacon\nStop", .press = beacon_stop_cb };

static dialog_t             dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = destruct_cb,
    .audio_cb = NULL,
    .buttons = true,
    .key_cb = NULL
};

dialog_t                    *dialog_msg_cw = &dialog;

static void reset() {
    free(ids);

    ids = NULL;
    table_rows = 0;
    lv_table_set_row_cnt(table, 1);
}

static void tx_cb(lv_event_t * e) {
    if (cw_encoder_state() == CW_ENCODER_BEACON_IDLE) {
        cw_encoder_stop();
        buttons_unload_page();
//        buttons_load_page(PAGE_APP_MSG_CW_1);
    }
}

static void construct_cb(lv_obj_t *parent) {
    dialog_init(parent, &dialog);

    lv_obj_add_event_cb(dialog.obj, tx_cb, EVENT_RADIO_TX, NULL); // FIXME

    table = lv_table_create(dialog.obj);

    lv_obj_remove_style(table, NULL, LV_STATE_ANY | LV_PART_MAIN);

    lv_obj_set_size(table, 775, 325);

    lv_table_set_col_cnt(table, 1);
    lv_table_set_col_width(table, 0, 770);

    lv_obj_set_style_border_width(table, 0, LV_PART_ITEMS);

    lv_obj_set_style_bg_opa(table, LV_OPA_TRANSP, LV_PART_ITEMS);
    lv_obj_set_style_text_color(table, lv_color_white(), LV_PART_ITEMS);
    lv_obj_set_style_pad_top(table, 5, LV_PART_ITEMS);
    lv_obj_set_style_pad_bottom(table, 5, LV_PART_ITEMS);
    lv_obj_set_style_pad_left(table, 0, LV_PART_ITEMS);
    lv_obj_set_style_pad_right(table, 0, LV_PART_ITEMS);

    lv_obj_set_style_text_color(table, lv_color_black(), LV_PART_ITEMS | LV_STATE_EDITED);
    lv_obj_set_style_bg_color(table, lv_color_white(), LV_PART_ITEMS | LV_STATE_EDITED);
    lv_obj_set_style_bg_opa(table, 128, LV_PART_ITEMS | LV_STATE_EDITED);

    lv_obj_add_event_cb(table, key_cb, LV_EVENT_KEY, NULL);
    lv_group_add_obj(keyboard_group, table);
    lv_group_set_editing(keyboard_group, true);

    lv_obj_center(table);

    table_rows = 0;
    ids = NULL;

///    params_msg_cw_load();
    main_screen_lock_mode(true);
}

static void destruct_cb() {
    if (!ids) {
        free(ids);
    }

    cw_encoder_stop();
    textarea_window_close();
    main_screen_lock_mode(false);
}

static void key_cb(lv_event_t * e) {
    uint32_t key = *((uint32_t *)lv_event_get_param(e));

    switch (key) {
        case KEYBOARD_F4:
            dialog_msg_cw_edit_cb(e);
            break;

        default:
            dialog_key_cb(e);
            break;
    }
}

static void textarea_window_close_cb() {
    lv_group_add_obj(keyboard_group, table);
    lv_group_set_editing(keyboard_group, true);
}

static void textarea_window_new_ok_cb() {
///    params_msg_cw_new(textarea_window_get());
    textarea_window_close_cb();
}

static void textarea_window_edit_ok_cb() {
    const char *val = textarea_window_get();
    int16_t     row = 0;
    int16_t     col = 0;

    lv_table_get_selected_cell(table, &row, &col);
    lv_table_set_cell_value(table, row, col, val);
///    params_msg_cw_edit(ids[row], val);
    textarea_window_close_cb();
}

static const char* get_msg() {
    if (table_rows == 0) {
        return NULL;
    }

    int16_t     row = 0;
    int16_t     col = 0;

    lv_table_get_selected_cell(table, &row, &col);

    if (row == LV_TABLE_CELL_NONE) {
        return NULL;
    }

    return lv_table_get_cell_value(table, row, col);
}

void dialog_msg_cw_append(uint32_t id, const char *val) {
    ids = realloc(ids, sizeof(uint32_t) * (table_rows + 1));

    ids[table_rows] = id;
    lv_table_set_cell_value(table, table_rows, 0, val);

    table_rows++;
}

void dialog_msg_cw_send_cb(lv_event_t * e) {
    const char *msg = get_msg();

    cw_encoder_send(msg, false);
    buttons_unload_page();
    buttons_load(1, &button_send_stop);
}

static void send_stop_cb(lv_event_t * e) {
    cw_encoder_stop();
    buttons_unload_page();
//    buttons_load_page(PAGE_APP_MSG_CW_1);
}

void dialog_msg_cw_beacon_cb(lv_event_t * e) {
    const char *msg = get_msg();

    cw_encoder_send(msg, true);
    buttons_unload_page();
    buttons_load(2, &button_beacon_stop);
}

static void beacon_stop_cb(lv_event_t * e) {
    cw_encoder_stop();
    buttons_unload_page();
//    buttons_load_page(PAGE_APP_MSG_CW_1);
}

void dialog_msg_cw_period_cb(lv_event_t * e) {
    switch (options->msg.cw_period) {
        case 10:
            options->msg.cw_period = 30;
            break;

        case 30:
            options->msg.cw_period = 60;
            break;

        case 60:
            options->msg.cw_period = 120;
            break;

        case 120:
            options->msg.cw_period = 10;
            break;
    }

    msg_set_text_fmt("Beacon period: %i s", options->msg.cw_period);
}

void dialog_msg_cw_new_cb(lv_event_t * e) {
    lv_group_remove_obj(table);
    textarea_window_open(textarea_window_new_ok_cb, textarea_window_close_cb);
}

void dialog_msg_cw_edit_cb(lv_event_t * e) {
    const char *msg = get_msg();

    if (msg) {
        lv_group_remove_obj(table);
        textarea_window_open(textarea_window_edit_ok_cb, textarea_window_close_cb);
        textarea_window_set(msg);
    }
}

void dialog_msg_cw_delete_cb(lv_event_t * e) {
    if (table_rows == 0) {
        return;
    }

    int16_t     row = 0;
    int16_t     col = 0;

    lv_table_get_selected_cell(table, &row, &col);

    if (row != LV_TABLE_CELL_NONE) {
///        params_msg_cw_delete(ids[row]);
        reset();
///        params_msg_cw_load();
    }
}
