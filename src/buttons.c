/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "styles.h"
#include "main_screen.h"
#include "buttons.h"
#include "mfk.h"
#include "vol.h"
#include "msg.h"
#include "rtty.h"
#include "pannel.h"
#include "params.h"
#include "dialog.h"
#include "dialog_settings.h"
#include "dialog_swrscan.h"
#include "dialog_ft8.h"
#include "dialog_freq.h"
#include "dialog_gps.h"
#include "dialog_msg_cw.h"
#include "dialog_msg_voice.h"
#include "dialog_recorder.h"
#include "voice.h"
#include "events.h"
#include "msgs.h"

#define BUTTONS     6

typedef struct {
    lv_obj_t        *obj;
    button_item_t   *item;
} button_t;

static uint8_t      btn_height = 62;
static button_t     btn[6];
static lv_obj_t     *parent_obj = NULL;

static void button_app_page_cb(lv_event_t * e);
static void button_vol_update_cb(lv_event_t * e);
static void button_mfk_update_cb(lv_event_t * e);
static void button_mem_load_cb(lv_event_t * e);

static void button_vol_hold_cb(void * ptr);
static void button_mfk_hold_cb(void * ptr);
static void button_mem_save_cb(void * ptr);

static void button_action_cb(lv_event_t * e);

static button_page_t    buttons_page = PAGE_VOL_1;

static button_item_t    buttons[] = {
    { .label = "Audio\nVol",        .press = button_vol_update_cb,                                  .data = VOL_VOL },
    { .label = "TX\nPower",         .press = button_vol_update_cb,  .hold = button_vol_hold_cb,     .data = VOL_PWR },
    { .label = "Freq\nMode",        .press = button_vol_update_cb,  .hold = button_vol_hold_cb,     .data = VOL_FREQ_MODE },
    { .label = "Split",             .press = button_vol_update_cb,  .hold = button_vol_hold_cb,     .data = VOL_SPLIT },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },

    /* LSB, USB, AM, NFM */

    { .label = "Filter\nLow",       .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_LOW },
    { .label = "Filter\nHigh",      .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_HIGH },
    { .label = "Filter\nTransition",.press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_TRANSITION },
    { .label = "AGC",               .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_AGC },
    { .label = "Spectrum\nZoom",    .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_SPECTRUM_FACTOR },
    { .label = "",                  .press = NULL },

    /* CW, CWR */

    { .label = "Filter\nLow",       .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_LOW },
    { .label = "Filter\nHigh",      .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_HIGH },
    { .label = "Filter\nTransition",.press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_TRANSITION },
    { .label = "AGC",               .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_AGC },
    { .label = "Spectrum\nZoom",    .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_SPECTRUM_FACTOR },
    { .label = "Key\nSpeed",        .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_KEY_SPEED },

    { .label = "Key\nTone",         .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_KEY_TONE },
    { .label = "Key\nMode",         .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_KEY_MODE },
    { .label = "Iambic\nMode",      .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_IAMBIC_MODE },
    { .label = "Key\nTrain",        .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_KEY_TRAIN },
    { .label = "QSK\nTime",         .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_QSK_TIME },
    { .label = "Key\nRatio",        .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_KEY_RATIO },

    { .label = "CW\nDecoder",       .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_CW_DECODER },
    { .label = "CW\nSNR",           .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_CW_DECODER_SNR },
    { .label = "CW Peak\nBeta",     .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_CW_DECODER_PEAK_BETA },
    { .label = "CW Noise\nBeta",    .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_CW_DECODER_NOISE_BETA },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    
    /* RTTY */

    { .label = "Filter\nLow",       .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_LOW },
    { .label = "Filter\nHigh",      .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_HIGH },
    { .label = "Filter\nTransition",.press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_FILTER_TRANSITION },
    { .label = "AGC",               .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_AGC },
    { .label = "Spectrum\nZoom",    .press = button_mfk_update_cb,  .hold = button_mfk_hold_cb,     .data = MFK_SPECTRUM_FACTOR },
    { .label = "Rate",              .press = button_mfk_update_cb,  .data = MFK_RTTY_RATE },

    { .label = "Shift",             .press = button_mfk_update_cb,  .data = MFK_RTTY_SHIFT },
    { .label = "Center",            .press = button_mfk_update_cb,  .data = MFK_RTTY_CENTER },
    { .label = "Reverse",           .press = button_mfk_update_cb,  .data = MFK_RTTY_REVERSE },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },

    /* APP */

    { .label = "FT8",               .press = button_app_page_cb,    .data = APP_FT8 },
    { .label = "GPS",               .press = button_app_page_cb,    .data = APP_GPS },
    { .label = "Recorder",          .press = button_app_page_cb,    .data = APP_RECORDER },
    { .label = "QTH",               .press = button_action_cb,      .data = ACTION_APP_QTH },
    { .label = "Callsign",          .press = button_action_cb,      .data = ACTION_APP_CALLSIGN },
    { .label = "Settings",          .press = button_app_page_cb,    .data = APP_SETTINGS },
    
    /* APP MSG CW */

    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },

    /* APP MSG VOICE */

    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },

    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
    { .label = "",                  .press = NULL },
};

static void buttons_load_mode() {
    switch (params_band.mode) {
        case RADIO_MODE_LSB:
        case RADIO_MODE_USB:
        case RADIO_MODE_AM:
        case RADIO_MODE_NFM:
            buttons_unload_page();
            buttons_load_page(PAGE_VOICE_1);
            break;

        case RADIO_MODE_CW:
        case RADIO_MODE_CWR:
            buttons_unload_page();
            buttons_load_page(PAGE_CW_1);
            break;

        case RADIO_MODE_RTTY:
            buttons_unload_page();
            buttons_load_page(PAGE_RTTY_1);
            break;
    }
}

