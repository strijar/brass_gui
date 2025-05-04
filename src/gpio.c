/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <gpiod.h>
#include "lvgl/lvgl.h"

#include "gpio.h"
#include "settings/options.h"

/* Main unit */

static struct gpiod_line    *line_preamp = NULL;
static struct gpiod_line    *line_tx = NULL;

/* RF unit */

static struct gpiod_line    *bpf[BPF_NUM];
static struct gpiod_line    *xvrt_hf = NULL;

static int16_t              current_bpf = -1;
static int16_t              current_rf_route = -1;

static void main_init() {
    struct gpiod_chip    *chip = NULL;

    chip = gpiod_chip_open_by_number(0);

    if (!chip) {
        LV_LOG_ERROR("Unable to open gpio chip 0");
        return;
    }

    line_preamp = gpiod_chip_find_line(chip, "preamp_on");

    if (line_preamp) {
        gpiod_line_request_output(line_preamp, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio preamp_on line");
    }

    line_tx = gpiod_chip_find_line(chip, "tx_out");

    if (line_tx) {
        gpiod_line_request_output(line_tx, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio tx_out line");
    }
}

static void rf_2_init() {
    struct gpiod_chip    *chip = NULL;

    chip = gpiod_chip_open_by_number(2);

    if (!chip) {
        LV_LOG_ERROR("Unable to open gpio chip 2");
        return;
    }

    const char* bpf_gpio[BPF_NUM] = {
        "bpf_lf", "bpf_160", "bpf_80", "bpf_40",
        "bpf_30_20", "bpf_17_15", "bpf_12_10", "bpf_6"
    };

    for (uint8_t i = 0; i < BPF_NUM; i++) {
        bpf[i] = gpiod_chip_find_line(chip, bpf_gpio[i]);

        if (bpf[i]) {
            gpiod_line_request_output(bpf[i], "GUI", 0);
        } else {
            LV_LOG_ERROR("Unable to open gpio %s line", bpf_gpio[i]);
        }
    }
}

static void rf_3_init() {
    struct gpiod_chip    *chip = NULL;

    chip = gpiod_chip_open_by_number(3);

    if (!chip) {
        LV_LOG_ERROR("Unable to open gpio chip 3");
        return;
    }

    xvrt_hf = gpiod_chip_find_line(chip, "xvrt_hf_vhf/uhf");

    if (xvrt_hf) {
        gpiod_line_request_output(xvrt_hf, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio xvrt_hf_vhf/uhf line");
    }
}

void gpio_init() {
    main_init();
    rf_2_init();
    rf_3_init();
}

void gpio_set_preamp(bool on) {
    if (line_preamp) {
        gpiod_line_set_value(line_preamp, on ? 0 : 1);
    }
}

void gpio_set_tx(bool on) {
    if (line_tx) {
        gpiod_line_set_value(line_tx, on ? 1 : 0);
    }
}

void gpio_set_rf_route(rf_route_t route) {
    if (current_rf_route == route)
        return;

    switch (route) {
        case RF_ROUTE_HF:
            gpiod_line_set_value(xvrt_hf, 1);
            break;

        case RF_ROUTE_VHF:
            gpiod_line_set_value(xvrt_hf, 0);
            break;

        case RF_ROUTE_UHF:
            gpiod_line_set_value(xvrt_hf, 0);
            break;
    }

    current_rf_route = route;
}

void gpio_set_rf_bpf(uint8_t index) {
    if (current_bpf == index)
        return;

    for (uint8_t i = 0; i < BPF_NUM; i++)
        gpiod_line_set_value(bpf[i], i == index ? 1 : 0);

    current_bpf = index;
}
