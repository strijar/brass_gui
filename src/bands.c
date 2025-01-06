/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "lvgl/lvgl.h"
#include "bands.h"
#include "params.h"
#include "radio.h"
#include "info.h"
#include "waterfall.h"
#include "main_screen.h"
#include "pannel.h"
#include "voice.h"
#include "settings/bands.h"
#include "msgs.h"

static op_work_t  op_dummy = {
    .rx = 14100000,
    .tx = 14100000,
    .fft = 14100000,
    .mode = RADIO_MODE_USB,
    .split = SPLIT_NONE
};

band_settings_t     *band_settings = NULL;

void bands_activate(band_t *band, bool touch_freq) {
    band_settings = &band->settings;
    op_work = &band->work;

    if (touch_freq) {
        if (op_work->rx == 0) {
            op_work->rx = band_settings->start / 2 + band_settings->stop / 2;
        }

        if (op_work->tx == 0) {
            op_work->tx = band_settings->start / 2 + band_settings->stop / 2;
        }

        if (op_work->fft == 0) {
            op_work->fft = band_settings->start / 2 + band_settings->stop / 2;
        }
    }

    op_work_activate(touch_freq);
    lv_msg_send(MSG_MODE_CHANGED, &op_work->mode);
}

void bands_change(bool up) {
    uint64_t    freq = op_work->rx;
    int32_t     i;

    band_settings = NULL;

    if (up) {
        i = 0;

        while (true) {
            band_t *band = &bands->item[i];

            if (band->settings.jump && band->settings.start > freq) {
                bands_activate(band, true);
                break;
            }

            i++;

            if (i > bands->count) {
                i = 0;
            }
        }
    } else {
        i = bands->count - 1;

        while (true) {
            band_t *band = &bands->item[i];

            if (band->settings.jump && band->settings.stop < freq) {
                bands_activate(band, true);
                break;
            }

            i--;

            if (i < 0) {
                i = bands->count - 1;
            }
        }
    }

    main_screen_band_changed();
    voice_say_text_fmt("Band %s", band_settings->label);
}

bool bands_find(uint64_t freq) {
    for (int32_t i = 0; i < bands->count; i++) {
        band_t *band = &bands->item[i];

        if (freq > band->settings.start && freq < band->settings.stop) {
            bands_activate(band, false);
            return true;
        }
    }

    band_settings = NULL;
    op_dummy = *op_work;
    op_work = &op_dummy;

    return false;
}

bool bands_prior(uint64_t freq) {
    return band_settings && freq > band_settings->start && freq < band_settings->stop;
}

bool bands_changed(uint64_t freq) {
    if (bands_prior(freq)) {
        return false;
    }

    return bands_find(freq);
}
