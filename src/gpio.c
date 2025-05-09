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

static struct gpiod_line    *adf_clk = NULL;
static struct gpiod_line    *adf_data = NULL;
static struct gpiod_line    *adf_le = NULL;

static struct gpiod_line    *k39 = NULL;        /* VHF/UHF_RX_TX        */
static struct gpiod_line    *k37 = NULL;        /* XVRT_HF_VHF/UHF      */
static struct gpiod_line    *k38 = NULL;        /* XVRT_VHF/UHF         */
static struct gpiod_line    *k32_k33 = NULL;    /* RELAY_LPF_VHF/UHF    */
static struct gpiod_line    *k34 = NULL;        /* RELAY_VHF_UHF_RX_TX  */
static struct gpiod_line    *k41 = NULL;        /* XVRT_VHF/UHF_RX_TX   */
static struct gpiod_line    *k23 = NULL;        /* RELAY_HF_RX_TX       */
static struct gpiod_line    *k22 = NULL;        /* RELAY_HF_VHF/UHF     */
static struct gpiod_line    *k40 = NULL;        /* SEL_VHF/UHF          */

static int16_t              current_bpf = -1;
static int16_t              current_rf_route = -1;

static struct gpiod_line * init_line(struct gpiod_chip *chip, const char *name) {
    struct gpiod_line * line = gpiod_chip_find_line(chip, name);

    if (line) {
        gpiod_line_request_output(line, "GUI", 0);
    } else {
        LV_LOG_ERROR("Unable to open gpio %s", name);
    }

    return line;
}

static void main_init() {
    struct gpiod_chip    *chip = NULL;

    chip = gpiod_chip_open_by_number(0);

    if (!chip) {
        LV_LOG_ERROR("Unable to open gpio chip 0");
        return;
    }

    line_preamp = init_line(chip, "preamp_on");
    line_tx = init_line(chip, "tx_out");
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

    for (uint8_t i = 0; i < BPF_NUM; i++)
        bpf[i] = init_line(chip, bpf_gpio[i]);
}

static void rf_3_init() {
    struct gpiod_chip    *chip = NULL;

    chip = gpiod_chip_open_by_number(3);

    if (!chip) {
        LV_LOG_ERROR("Unable to open gpio chip 3");
        return;
    }

    adf_clk = init_line(chip, "adf_clk");
    adf_data = init_line(chip, "adf_data");
    adf_le = init_line(chip, "adf_le");

    k39 = init_line(chip, "k39");
    k37 = init_line(chip, "k37");
    k38 = init_line(chip, "k38");
    k32_k33 = init_line(chip, "k32_k33");
    k34 = init_line(chip, "k34");
    k41 = init_line(chip, "k41");
    k23 = init_line(chip, "k23");
    k22 = init_line(chip, "k22");
    k40 = init_line(chip, "k40");
}

void gpio_init() {
    main_init();
    rf_2_init();
    rf_3_init();

    gpiod_line_set_value(adf_le, 0); usleep(100);
    gpiod_line_set_value(adf_le, 1); usleep(100);
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
            gpiod_line_set_value(k37, 1);
            gpiod_line_set_value(k23, 0);
            gpiod_line_set_value(k38, 0);
            gpiod_line_set_value(k40, 0);
            break;

        case RF_ROUTE_VHF:
            gpiod_line_set_value(k37, 0);
            gpiod_line_set_value(k23, 1);
            gpiod_line_set_value(k38, 0);
            gpiod_line_set_value(k40, 0);
            break;

        case RF_ROUTE_UHF:
            gpiod_line_set_value(k37, 0);
            gpiod_line_set_value(k23, 1);
            gpiod_line_set_value(k38, 1);
            gpiod_line_set_value(k40, 1);
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

void gpio_send_adf(uint32_t data) {
    gpiod_line_set_value(adf_le, 0); usleep(10);

    for (int16_t i = 31; i >= 0; i--) {
        uint32_t    mask = (1 << i);
        uint8_t     x = data & mask ? 1 : 0;

        for (int i = 0; i < 10; i++) {
            gpiod_line_set_value(adf_data, x);
            usleep(1);
        }

        gpiod_line_set_value(adf_clk, 1);
        gpiod_line_set_value(adf_clk, 0);
    }

    gpiod_line_set_value(adf_le, 1); usleep(10);
}
