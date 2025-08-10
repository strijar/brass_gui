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

static void construct_cb(lv_obj_t *parent);
static void equalizer_speaker_update_cb(lv_event_t * e);
static void equalizer_mic_update_cb(lv_event_t * e);

typedef enum {
    EQ_SPEAKER = 0,
    EQ_MIC
} eq_sel_t;

static const lv_event_cb_t  eq_update[] = { equalizer_speaker_update_cb, equalizer_mic_update_cb };

static dialog_t     dialog = {
    .run = false,
    .construct_cb = construct_cb,
    .destruct_cb = NULL,
    .audio_cb = NULL,
    .buttons = false,
    .key_cb = dialog_key_cb
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

static void make_equalizer_item(eq_sel_t sel, uint8_t n, equalizer_item_t *item) {
    lv_obj_t        *obj;

    /* Label */

    dialog_label(&dialog, true, "EQ band %i", n + 1);

    /* Freq */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

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

    /* Width */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

    lv_spinbox_set_value(obj, item->q);
    lv_spinbox_set_range(obj, 1, 9);
    lv_spinbox_set_digit_format(obj, 1, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);

    lv_obj_add_event_cb(obj, eq_update[sel], LV_EVENT_VALUE_CHANGED, &item->q);

    /* Gain */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

    lv_spinbox_set_value(obj, item->gain);
    lv_spinbox_set_range(obj, -24, 12);
    lv_spinbox_set_digit_format(obj, 2, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
    lv_obj_add_event_cb(obj, eq_update[sel], LV_EVENT_VALUE_CHANGED, &item->gain);
}

/* Mic filter */

static void mic_filter_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    uint16_t        *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    mic_update_filter();
}

static void make_mic_filter() {
    lv_obj_t        *obj;
    filter_t        *filter = &options->audio.mic.filter;

    /* Label */

    dialog_label(&dialog, true, "Filter");

    /* Low */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

    lv_spinbox_set_value(obj, filter->low);
    lv_spinbox_set_range(obj, 50, 800);
    lv_spinbox_set_digit_format(obj, 3, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);

    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->low);

    /* High */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

    lv_spinbox_set_value(obj, filter->high);
    lv_spinbox_set_range(obj, 2000, 3200);
    lv_spinbox_set_digit_format(obj, 4, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);

    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->high);

    /* Transition */

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 2);

    lv_spinbox_set_value(obj, filter->transition);
    lv_spinbox_set_range(obj, 50, 200);
    lv_spinbox_set_digit_format(obj, 3, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);

    lv_obj_add_event_cb(obj, mic_filter_update_cb, LV_EVENT_VALUE_CHANGED, &filter->transition);
}

/* NR */

static void nr_update_cb(lv_event_t * e) {
    lv_obj_t        *obj = lv_event_get_target(e);
    uint16_t        *x = lv_event_get_user_data(e);

    *x = lv_spinbox_get_value(obj);
    dsp_update_denoise();
}

static void nr_item(const char *label, int16_t *data, int16_t min, int16_t max) {
    lv_obj_t    *obj;

    dialog_label(&dialog, true, label);

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 6);
    lv_spinbox_set_value(obj, *data);
    lv_spinbox_set_range(obj, min, max);
    lv_obj_add_event_cb(obj, nr_update_cb, LV_EVENT_VALUE_CHANGED, data);

    lv_spinbox_set_digit_format(obj, 2, 0);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
}

static void nr_scaling_type_cb(lv_event_t * e) {
    lv_obj_t *obj = lv_event_get_target(e);

    options->audio.denoise.nr.noise_scaling_type = lv_dropdown_get_selected(obj);

    dsp_update_denoise();
}

static void make_nr() {
    lv_obj_t    *obj;

    dialog_title(&dialog, "Noice reducer");

    nr_item("Reduction amount", &options->audio.denoise.nr.reduction_amount, 0, 20);
    nr_item("Smoothing factor", &options->audio.denoise.nr.smoothing_factor, 0, 100);
    nr_item("Whitening factor", &options->audio.denoise.nr.whitening_factor, 0, 100);

    /* * */

    dialog_label(&dialog, true, "Noise scale type");

    obj = dialog_dropdown(&dialog, 6);

    lv_dropdown_set_options(obj, " Complite spectrum \n Critical bands \n Masking thresholds ");
    lv_dropdown_set_selected(obj, options->audio.denoise.nr.noise_scaling_type);
    lv_obj_add_event_cb(obj, nr_scaling_type_cb, LV_EVENT_VALUE_CHANGED, NULL);

    /* * */

    nr_item("Noise rescale", &options->audio.denoise.nr.noise_rescale, 0, 12);
    nr_item("Threshold", &options->audio.denoise.nr.post_filter_threshold, -10, 10);
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

static void make_emnr() {
    lv_obj_t    *obj;
    lv_obj_t    *list;

    dialog_title(&dialog, "EMNR");

    dialog_label(&dialog, true, "Gain method");

    obj = dialog_dropdown(&dialog, 6);

    lv_dropdown_set_options(obj, " Gausian, linear scale \n Gausian, log scale \n Gamma \n Trained ");
    lv_dropdown_set_selected(obj, options->audio.denoise.emnr.gain_method);
    lv_obj_add_event_cb(obj, emnr_method_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.gain_method);

    /* * */

    dialog_label(&dialog, true, "NPE method");

    obj = dialog_dropdown(&dialog, 6);

    lv_dropdown_set_options(obj, " OSMS \n MMSE \n NSTAT ");
    lv_dropdown_set_selected(obj, options->audio.denoise.emnr.npe_method);
    lv_obj_add_event_cb(obj, emnr_method_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.npe_method);

    /* * */

    dialog_label(&dialog, true, "Trained threshold");

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 6);
    lv_spinbox_set_value(obj, options->audio.denoise.emnr.trained_thresh * 100);
    lv_spinbox_set_range(obj, -500, 500);
    lv_obj_add_event_cb(obj, emnr_trained_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.trained_thresh);

    lv_spinbox_set_digit_format(obj, 3, 1);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);

    /* * */

    dialog_label(&dialog, true, "Trained T2");

    obj = lv_spinbox_create(dialog.grid);

    dialog_item(&dialog, obj, 6);
    lv_spinbox_set_value(obj, options->audio.denoise.emnr.trained_t2 * 100);
    lv_spinbox_set_range(obj, 2, 30);
    lv_obj_add_event_cb(obj, emnr_trained_cb, LV_EVENT_VALUE_CHANGED, &options->audio.denoise.emnr.trained_t2);

    lv_spinbox_set_digit_format(obj, 3, 1);
    lv_spinbox_set_digit_step_direction(obj, LV_DIR_LEFT);
}

/* * */

static void construct_cb(lv_obj_t *parent) {
    dialog_grid(parent, &dialog);

    /* * */

    dialog_title(&dialog, "Mic");

    make_mic_filter();

    for (uint8_t i = 0; i < EQUALIZER_NUM; i++) {
        make_equalizer_item(EQ_MIC, i, &options->audio.mic.eq[i]);
    }

    /* * */

    dialog_title(&dialog, "Speaker");

    for (uint8_t i = 0; i < EQUALIZER_NUM; i++) {
        make_equalizer_item(EQ_SPEAKER, i, &options->audio.speaker.eq[i]);
    }

    /* * */

    make_nr();
    make_emnr();
}
