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

extern lv_style_t   waterfall_style;
extern lv_style_t   msg_style;
extern lv_style_t   msg_tiny_style;
extern lv_style_t   tx_info_style;
extern lv_style_t   rx_finder_style;

extern lv_style_t   *pannel_style;

extern lv_style_t   *dialog_style;
extern lv_style_t   *dialog_no_buttons_style;
extern lv_style_t   *dialog_grid_style;
extern lv_style_t   *dialog_title_style;
extern lv_style_t   *dialog_title_label_style;
extern lv_style_t   *dialog_label_style;
extern lv_style_t   *dialog_item_style;
extern lv_style_t   *dialog_label_style;
extern lv_style_t   *dialog_item_focus_style;
extern lv_style_t   *dialog_item_edited_style;
extern lv_style_t   *dialog_item_cursor_style;

extern lv_style_t   *dropdown_list_style;

extern lv_style_t   *slider_style;
extern lv_style_t   *slider_indicator_style;
extern lv_style_t   *slider_knob_style;
extern lv_style_t   *slider_indicator_edited_style;
extern lv_style_t   *slider_knob_edited_style;

extern lv_style_t   *switch_style;
extern lv_style_t   *switch_indicator_style;
extern lv_style_t   *switch_knob_style;
extern lv_style_t   *switch_indicator_checked_style;
extern lv_style_t   *switch_knob_checked_style;

extern lv_font_t    *font_dialog_freq;
extern lv_font_t    *font_swrscan;
extern lv_font_t    *font_panel;
extern lv_font_t    *font_textarea;
extern lv_font_t    *font_tx_info;

void styles_init();
