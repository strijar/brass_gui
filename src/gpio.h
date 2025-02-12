/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  TRX Brass LVGL GUI
 *
 *  Copyright (c) 2022-2024 Belousov Oleg aka R1CBU
 */

#pragma once

#include <stdbool.h>

void gpio_init();

void gpio_set_preamp(bool on);
void gpio_set_tx(bool on);
