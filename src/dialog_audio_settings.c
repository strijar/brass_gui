/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "dialog.h"
#include "dialog_settings.h"
#include "styles.h"
#include "params.h"
#include "events.h"
#include "keyboard.h"
#include "dsp.h"
#include "mic.h"
#include "settings/options.h"

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
static void key_cb(lv_event_t * e);
static void equalizer_speaker_update_cb(lv_event_t * e);
static void equalizer_mic_update_cb(lv_event_t * e);

typedef enum {
    EQ_SPEAKER = 0,
    EQ_MIC
} eq_sel_t;

static const char           *eq_name[] = { "Speaker", "Mic" };
static const lv_event_cb_t  eq_update[] = { equalizer_speaker_update_cb, equalizer_mic_update_cb };

static lv_obj_t     *grid;

static dialog_t     dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = NULL,
    .audio_cb = NULL,
    .key_cb = key_cb
};

dialog_t            *dialog_audio_settings = &dialog;

/* Equalizer item */

static void equalizer_speaker_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    int16_t         *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    dsp_update_equalizer();
}

static void equalizer_mic_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    int16_t         *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    mic_update_equalizer();
}

static uint8_t make_equalizer_item(uint8_t row, eq_sel_t sel, uint8_t n, equalizer_item_t *item) {
    lv_obj_t        *obj;
    uint8_t         col = 0;

    /* Label */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text_fmt(obj, "%s EQ %i", eq_name[sel], n + 1);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    /* Freq */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, item->freq);

    switch (n) {
        case 0:
            lv_spinbox_set_range(obj, 50, 800);
            lv_spinbox_set_digit_format(obj, 3, 0);
            break;
        case 1:
            lv_spinbox_set_range(obj, 800, 1600);
            lv_spinbox_set_digit_format(obj, 4, 0);
            break;
        case 2:
            lv_spinbox_set_range(obj, 1600, 3200);
            lv_spinbox_set_digit_format(obj, 4, 0);
            break;
    }

    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, eq_update[sel], LV_EVENT_VALUE_CHANGED, &item->freq);

    /* Width */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, item->q);
    lv_spinbox_set_range(obj, 1, 9);
    lv_spinbox_set_digit_format(obj, 1, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, eq_update[sel], LV_EVENT_VALUE_CHANGED, &item->q);

    /* Gain */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, item->gain);
    lv_spinbox_set_range(obj, -24, 12);
    lv_spinbox_set_digit_format(obj, 2, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, eq_update[sel], LV_EVENT_VALUE_CHANGED, &item->gain);

    return row + 1;
}

/* Mic filter */

static void mic_filter_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    uint16_t        *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    mic_update_filter();
}

static uint8_t make_mic_filter(uint8_t row) {
    lv_obj_t        *obj;
    uint8_t         col = 0;
    filter_t        *filter = &options->audio.mic.filter;

    /* Label */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text_fmt(obj, "Mic filter");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col++, 1, LV_GRID_ALIGN_CENTER, row, 1);

    /* Low */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, filter->low);
    lv_spinbox_set_range(obj, 50, 800);
    lv_spinbox_set_digit_format(obj, 3, 0);

    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->low);

    /* High */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, filter->high);
    lv_spinbox_set_range(obj, 2000, 3200);
    lv_spinbox_set_digit_format(obj, 4, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->high);

    /* Transition */

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);

    lv_spinbox_set_value(obj, filter->transition);
    lv_spinbox_set_range(obj, 50, 200);
    lv_spinbox_set_digit_format(obj, 3, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_2, 56);

    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, col, 2, LV_GRID_ALIGN_CENTER, row, 1);   col += 2;
    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->transition);

    return row + 1;
}

/* * */

static uint8_t make_delimiter(uint8_t row) {
    row_dsc[row] = 10;

    return row + 1;
}

static void construct_cb(lv_obj_t *parent) {
    dialog.obj = dialog_init(parent);

    grid = lv_obj_create(dialog.obj);

    lv_obj_set_layout(grid, LV_LAYOUT_GRID);

    lv_obj_set_size(grid, 780, 330);
    lv_obj_set_style_text_color(grid, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(grid, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_column(grid, SMALL_PAD, 0);
    lv_obj_set_style_pad_row(grid, 5, 0);

    lv_obj_center(grid);

    uint8_t row = 1;

    /* * */

    for (uint8_t i = 0; i < EQUALIZER_NUM; i++) {
        row = make_equalizer_item(row, EQ_SPEAKER, i, &options->audio.speaker.eq[i]);
    }

    row = make_delimiter(row);

    for (uint8_t i = 0; i < EQUALIZER_NUM; i++) {
        row = make_equalizer_item(row, EQ_MIC, i, &options->audio.mic.eq[i]);
    }

    row = make_delimiter(row);
    row = make_mic_filter(row);

    row_dsc[row] = LV_GRID_TEMPLATE_LAST;
    lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);
}

static void key_cb(lv_event_t * e) {
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
