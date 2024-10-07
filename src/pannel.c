/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include <stdio.h>
#include <stdlib.h>
#include "pannel.h"
#include "styles.h"
#include "util.h"
#include "events.h"
#include "radio.h"
#include "params.h"
#include "rtty.h"

static lv_obj_t     *obj;
static char         buf[1024];
static char         tmp_buf[1024];
static char         *last_line;

static void check_lines() {
    char        *second_line = NULL;
    char        *ptr = (char *) &buf;
    uint16_t    count = 0;
    
    while (*ptr) {
        if (*ptr == '\n') {
            count++;
            
            if (count == 1) {
                second_line = ptr + 1;
            }
        }
        ptr++;
    }
    
    if (count > 6) {
        strcpy(tmp_buf, second_line);
        strcpy(buf, tmp_buf);
    }

    ptr = (char *) &buf;

    while (*ptr) {
        if (*ptr == '\n') {
            last_line = ptr + 1;
        }
        ptr++;
    }
    
    *last_line = '\0';
}

static void pannel_update_cb(lv_event_t * e) {
    lv_point_t line_size;
    lv_point_t text_size;

    char *text = lv_event_get_param(e);
    
    if (strcmp(text, "\n") == 0) {
        if (last_line[strlen(last_line) - 1] != '\n') {
            strcat(last_line, text);
            check_lines();
        }
    } else {
        lv_txt_get_size(&line_size, last_line, font_panel, 0, 0, LV_COORD_MAX, 0);
        lv_txt_get_size(&text_size, text, font_panel, 0, 0, LV_COORD_MAX, 0);

        if (line_size.x + text_size.x > (lv_obj_get_width(obj) - 40)) {
            strcat(last_line, "\n");
            check_lines();
        }
    
        strcat(last_line, text);
    }
    
    lv_label_set_text_static(obj, buf);
}

lv_obj_t * pannel_init(lv_obj_t *parent) {
    obj = lv_label_create(parent);

    lv_obj_add_style(obj, &pannel_style, 0);
    lv_obj_add_event_cb(obj, pannel_update_cb, EVENT_PANNEL_UPDATE, NULL);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);

    return obj;
}

void pannel_add_text(const char * text) {
    lv_obj_send_event(obj, EVENT_PANNEL_UPDATE, strdup(text));
}

void pannel_hide() {
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void pannel_visible() {
    radio_mode_t    mode = radio_current_mode();
    bool            on = false;

    switch (mode) {
        case radio_mode_cw:
        case radio_mode_cwr:
            on = params.cw_decoder;
            break;
            
        case radio_mode_usb:
        case radio_mode_lsb:
            on = rtty_get_state() != RTTY_OFF;
            break;
    }

    if (on) {
        strcpy(buf, "");
        last_line = (char *) &buf;
        lv_label_set_text_static(obj, buf);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
    }
}
