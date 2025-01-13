/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#include "main.h"
#include "main_screen.h"
#include "styles.h"
#include "radio.h"
#include "dsp.h"
#include "util.h"
#include "keyboard.h"
#include "waterfall.h"
#include "keypad.h"
#include "params.h"
#include "bands.h"
#include "audio.h"
#include "cw.h"
#include "cw_key.h"
#include "pannel.h"
#include "rtty.h"
#include "backlight.h"
#include "events.h"
#include "queue.h"
#include "gps.h"
#include "fpga/adc.h"
#include "fpga/dac.h"
#include "fpga/mb.h"
#include "python/python.h"
#include "mic.h"
#include "vt.h"
#include "render/render.h"
#include "gpio.h"
#include "settings/bands.h"
#include "settings/modes.h"
#include "settings/options.h"

#define DISP_BUF_SIZE (800 * 480)

rotary_t                    *vol;
encoder_t                   *mfk;

static lv_color_t           buf_1[DISP_BUF_SIZE];
static lv_color_t           buf_2[DISP_BUF_SIZE];
static lv_disp_draw_buf_t   disp_buf;
static lv_disp_drv_t        disp_drv;
static pthread_mutex_t      mux;

void lv_lock() {
    pthread_mutex_lock(&mux);
}

void lv_unlock() {
    pthread_mutex_unlock(&mux);
}

void main_exit() {
    settings_bands_save();
    settings_modes_save();
    settings_options_save();
    vt_enable();
    exit(1);
}

int main(void) {
    vt_disable();
    pthread_mutex_init(&mux, NULL);

    params_init();
    settings_modes_load();
    settings_bands_load();
    settings_options_load();

    lv_init();
    lv_png_init();

    fbdev_init();
    mic_init();
    audio_init();
    queue_init();
    event_init();
    gpio_init();

    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);
    lv_disp_drv_init(&disp_drv);

    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;

#if 1
    disp_drv.draw_ctx_init = brass_draw_ctx_init;
    disp_drv.draw_ctx_size = sizeof(brass_draw_ctx_t);
#endif

    lv_disp_drv_register(&disp_drv);

    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());
    lv_disp_set_bg_opa(lv_disp_get_default(), LV_OPA_COVER);

    lv_timer_t *timer = _lv_disp_get_refr_timer(lv_disp_get_default());

    lv_timer_set_period(timer, 15);

    keyboard_init();

    vol = rotary_init("/dev/input/event0", 1);
    mfk = encoder_init("/dev/input/event1");
    rotary_t *main = rotary_init("/dev/input/event2", 8);
    keypad_t *keypad = keypad_init("/dev/input/event3");
    keypad_t *gpio = keypad_init("/dev/input/event4");

    vol->left[VOL_EDIT] = KEY_VOL_LEFT_EDIT;
    vol->right[VOL_EDIT] = KEY_VOL_RIGHT_EDIT;

    vol->left[VOL_SELECT] = KEY_VOL_LEFT_SELECT;
    vol->right[VOL_SELECT] = KEY_VOL_RIGHT_SELECT;

    styles_init();
    python_init();

    lv_obj_t *main_obj = main_screen();

    cw_init();
    cw_key_init();
    dsp_init();
    rtty_init();
    radio_init(main_obj);
    adc_init();
    dac_init();
    mb_init();

/*
    backlight_init();
    gps_init();
*/
    uint64_t prev_time = get_time();

    lv_scr_load(main_obj);

    while (1) {
        lv_lock();

        lv_timer_handler();
        queue_work();

        uint64_t now = get_time();
        uint64_t delta = now - prev_time;

        lv_tick_inc(delta);
        prev_time = now;

        lv_unlock();
        usleep(100);
    }

    return 0;
}