static void mode_changed_cb(void *s, lv_msg_t *m) {
    buttons_load_mode();
}

void buttons_init(lv_obj_t *parent) {
    uint16_t y = 480 - btn_height;
    uint16_t x = 0;
    uint16_t width = 133;

    for (uint8_t i = 0; i < BUTTONS; i++) {
        lv_obj_t *f = lv_btn_create(parent);
        
        lv_obj_remove_style_all(f); 
        lv_obj_add_style(f, &btn_style, 0);

        lv_obj_set_pos(f, x, y);
        lv_obj_set_size(f, width, btn_height);

        x += width;
        
        lv_obj_t *label = lv_label_create(f);
        
        lv_obj_center(label);
        lv_obj_set_user_data(f, label);
        lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

        btn[i].obj = f;
    }

    parent_obj = parent;
    lv_msg_subsribe(MSG_MODE_CHANGED, mode_changed_cb, NULL);
}

void buttons_load(uint8_t n, button_item_t *item) {
    lv_obj_t        *label = lv_obj_get_user_data(btn[n].obj);

    lv_obj_remove_event_cb(btn[n].obj, NULL);
    lv_obj_add_event_cb(btn[n].obj, item->press, LV_EVENT_PRESSED, item);
    lv_label_set_text(label, item->label);

    btn[n].item = item;
}

void buttons_load_page(button_page_t page) {
    buttons_page = page;

    for (uint8_t i = 0; i < BUTTONS; i++) {
        buttons_load(i, &buttons[buttons_page * BUTTONS + i]);
    }
}

void buttons_unload_page() {
    for (uint8_t i = 0; i < BUTTONS; i++) {
        lv_obj_t        *label = lv_obj_get_user_data(btn[i].obj);

        lv_obj_remove_event_cb(btn[i].obj, NULL);
        lv_label_set_text(label, "");
        btn[i].item = NULL;
    }
}

static void button_app_page_cb(lv_event_t * e) {
    button_item_t *item = lv_event_get_user_data(e);

    main_screen_app(item->data);
}

static void button_action_cb(lv_event_t * e) {
    button_item_t *item = lv_event_get_user_data(e);

    main_screen_action(item->data);
}

static void button_vol_update_cb(lv_event_t * e) {
    button_item_t *item = lv_event_get_user_data(e);

    vol_set_mode(item->data);
    vol_update(0, true);
}

static void button_mfk_update_cb(lv_event_t * e) {
    button_item_t *item = lv_event_get_user_data(e);

    mfk_set_mode(item->data);
    mfk_update(0, true);
}

static void button_vol_hold_cb(void * ptr) {
    button_item_t   *item = (button_item_t*) ptr;
    uint64_t        mask = (uint64_t) 1L << item->data;

    params_lock();
    params.vol_modes ^= mask;
    params_unlock(&params.durty.vol_modes);
    
    if (params.vol_modes & mask) {
        msg_set_text_fmt("Added to VOL encoder");
        voice_say_text_fmt("Added to volume encoder");
    } else {
        msg_set_text_fmt("Removed from VOL encoder");
        voice_say_text_fmt("Romoved to volume encoder");
    }
}

static void button_mfk_hold_cb(void * ptr) {
    button_item_t   *item = (button_item_t*) ptr;
    uint64_t        mask = (uint64_t) 1L << item->data;

    params_lock();
    params.mfk_modes ^= mask;
    params_unlock(&params.durty.mfk_modes);
    
    if (params.mfk_modes & mask) {
        msg_set_text_fmt("Added to MFK encoder");
        voice_say_text_fmt("Added to MFK encoder");
    } else {
        msg_set_text_fmt("Removed from MFK encoder");
        voice_say_text_fmt("Removed from MFK encoder");
    }
}

static void button_mem_load_cb(lv_event_t * e) {
    button_item_t *item = lv_event_get_user_data(e);

    mem_load(item->data);
    voice_say_text_fmt("Memory %i loaded", item->data);
}

static void button_mem_save_cb(void * ptr) {
    button_item_t   *item = (button_item_t*) ptr;
 
    mem_save(item->data);
    voice_say_text_fmt("Memory %i stored", item->data);
}

void buttons_press(uint8_t n, bool hold) {
    if (hold) {
        button_item_t *item = btn[n].item;
        
        if (item != NULL && item->hold) {
            item->hold(item);
        }
    } else {
        lv_event_send(btn[n].obj, LV_EVENT_PRESSED, NULL);
        lv_event_send(btn[n].obj, LV_EVENT_RELEASED, NULL);
    }
}

void buttons_vol() {
    buttons_unload_page();
    buttons_load_page(PAGE_VOL_1);
}

void buttons_mfk() {
    switch (buttons_page) {
        case PAGE_CW_1:
            buttons_unload_page();
            buttons_load_page(PAGE_CW_2);
            break;

        case PAGE_CW_2:
            buttons_unload_page();
            buttons_load_page(PAGE_CW_3);
            break;

        case PAGE_CW_3:
            buttons_unload_page();
            buttons_load_page(PAGE_CW_1);
            break;

        case PAGE_RTTY_1:
            buttons_unload_page();
            buttons_load_page(PAGE_RTTY_2);
            break;

        case PAGE_RTTY_2:
            buttons_unload_page();
            buttons_load_page(PAGE_RTTY_1);
            break;
            
        default:
            buttons_load_mode();
            break;
    }
}

void buttons_app() {
    buttons_unload_page();
    buttons_load_page(PAGE_APP_1);
}
