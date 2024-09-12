/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <pthread.h>
#include "events.h"
#include "backlight.h"
#include "keyboard.h"
#include "dialog.h"

#define QUEUE_SIZE  32

uint32_t        EVENT_ROTARY;
uint32_t        EVENT_KEYPAD;
uint32_t        EVENT_HKEY;
uint32_t        EVENT_RADIO_TX;
uint32_t        EVENT_RADIO_RX;
uint32_t        EVENT_PANNEL_UPDATE;
uint32_t        EVENT_SCREEN_UPDATE;
uint32_t        EVENT_ATU_UPDATE;
uint32_t        EVENT_MSG_UPDATE;
uint32_t        EVENT_FREQ_UPDATE;
uint32_t        EVENT_FT8_MSG;
uint32_t        EVENT_GPS;
uint32_t        EVENT_BAND_UP;
uint32_t        EVENT_BAND_DOWN;

typedef struct item_t {
    lv_obj_t        *obj;
    lv_event_code_t event_code;
    void            *param;
    struct item_t   *next;
} item_t;

static struct item_t    *head = NULL;
static struct item_t    *tail = NULL;
static pthread_mutex_t  mux;

void event_init() {
    EVENT_ROTARY = lv_event_register_id();
    EVENT_KEYPAD = lv_event_register_id();
    EVENT_HKEY = lv_event_register_id();
    EVENT_RADIO_TX = lv_event_register_id();
    EVENT_RADIO_RX = lv_event_register_id();
    EVENT_PANNEL_UPDATE = lv_event_register_id();
    EVENT_SCREEN_UPDATE = lv_event_register_id();
    EVENT_ATU_UPDATE = lv_event_register_id();
    EVENT_MSG_UPDATE = lv_event_register_id();
    EVENT_FREQ_UPDATE = lv_event_register_id();
    EVENT_FT8_MSG = lv_event_register_id();
    EVENT_GPS = lv_event_register_id();
    EVENT_BAND_UP = lv_event_register_id();
    EVENT_BAND_DOWN = lv_event_register_id();

    pthread_mutex_init(&mux, NULL);
}

void event_obj_check() {
    pthread_mutex_lock(&mux);

    while (head != NULL) {
        item_t *item = head;

        pthread_mutex_unlock(&mux);
        
        if (item->event_code == LV_EVENT_REFRESH) {
            if (backlight_is_on()) {
                lv_obj_invalidate(item->obj);
            }
        } else {
            lv_event_send(item->obj, item->event_code, item->param);
        }

        pthread_mutex_lock(&mux);

        if (head == tail) {
            head = tail = NULL;
        } else {
            head = head->next;
        }

        if (item->param != NULL) {
            free(item->param);
        }
        
        free(item);
    }

    pthread_mutex_unlock(&mux);
}

void event_send(lv_obj_t *obj, lv_event_code_t event_code, void *param) {
    item_t *item = malloc(sizeof(item_t));

    item->obj = obj;
    item->event_code = event_code;
    item->param = param;
    item->next = NULL;

    pthread_mutex_lock(&mux);
    
    if (head == NULL && tail == NULL) {
        head = tail = item;
    } else {
        tail->next = item;
        tail = item;
    }

    pthread_mutex_unlock(&mux);
}

void event_send_key(int32_t key) {
    int32_t *c = malloc(sizeof(int32_t));
    *c = key;
        
    event_send(lv_group_get_focused(keyboard_group), LV_EVENT_KEY, c);
}
