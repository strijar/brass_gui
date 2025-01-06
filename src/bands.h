/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "settings/bands.h"

extern band_settings_t  *band_settings;

void bands_activate(band_t *band, bool touch_freq);
void bands_change(bool up);
bool bands_find(uint64_t freq);
bool bands_prior(uint64_t freq);
bool bands_changed(uint64_t freq);
