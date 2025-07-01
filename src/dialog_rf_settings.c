/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "dialog.h"
#include "dialog_settings.h"
#include "styles.h"
#include "events.h"
#include "keyboard.h"
#include "dsp.h"
#include "settings/rf.h"
#include "hw/pa_bias.h"

#define SMALL_PAD   5

#define SMALL_1     57
#define SMALL_2     (SMALL_1 * 2 + SMALL_PAD * 1)
#define SMALL_3     (SMALL_1 * 3 + SMALL_PAD * 2)
#define SMALL_4     (SMALL_1 * 4 + SMALL_PAD * 3)
#define SMALL_5     (SMALL_1 * 5 + SMALL_PAD * 4)
#define SMALL_6     (SMALL_1 * 6 + SMALL_PAD * 5)

#define SMALL_WIDTH 57

static lv_coord_t   col_dsc[] = { 740 - (SMALL_1 + SMALL_PAD) * 6, SMALL_1, SMALL_1, SMALL_1, SMALL_1, SMALL_1, SMALL_1, LV_GRID_TEMPLATE_LAST };
static lv_coord_t   row_dsc[64] = { 1 };

static void construct_cb(lv_obj_t *parent);
static void destruct_cb();

static lv_obj_t     *grid;

static dialog_t     dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = destruct_cb,
    .audio_cb = NULL,
    .buttons = false,
    .key_cb = dialog_key_cb
};

dialog_t            *dialog_rf_settings = &dialog;

static void destruct_cb() {
    settings_rf_save();
}

/* Mode */

static void mode_update_cb(lv_event_t * e) {
    lv_obj_t *obj = lv_event_get_target(e);

    rf->mode = lv_dropdown_get_selected(obj);
}

static uint8_t make_mode(uint8_t row) {
    lv_obj_t    *obj;
    uint8_t     col = 0;

    /* Label */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "TX Mode");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    /* * */

    obj = lv_dropdown_create(grid);

    dialog_item(&dialog, obj);

    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    lv_obj_center(obj);

    lv_obj_t *list = lv_dropdown_get_list(obj);
    lv_obj_add_style(list, &dialog_dropdown_list_style, 0);

    lv_dropdown_set_options(obj, " Normal \n Two Tone \n Silence");
    lv_dropdown_set_symbol(obj, NULL);
    lv_dropdown_set_selected(obj, rf->mode);
    lv_obj_add_event_cb(obj, mode_update_cb, LV_EVENT_VALUE_CHANGED, NULL);

    return row + 1;
}


/* PA Bias item */

static void pa_bias_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    uint16_t        *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    pa_bias_update();
}

static uint8_t make_pa_bias(uint8_t row) {
    lv_obj_t    *obj;
    uint8_t     col = 0;

    /* Label */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "PA Bias");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    for (int i = 0; i < 2; i++) {
        obj = lv_spinbox_create(grid);

        dialog_item(&dialog, obj);

        lv_spinbox_set_value(obj, rf->pa_bias[i]);
        lv_spinbox_set_range(obj, 0, 255);
        lv_spinbox_set_digit_format(obj, 3, 0);
        lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
        lv_obj_set_size(obj, SMALL_3, 56);

        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 3, LV_GRID_ALIGN_CENTER, row, 1);   col += 3;
        lv_obj_add_event_cb(obj, pa_bias_update_cb, LV_EVENT_VALUE_CHANGED, &rf->pa_bias[i]);
    }

    return row + 1;
}

/* TX Band */

static void tx_band_freq_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    tx_band_item_t  *item = lv_event_get_user_data(e);

    item->to = lv_spinbox_get_value(obj) * 1000;
}

static void tx_band_vref_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    tx_band_item_t  *item = lv_event_get_user_data(e);

    item->vref = lv_spinbox_get_value(obj);
}

static uint8_t make_tx_band(uint8_t row) {
    lv_obj_t    *obj;

    for (int i = 0; i < rf->tx_band_count; i++) {
        uint8_t         col = 0;
        tx_band_item_t  *item = &rf->tx_band[i];

        /* Label */

        row_dsc[row] = 54;

        obj = lv_label_create(grid);

        lv_label_set_text_fmt(obj, "TX band LPF:%i", item->lpf + 1);
        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

        /* Freq */

        obj = lv_spinbox_create(grid);

        dialog_item(&dialog, obj);

        lv_spinbox_set_value(obj, item->to / 1000);
        lv_spinbox_set_range(obj, 0, 62000);
        lv_spinbox_set_digit_format(obj, 6, 3);
        lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
        lv_obj_set_size(obj, SMALL_3, 56);

        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 3, LV_GRID_ALIGN_CENTER, row, 1);   col += 3;
        lv_obj_add_event_cb(obj, tx_band_freq_update_cb, LV_EVENT_VALUE_CHANGED, item);

        /* VRef */

        obj = lv_spinbox_create(grid);

        dialog_item(&dialog, obj);

        lv_spinbox_set_value(obj, item->vref);
        lv_spinbox_set_range(obj, 0, 4095);
        lv_spinbox_set_digit_format(obj, 4, 0);
        lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
        lv_obj_set_size(obj, SMALL_3, 56);

        lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 3, LV_GRID_ALIGN_CENTER, row, 1);   col += 3;
        lv_obj_add_event_cb(obj, tx_band_vref_update_cb, LV_EVENT_VALUE_CHANGED, item);

        row++;
    }

    return row + 1;
}


/* * */

static uint8_t make_delimiter(uint8_t row) {
    row_dsc[row] = 10;

    return row + 1;
}

static void construct_cb(lv_obj_t *parent) {
    dialog_init(parent, &dialog);

    grid = lv_obj_create(dialog.obj);

    lv_obj_set_layout(grid, LV_LAYOUT_GRID);

    lv_obj_set_size(grid, 780, 330 + 68);
    lv_obj_set_style_text_color(grid, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(grid, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(grid, SMALL_PAD, 0);
    lv_obj_set_style_pad_row(grid, 5, 0);

    lv_obj_center(grid);

    uint8_t row = 1;

    row = make_mode(row);
    row = make_delimiter(row);

    row = make_pa_bias(row);
    row = make_delimiter(row);

    row = make_tx_band(row);
    row = make_delimiter(row);

    row_dsc[row] = LV_GRID_TEMPLATE_LAST;
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
}
