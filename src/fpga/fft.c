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
#include "fft.h"
#include "adc.h"
#include "dma-proxy.h"

#define FFT_BUFS                2

static int                      fd;
static int                      buf_id = 0;
static struct channel_buffer    *buf_ptr = NULL;

static void * fft_thread(void *arg) { 
    for (buf_id = 0; buf_id < FFT_BUFS; buf_id++) {
        usleep(10);
        buf_ptr[buf_id].length = FFT_SAMPLES * sizeof(complex float);
        ioctl(fd, START_XFER, &buf_id);
    }

    buf_id = 0;

    while (true) {
        ioctl(fd, FINISH_XFER, &buf_id);
        
        if (buf_ptr[buf_id].status != PROXY_NO_ERROR) {
            LV_LOG_ERROR("FFT transfer error");
            sleep(5);
        } else {
            complex float *samples = (complex float *) &buf_ptr[buf_id].buffer;

            dsp_fft(samples);
            ioctl(fd, START_XFER, &buf_id);
            buf_id = (buf_id + 1) % FFT_BUFS;

            usleep(10);
        }
    }
}

bool fft_init() {
    fd = open("/dev/fft", O_RDWR);
    
    if (fd < 1) {
        LV_LOG_ERROR("Unable to open FFT device file");
        return false;
    }

    buf_ptr = (struct channel_buffer *) mmap(NULL, sizeof(struct channel_buffer) * FFT_BUFS,
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (buf_ptr == MAP_FAILED) {
        LV_LOG_ERROR("Failed to mmap FFT channel");
        close(fd);
        return false;
    }

    pthread_t thread;

    pthread_create(&thread, NULL, fft_thread, NULL);
    pthread_detach(thread);

    LV_LOG_INFO("ok");

    return true;
}
