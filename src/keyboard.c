/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include "lvgl/src/drivers/evdev/lv_evdev.h"

#include "keyboard.h"

lv_group_t *keyboard_group;

static bool                 ready = false;

void keyboard_init() {
    keyboard_group = lv_group_create();

    lv_indev_t *keyboard_indev = lv_evdev_create(LV_INDEV_TYPE_KEYPAD, "/dev/input/event5");
    if (keyboard_indev == NULL) return;

    lv_indev_set_group(keyboard_indev, keyboard_group);

    ready = true;
}

bool keyboard_ready() {
    return ready;
}
