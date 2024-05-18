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

#include "lvgl/lvgl.h"
#include "src/dsp.h"
#include "adc.h"
#include "dma-proxy.h"

#define ADC_BUFS                4

static int                      fd;
static int                      buf_id = 0;
static struct channel_buffer    *buf_ptr = NULL;

static void * adc_thread(void *arg) {
    for (buf_id = 0; buf_id < ADC_BUFS; buf_id++) {
        usleep(10);
        buf_ptr[buf_id].length = ADC_SAMPLES * sizeof(complex float);
        ioctl(fd, START_XFER, &buf_id);
    }

    buf_id = 0;

    while (true) {
        ioctl(fd, FINISH_XFER, &buf_id);

        if (buf_ptr[buf_id].status != PROXY_NO_ERROR) {
            LV_LOG_ERROR("ADC transfer error");
            sleep(5);
        } else {
            complex float *samples = (complex float *) &buf_ptr[buf_id].buffer;

            dsp_adc(samples);
            ioctl(fd, START_XFER, &buf_id);
            buf_id = (buf_id + 1) % ADC_BUFS;
        }
    }
}

bool adc_init() {
    fd = open("/dev/adc", O_RDWR);
    
    if (fd < 1) {
        LV_LOG_ERROR("Unable to open ADC device file");
        return false;
    }

    buf_ptr = (struct channel_buffer *) mmap(NULL, sizeof(struct channel_buffer) * ADC_BUFS,
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (buf_ptr == MAP_FAILED) {
        LV_LOG_ERROR("Failed to mmap ADC channel");
        close(fd);
        return false;
    }

    pthread_t thread;

    pthread_create(&thread, NULL, adc_thread, NULL);
    pthread_detach(thread);

    return true;
}
