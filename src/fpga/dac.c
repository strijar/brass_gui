/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <math.h>

#include "lvgl/lvgl.h"
#include "src/dsp.h"
#include "src/gpio.h"
#include "dac.h"

static int              fd;
static float complex    samples[DAC_SAMPLES];
static bool             prev_tx = false;

static void * dac_thread(void *arg) {
    while (true) {
        size_t size = dsp_dac(samples, DAC_SAMPLES);

        if (size > 0) {
            if (!prev_tx) {
                prev_tx = true;
                gpio_set_preamp(false);
                gpio_set_tx(true);
            }

            int res = write(fd, samples, size * sizeof(float complex));

            if (res != size * sizeof(float complex)) {
                LV_LOG_WARN("Fix me");
            }
        } else {
            if (prev_tx) {
                prev_tx = false;
                gpio_set_preamp(true);
                gpio_set_tx(false);
            }
            usleep(1000);
        }
    }
}

bool dac_init() {
    /* Stream */

    fd = open("/dev/axis_fifo_0x43c10000", O_WRONLY);

    if (fd < 1) {
        LV_LOG_ERROR("Unable to open DAC stream device file");
        return false;
    }

    pthread_t thread;

    pthread_create(&thread, NULL, dac_thread, NULL);
    pthread_detach(thread);

    return true;
}
