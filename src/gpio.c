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

/* Main unit */

static struct gpiod_chip    *chip_main = NULL;
static struct gpiod_line    *line_preamp = NULL;
static struct gpiod_line    *line_tx = NULL;

void gpio_init() {
    /* Main unit */

    chip_main = gpiod_chip_open_by_number(0);

    if (!chip_main) {
        LV_LOG_ERROR("Unable to open gpio chip 0");
        return;
    }

    line_preamp = gpiod_chip_find_line(chip_main, "preamp_on");

    if (line_preamp) {
        gpiod_line_request_output(line_preamp, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio preamp_on line");
    }

    line_tx = gpiod_chip_find_line(chip_main, "tx_out");

    if (line_tx) {
        gpiod_line_request_output(line_tx, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio tx_out line");
    }
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
