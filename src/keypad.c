/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#include "keypad.h"
#include "main.h"
#include "backlight.h"
#include "keyboard.h"
#include "msgs.h"

#define KEYPAD_LONG_TIME 1000

static event_keypad_t   event;
static lv_timer_t       *timer = NULL;

static void keypad_timer(lv_timer_t *t) {
    event.state = KEYPAD_LONG;
    lv_event_send(lv_scr_act(), EVENT_KEYPAD, (void*) &event);
    timer = NULL;
}

static void keypad_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    struct input_event  in;
    keypad_t            *keypad = (keypad_t*) drv->user_data;

    if (read(keypad->fd, &in, sizeof(struct input_event)) > 0) {
        if (in.type == EV_KEY) {
            backlight_tick();

            switch (in.code) {
                /* PTT */

                case KEY_CONNECT:
                    lv_msg_send(MSG_PTT, &in.value);
                    return;

                /* Rotary VOL */

                case BTN_NORTH:
                    if (in.value) {
                        int32_t *c = malloc(sizeof(int32_t));
                        *c = LV_KEY_ESC;

                        lv_event_send(lv_group_get_focused(keyboard_group), LV_EVENT_KEY, c);
                    }
                    return;

                /* Rotary MFK */

                case BTN_SOUTH:
                    mfk->pressed = (in.value != 0);
                    return;

                /* Front side */

                case KEY_POWER:
                    event.key = KEYPAD_POWER;
                    break;

                case KEY_1:
                    event.key = KEYPAD_VOL;
                    break;

                case KEY_2:
                    event.key = KEYPAD_MFK;
                    break;

                case KEY_3:
                    event.key = KEYPAD_APP;
                    break;

                case KEY_F1:
                    event.key = KEYPAD_F1;
                    break;

                case KEY_F2:
                    event.key = KEYPAD_F2;
                    break;

                case KEY_F3:
                    event.key = KEYPAD_F3;
                    break;

                case KEY_F4:
                    event.key = KEYPAD_F4;
                    break;

                case KEY_F5:
                    event.key = KEYPAD_F5;
                    break;

                case KEY_F6:
                    event.key = KEYPAD_F6;
                    break;

                case KEY_A:
                    event.key = KEYPAD_BAND_DOWN;
                    break;

                case KEY_B:
                    event.key = KEYPAD_BAND_UP;
                    break;

                case KEY_C:
                    event.key = KEYPAD_FST;
                    break;

                case KEY_D:
                    event.key = KEYPAD_MODE;
                    break;

                default:
                    event.key = KEYPAD_UNKNOWN;
                    LV_LOG_WARN("Unknown key");
                    break;
            }

            if (timer) {
                lv_timer_del(timer);
                timer = NULL;
            }

            if (in.value == 1) {
                event.state = KEYPAD_PRESS;
                lv_event_send(lv_scr_act(), EVENT_KEYPAD, (void*) &event);

                timer = lv_timer_create(keypad_timer, KEYPAD_LONG_TIME, NULL);
                lv_timer_set_repeat_count(timer, 1);
            } else {
                if (event.state == KEYPAD_PRESS) {
                    event.state = KEYPAD_RELEASE;
                    lv_event_send(lv_scr_act(), EVENT_KEYPAD, (void*) &event);
                } else if (event.state == KEYPAD_LONG) {
                    event.state = KEYPAD_LONG_RELEASE;
                    lv_event_send(lv_scr_act(), EVENT_KEYPAD, (void*) &event);
                }
            }
        }
    }

    data->key = keypad->evdev_key;
    data->state = keypad->evdev_state;
}

keypad_t * keypad_init(char *dev_name) {
    int fd = open(dev_name, O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror("unable to open keypad interface:");

        return NULL;
    }

    fcntl(fd, F_SETFL, O_ASYNC | O_NONBLOCK);

    keypad_t *keypad = malloc(sizeof(keypad_t));

    keypad->fd = fd;

    lv_indev_drv_init(&keypad->indev_drv);

    keypad->indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    keypad->indev_drv.read_cb = keypad_input_read;
    keypad->indev_drv.user_data = keypad;
    keypad->indev_drv.long_press_time = 1000;

    keypad->indev = lv_indev_drv_register(&keypad->indev_drv);

    lv_indev_set_group(keypad->indev, keyboard_group);

    return keypad;
}
