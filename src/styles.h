/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#pragma once

#include <unistd.h>
#include "lvgl/lvgl.h"

extern lv_color_t   bg_color;

extern lv_style_t   background_style;
extern lv_style_t   spectrum_style;
extern lv_style_t   freq_style;
extern lv_style_t   freq_main_style;
extern lv_style_t   waterfall_style;
extern lv_style_t   btn_style;
extern lv_style_t   msg_style;
extern lv_style_t   msg_tiny_style;
extern lv_style_t   clock_style;
extern lv_style_t   info_style;
extern lv_style_t   info_item_style;
extern lv_style_t   meter_style;
extern lv_style_t   tx_info_style;
extern lv_style_t   rx_finder_style;

extern lv_style_t   panel_top_style;
extern lv_style_t   panel_mid_style;
extern lv_style_t   panel_bottom_style;
extern lv_style_t   pannel_style;

extern lv_style_t   dialog_style;
extern lv_style_t   dialog_item_style;
extern lv_style_t   dialog_item_focus_style;
extern lv_style_t   dialog_item_edited_style;
extern lv_style_t   dialog_dropdown_list_style;

extern lv_font_t    *font_band_info;
extern lv_font_t    *font_clock_time;
extern lv_font_t    *font_clock_power;
extern lv_font_t    *font_dialog_freq;
extern lv_font_t    *font_swrscan;
extern lv_font_t    *font_meter;
extern lv_font_t    *font_panel;
extern lv_font_t    *font_textarea;
extern lv_font_t    *font_tx_info;

void styles_init();
void styles_waterfall_palette(lv_color_t *palette, uint16_t size);
