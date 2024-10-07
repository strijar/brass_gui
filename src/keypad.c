/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
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
    lv_obj_send_event(lv_screen_active(), EVENT_KEYPAD, (void*) &event);
    timer = NULL;
}

static void keypad_input_read(lv_indev_t *drv, lv_indev_data_t *data) {
    struct input_event  in;
    keypad_t            *keypad = (keypad_t*) lv_indev_get_driver_data(drv);

    if (read(keypad->fd, &in, sizeof(struct input_event)) > 0) {
        if (in.type == EV_KEY) {
            backlight_tick();
        
            switch (in.code) {
                /* PTT */
            
                case KEY_CONNECT:
//                    lv_msg_send(MSG_PTT, &in.value);
                    return;
            
                /* Rotary VOL */
                
                case BTN_NORTH:
                    data->key = LV_KEY_ESC;
                    data->state = (in.value) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
                    keypad->evdev_key = data->key;
                    keypad->evdev_state = data->state;
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
                    event.key = KEYPAD_GEN;
                    break;

                case KEY_2:
                    event.key = KEYPAD_APP;
                    break;

                /*
                case KEY_3:
                    event.key = KEYPAD_KEY;
                    break;
                */

                case KEY_3:
                    event.key = KEYPAD_MSG;
                    break;

                case BTN_TRIGGER_HAPPY3:
                    event.key = KEYPAD_DFN;
                    break;

                case BTN_TRIGGER_HAPPY9:
                    event.key = KEYPAD_DFL;
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

                /* Top side */ 

                case BTN_TRIGGER_HAPPY4:
                    event.key = KEYPAD_PTT;
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

                case BTN_TRIGGER_HAPPY16:
                    event.key = KEYPAD_AB;
                    break;

                case BTN_TRIGGER_HAPPY17:
                    event.key = KEYPAD_PRE;
                    break;

                case BTN_TRIGGER_HAPPY18:
                    event.key = KEYPAD_ATU;
                    break;

                case BTN_TRIGGER_HAPPY22:
                    event.key = KEYPAD_VM;
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
                lv_obj_send_event(lv_screen_active(), EVENT_KEYPAD, (void*) &event);

                timer = lv_timer_create(keypad_timer, KEYPAD_LONG_TIME, NULL);
                lv_timer_set_repeat_count(timer, 1);
            } else {
                if (event.state == KEYPAD_PRESS) {
                    event.state = KEYPAD_RELEASE;
                    lv_obj_send_event(lv_screen_active(), EVENT_KEYPAD, (void*) &event);
                } else if (event.state == KEYPAD_LONG) {
                    event.state = KEYPAD_LONG_RELEASE;
                    lv_obj_send_event(lv_screen_active(), EVENT_KEYPAD, (void*) &event);
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
    
    keypad->indev = lv_indev_create();
    
    lv_indev_set_type(keypad->indev, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(keypad->indev, keypad_input_read);
//    keypad->indev_drv.user_data = keypad;
//    keypad->indev_drv.long_press_time = 1000;
    
    lv_indev_set_group(keypad->indev, keyboard_group);

    return keypad;
}
