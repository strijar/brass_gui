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
    .buttons = false,
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

/* NR */

static void nr_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    uint16_t        *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    dsp_update_denoise();
}

static uint8_t nr_item(uint8_t row, const char *label, int16_t *data, int16_t min, int16_t max) {
    lv_obj_t    *obj;

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, label);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);
    lv_spinbox_set_value(obj, *data);
    lv_spinbox_set_range(obj, min, max);
    lv_obj_add_event_cb(obj, nr_update_cb, LV_EVENT_VALUE_CHANGED, data);

    lv_spinbox_set_digit_format(obj, 2, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);

    return row + 1;
}

static void nr_scaling_type_cb(lv_event_t * e) {
    lv_obj_t *obj = lv_event_get_target(e);

    options->audio.denoise.nr.noise_scaling_type = lv_dropdown_get_selected(obj);

    dsp_update_denoise();
}

static uint8_t make_nr(uint8_t row) {
    lv_obj_t    *obj;

    row = nr_item(row, "NR reduction amount", &options->audio.denoise.nr.reduction_amount, 0, 20);
    row = nr_item(row, "NR smoothing factor", &options->audio.denoise.nr.smoothing_factor, 0, 100);
    row = nr_item(row, "NR whitening factor", &options->audio.denoise.nr.whitening_factor, 0, 100);

    /* * */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "NR noise scale type");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_dropdown_create(grid);

    dialog_item(&dialog, obj);

    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    lv_obj_center(obj);

    lv_obj_t *list = lv_dropdown_get_list(obj);
    lv_obj_add_style(list, &dialog_dropdown_list_style, 0);

    lv_dropdown_set_options(obj, " Complite spectrum \n Critical bands \n Masking thresholds ");
    lv_dropdown_set_symbol(obj, NULL);
    lv_dropdown_set_selected(obj, options->audio.denoise.nr.noise_scaling_type);
    lv_obj_add_event_cb(obj, nr_scaling_type_cb, LV_EVENT_VALUE_CHANGED, NULL);
    row++;

    /* * */

    row = nr_item(row, "NR noise rescale", &options->audio.denoise.nr.noise_rescale, 0, 12);
    row = nr_item(row, "NR filter threshold", &options->audio.denoise.nr.post_filter_threshold, -10, 10);

    return row;
}

/* EMNR */

static void emnr_method_cb(lv_event_t * e) {
    lv_obj_t    *obj = lv_event_get_target(e);
    uint16_t    *x = lv_event_get_user_data(e);

    *x = lv_dropdown_get_selected(obj);

    dsp_update_denoise();
}

static void emnr_trained_cb(lv_event_t * e) {
    lv_obj_t    *obj = lv_event_get_target(e);
    float       *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj) / 100.0f;

    dsp_update_denoise();
}

static uint8_t make_emnr(uint8_t row) {
    lv_obj_t    *obj;
    lv_obj_t    *list;

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "EMNR gain method");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_dropdown_create(grid);

    dialog_item(&dialog, obj);

    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    lv_obj_center(obj);

    list = lv_dropdown_get_list(obj);
    lv_obj_add_style(list, &dialog_dropdown_list_style, 0);

    lv_dropdown_set_options(obj, " Gausian, linear scale \n Gausian, log scale \n Gamma \n Trained ");
    lv_dropdown_set_symbol(obj, NULL);
    lv_dropdown_set_selected(obj, options->audio.denoise.emnr.gain_method);
    lv_obj_add_event_cb(obj, emnr_method_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.gain_method);
    row++;

    /* * */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "EMNR NPE method");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_dropdown_create(grid);

    dialog_item(&dialog, obj);

    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    lv_obj_center(obj);

    list = lv_dropdown_get_list(obj);
    lv_obj_add_style(list, &dialog_dropdown_list_style, 0);

    lv_dropdown_set_options(obj, " OSMS \n MMSE \n NSTAT ");
    lv_dropdown_set_symbol(obj, NULL);
    lv_dropdown_set_selected(obj, options->audio.denoise.emnr.npe_method);
    lv_obj_add_event_cb(obj, emnr_method_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.npe_method);
    row++;

    /* * */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "EMNR trained threshold");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);
    lv_spinbox_set_value(obj, options->audio.denoise.emnr.trained_thresh * 100);
    lv_spinbox_set_range(obj, -500, 500);
    lv_obj_add_event_cb(obj, emnr_trained_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.trained_thresh);

    lv_spinbox_set_digit_format(obj, 3, 1);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    row++;

    /* * */

    row_dsc[row] = 54;

    obj = lv_label_create(grid);

    lv_label_set_text(obj, "EMNR trained T2");
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 0, 1, LV_GRID_ALIGN_CENTER, row, 1);

    obj = lv_spinbox_create(grid);

    dialog_item(&dialog, obj);
    lv_spinbox_set_value(obj, options->audio.denoise.emnr.trained_t2 * 100);
    lv_spinbox_set_range(obj, 2, 30);
    lv_obj_add_event_cb(obj, emnr_trained_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.trained_t2);

    lv_spinbox_set_digit_format(obj, 3, 1);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_set_size(obj, SMALL_6, 56);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_START, 1, 6, LV_GRID_ALIGN_CENTER, row, 1);
    row++;

    return row;
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

    row = make_delimiter(row);
    row = make_nr(row);

    row = make_delimiter(row);
    row = make_emnr(row);

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
