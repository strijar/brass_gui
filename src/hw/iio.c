/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <iio.h>
#include "lvgl/lvgl.h"
#include "iio.h"

struct iio_context  *ctx = NULL;

struct iio_device   *vref = NULL;
struct iio_channel  *vref_channel = NULL;

void iio_init() {
    ctx = iio_create_local_context();

    if (ctx == NULL) {
        LV_LOG_ERROR("Create context");
        return;
    }

    vref = iio_context_find_device(ctx, "mcp4725");

    if (vref == NULL) {
        LV_LOG_ERROR("Find mcp4725");
        return;
    }

    vref_channel = iio_device_find_channel(vref, "voltage0", true);

    if (vref_channel == NULL) {
        LV_LOG_ERROR("Find mcp4725 channel");
        return;
    }
}

void iio_set_vref(uint16_t data) {
    if (iio_channel_attr_write_longlong(vref_channel, "raw", data) < 0) {
        LV_LOG_ERROR("Write to VRef");
    }
}
