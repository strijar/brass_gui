/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <math.h>
#include <stddef.h>

#include "lvgl/lvgl.h"
#include "control.h"
#include "src/params.h"

typedef struct {
    uint32_t    fft_dds_step;
    uint32_t    fft_rate;
    uint32_t    adc_dds_step;
} control_reg_t;

static int              fd;
static control_reg_t    *control_reg;

static uint64_t         rx_freq;
static uint64_t         fft_freq;

void control_init() {
    fd = open("/dev/uio0", O_RDWR | O_SYNC);
    
    if (fd < 1) {
        LV_LOG_ERROR("Unable to open Radio control device file");
        return;
    }

    control_reg = (control_reg_t *) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (control_reg == MAP_FAILED) {
        close(fd);
        LV_LOG_ERROR("Failed to mmap Radio control reg");
    }
}

void control_update() {
    control_set_rx_freq(rx_freq);
    control_set_fft_freq(fft_freq);
}

void control_set_rx_freq(uint64_t freq) {
    float txo = 122880000.0f + params.txo_offset.x;

    rx_freq = freq;
    control_reg->adc_dds_step = (uint32_t) floor(freq / txo * (1 << 30) + 0.5f);
}

void control_set_fft_freq(uint64_t freq) {
    float txo = 122880000.0f + params.txo_offset.x;

    fft_freq = freq;
    control_reg->fft_dds_step = (uint32_t) floor(freq / txo * (1 << 30) + 0.5f);
}

void control_set_fft_rate(uint32_t rate) {
    control_reg->fft_rate = rate;
}
