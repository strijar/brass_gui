/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include "lvgl/lvgl.h"
#include "params.h"

#define MEM_NUM         8

#define MEM_BACKUP_ID   (MEM_NUM + 1)
#define MEM_FT8_ID      100
#define MEM_FT4_ID      200
#define MEM_WSPR_ID     300
#define MEM_SSTV_ID     400

typedef enum {
    APP_FT8 = 0,
    APP_GPS,
    APP_SETTINGS,
    APP_RECORDER,
} app_t;

lv_obj_t * main_screen();
void main_screen_band_changed();

void main_screen_keys_enable(bool value);
void main_screen_dialog_deleted_cb();
void main_screen_app(app_t app);
void main_screen_action(press_action_t action);

void main_screen_lock_freq(bool lock);
void main_screen_lock_band(bool lock);
void main_screen_lock_mode(bool lock);

void main_screen_set_freq(uint64_t f);

void mem_load(uint16_t id);
void mem_save(uint16_t id);

void main_screen_update_range();
