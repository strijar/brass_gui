/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2025 Belousov Oleg aka R1CBU
 */

#include <unistd.h>
#include <pthread.h>
#include <iio.h>

#include "lvgl/lvgl.h"
#include "iio.h"
#include "src/hkey.h"

static struct iio_channel  *vref = NULL;
static struct iio_channel  *hkeys_x = NULL;
static struct iio_channel  *hkeys_y = NULL;
static struct iio_channel  *pwr_ref = NULL;
static struct iio_channel  *pwr_fwd = NULL;

static void * iio_thread(void *arg) {
    while (true) {
        long long x, y, ref, fwd;

        iio_channel_attr_read_longlong(hkeys_x, "raw", &x);
        iio_channel_attr_read_longlong(hkeys_y, "raw", &y);
        iio_channel_attr_read_longlong(pwr_ref, "raw", &ref);
        iio_channel_attr_read_longlong(pwr_fwd, "raw", &fwd);

        hkey_put(x, y);
        usleep(1000);
    }
}

void iio_init() {
    struct iio_context  *ctx = NULL;
    struct iio_device   *dev = NULL;

    ctx = iio_create_local_context();

    if (ctx == NULL) {
        LV_LOG_ERROR("Create context");
        return;
    }

    /* * */

    dev = iio_context_find_device(ctx, "mcp4725");

    if (dev == NULL) {
        LV_LOG_ERROR("Find mcp4725");
        return;
    }

    vref = iio_device_find_channel(dev, "voltage0", true);

    if (vref == NULL) {
        LV_LOG_ERROR("Find mcp4725 channel");
        return;
    }

    /* * */

    dev = iio_context_find_device(ctx, "ads1015");

    if (dev == NULL) {
        LV_LOG_ERROR("Find ads1015");
        return;
    }

    hkeys_x = iio_device_find_channel(dev, "voltage0", false);

    if (hkeys_x == NULL) {
        LV_LOG_ERROR("Find ads1015 channel");
        return;
    }

    hkeys_y = iio_device_find_channel(dev, "voltage1", false);

    if (hkeys_y == NULL) {
        LV_LOG_ERROR("Find ads1015 channel");
        return;
    }

    pwr_ref = iio_device_find_channel(dev, "voltage2", false);

    if (pwr_ref == NULL) {
        LV_LOG_ERROR("Find ads1015 channel");
        return;
    }

    pwr_fwd = iio_device_find_channel(dev, "voltage3", false);

    if (pwr_fwd == NULL) {
        LV_LOG_ERROR("Find ads1015 channel");
        return;
    }

    /* Thread */

    pthread_t thread;

    pthread_create(&thread, NULL, iio_thread, NULL);
    pthread_detach(thread);
}

void iio_set_vref(uint16_t data) {
    if (iio_channel_attr_write_longlong(vref, "raw", data) < 0) {
        LV_LOG_ERROR("Write to VRef");
    }
}
