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

typedef struct {
    uint32_t    fft_dds_step;
    uint32_t    fft_rate;
    uint32_t    adc_dds_step;
} control_reg_t;

static int              fd;
static control_reg_t    *control_reg;

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

void control_set_rx_freq(uint64_t freq) {
    uint64_t f = freq - 585;

    control_reg->fft_dds_step = (uint32_t) floor(f / 122.88e6 * (1 << 30) + 0.5);
    control_reg->adc_dds_step = control_reg->fft_dds_step;
}
