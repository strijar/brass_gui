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
#include "dac.h"
#include "dma-proxy.h"

#define DAC_BUFS                4

static int                      fd;
static int                      buf_id = 0;
static struct channel_buffer    *buf_ptr = NULL;

static void * dac_thread(void *arg) {
    for (buf_id = 0; buf_id < DAC_BUFS; buf_id++) {
        usleep(100);
        buf_ptr[buf_id].length = DAC_SAMPLES * sizeof(complex float);
        memset(buf_ptr[buf_id].buffer, 0, buf_ptr[buf_id].length);
        ioctl(fd, START_XFER, &buf_id);
    }

    buf_id = 0;

    while (true) {
        ioctl(fd, FINISH_XFER, &buf_id);

        size_t size = dsp_dac((float complex *) &buf_ptr[buf_id].buffer, BUFFER_SIZE / sizeof(complex float));
        
        if (size > 0) {
            buf_ptr[buf_id].length = size * sizeof(complex float);
        } else {
            buf_ptr[buf_id].length = DAC_SAMPLES * sizeof(complex float);
            memset(buf_ptr[buf_id].buffer, 0, DAC_SAMPLES * sizeof(complex float));
        }
       
        ioctl(fd, START_XFER, &buf_id);
        buf_id = (buf_id + 1) % DAC_BUFS;
    }
}

bool dac_init() {
    fd = open("/dev/dac", O_RDWR);
    
    if (fd < 1) {
        LV_LOG_ERROR("Unable to open DAC device file");
        return false;
    }

    buf_ptr = (struct channel_buffer *) mmap(NULL, sizeof(struct channel_buffer) * DAC_BUFS,
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (buf_ptr == MAP_FAILED) {
        LV_LOG_ERROR("Failed to mmap DAC channel");
        close(fd);
        return false;
    }

    pthread_t thread;

    pthread_create(&thread, NULL, dac_thread, NULL);
    pthread_detach(thread);

    return true;
}
