/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdio.h>
#include "msg.h"
#include "styles.h"
#include "util.h"
#include "events.h"

static lv_obj_t     *obj;
static char         buf[512];
static lv_timer_t   *timer = NULL;
static lv_anim_t    fade;
static bool         fade_run = false;
static uint16_t     timeout = 5000;

static void msg_timer(lv_timer_t *t) {
    lv_anim_set_values(&fade, lv_obj_get_style_opa(obj, 0), LV_OPA_TRANSP);
    lv_anim_start(&fade);
    timer = NULL;
}

static void fade_anim(void * obj, int32_t v) {
    lv_obj_set_style_opa(obj, v, 0);
}

static void fade_ready(lv_anim_t * a) {
    fade_run = false;
}

static void msg_update_cb(lv_event_t * e) {
    lv_label_set_text(obj, buf);
    lv_obj_move_foreground(obj);
    
    if (!fade_run) {
        fade_run = true;
        lv_anim_set_values(&fade, lv_obj_get_style_opa(obj, 0), LV_OPA_COVER);
        lv_anim_start(&fade);
    }

    if (timer) {
        lv_timer_reset(timer);
    } else {
        timer = lv_timer_create(msg_timer, timeout, NULL);
        lv_timer_set_repeat_count(timer, 1);
    }
}

lv_obj_t * msg_init(lv_obj_t *parent) {
    obj = lv_label_create(parent);

    lv_obj_add_style(obj, &msg_style, 0);

    lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_opa(obj, LV_OPA_TRANSP, 0);
    lv_obj_add_event_cb(obj, msg_update_cb, EVENT_MSG_UPDATE, NULL);

    lv_anim_init(&fade);
    lv_anim_set_var(&fade, obj);
    lv_anim_set_time(&fade, 250);
    lv_anim_set_exec_cb(&fade, fade_anim);
    lv_anim_set_ready_cb(&fade, fade_ready);

    return obj;
}

void msg_set_text_fmt(const char * fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    lv_obj_send_event(obj, EVENT_MSG_UPDATE, NULL);
}

void msg_set_timeout(uint16_t x) {
    timeout = x;
}
