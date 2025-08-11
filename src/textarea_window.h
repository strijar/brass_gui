/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#pragma once

#include <unistd.h>
#include <stdint.h>

#include "lvgl/lvgl.h"

typedef void (*textarea_window_cb_t)(void);

lv_obj_t * textarea_window_open(textarea_window_cb_t ok_cb, textarea_window_cb_t cancel_cb);
void textarea_window_close();

const char* textarea_window_get();
void textarea_window_set(const char *text);

lv_obj_t * textarea_window_text();
