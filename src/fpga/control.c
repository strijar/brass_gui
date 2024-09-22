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
} rx_control_reg_t;

typedef struct {
    uint32_t    dac_dds_step;
} tx_control_reg_t;

static int              rx_fd;
static int              tx_fd;

static rx_control_reg_t *rx_control_reg;
static tx_control_reg_t *tx_control_reg;

static uint64_t         rx_freq;
static uint64_t         tx_freq;
static uint64_t         fft_freq;

void control_init() {
    /* RX */

    rx_fd = open("/dev/uio0", O_RDWR | O_SYNC);
    
    if (rx_fd < 1) {
        LV_LOG_ERROR("Unable to open RX Radio control device file");
        return;
    }

    rx_control_reg = (rx_control_reg_t *) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, rx_fd, 0);

    if (rx_control_reg == MAP_FAILED) {
        close(rx_fd);
        LV_LOG_ERROR("Failed to mmap RX Radio control reg");
    }

    /* TX */

    tx_fd = open("/dev/uio1", O_RDWR | O_SYNC);
    
    if (tx_fd < 1) {
        LV_LOG_ERROR("Unable to open TX Radio control device file");
        return;
    }

    tx_control_reg = (tx_control_reg_t *) mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED, tx_fd, 0);

    if (tx_control_reg == MAP_FAILED) {
        close(tx_fd);
        LV_LOG_ERROR("Failed to mmap TX Radio control reg");
    }
}

void control_update() {
    control_set_rx_freq(rx_freq);
    control_set_tx_freq(tx_freq);
    control_set_fft_freq(fft_freq);
}

void control_set_rx_freq(uint64_t freq) {
    float txo = 122880000.0f + params.txo_offset.x;

    rx_freq = freq;
    rx_control_reg->adc_dds_step = (uint32_t) floor(freq / txo * (1 << 30) + 0.5f);
}

void control_set_tx_freq(uint64_t freq) {
    float txo = 122880000.0f + params.txo_offset.x;

    tx_freq = freq;
    tx_control_reg->dac_dds_step = (uint32_t) floor(freq / txo * (1 << 30) + 0.5f);
}

void control_set_fft_freq(uint64_t freq) {
    float txo = 122880000.0f + params.txo_offset.x;

    fft_freq = freq;
    rx_control_reg->fft_dds_step = (uint32_t) floor(freq / txo * (1 << 30) + 0.5f);
}

void control_set_fft_rate(uint32_t rate) {
    rx_control_reg->fft_rate = rate;
}
