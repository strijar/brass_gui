/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <pthread.h>
#include "backlight.h"
#include "queue.h"

typedef struct item_t {
    lv_obj_t        *obj;
    lv_event_code_t event_code;
    void            *param;
    struct item_t   *next;
} item_t;

static struct item_t    *head = NULL;
static struct item_t    *tail = NULL;
static pthread_mutex_t  mux;

void queue_init() {
    pthread_mutex_init(&mux, NULL);
}

void queue_work() {
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
            head = tail  = NULL;
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

void queue_send(lv_obj_t *obj, lv_event_code_t event_code, void *param) {
    item_t *item = malloc(sizeof(item_t));

    item->obj = obj;
    item->event_code = event_code;
    item->param = param;

    pthread_mutex_lock(&mux);

    if (head == NULL && tail == NULL) {
        head = tail = item;
    } else {
        tail->next = item;
        tail = item;
    }

    pthread_mutex_unlock(&mux);
}
