/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
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
#include "audio_adc.h"
#include "cw.h"
#include "cw_key.h"
#include "pannel.h"
#include "rtty.h"
#include "backlight.h"
#include "events.h"
#include "gps.h"
#include "fpga/fft.h"
#include "fpga/adc.h"
#include "fpga/dac.h"
#include "python/python.h"
#include "mic.h"

#define DISP_BUF_SIZE (800 * 480 * 3)

rotary_t                    *vol;
encoder_t                   *mfk;

static lv_color_t           buf[DISP_BUF_SIZE];
static lv_display_t         *disp;

int main(void) {
    params_init();

    lv_init();
    lv_libpng_init();
    
    mic_init();
    audio_init();
    audio_adc_init();
    event_init();

    disp = lv_linux_fbdev_create();
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_DIRECT);

    /*    
    disp_drv.draw_buf   = &disp_buf;
    disp_drv.flush_cb   = fbdev_flush;
    disp_drv.hor_res    = 800;
    disp_drv.ver_res    = 480;
    */
    
//    lv_display_set_bg_color(lv_display_get_default(), lv_color_black());
//    lv_displat_set_bg_opa(lv_display_get_default(), LV_OPA_COVER);

    lv_timer_t *timer = _lv_disp_get_refr_timer(lv_display_get_default());
    
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
    fft_init();
    adc_init();
    dac_init();

/*
    backlight_init();
    pannel_visible();
    gps_init();
*/
    uint64_t prev_time = get_time();

    lv_screen_load(main_obj);

    while (1) {
        lv_lock();
        
        lv_timer_handler();
        
        uint64_t now = get_time();
        lv_tick_inc(now - prev_time);
        prev_time = now;

        lv_unlock();

        usleep(10);
    }

    return 0;
}
