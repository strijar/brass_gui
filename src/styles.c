/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "styles.h"
#include "fonts/jura.h"
#include "python/python.h"

#define PATH "A:/usr/share/brass/"

lv_style_t  waterfall_style;
lv_style_t  msg_style;
lv_style_t  msg_tiny_style;
lv_style_t  tx_info_style;
lv_style_t  rx_finder_style;

lv_style_t  *pannel_style;

lv_style_t  *dialog_style;
lv_style_t  *dialog_no_buttons_style;
lv_style_t  *dialog_grid_style;
lv_style_t  *dialog_item_style;
lv_style_t  *dialog_title_style;
lv_style_t  *dialog_title_label_style;
lv_style_t  *dialog_label_style;
lv_style_t  *dialog_item_focus_style;
lv_style_t  *dialog_item_edited_style;
lv_style_t  *dialog_item_cursor_style;

lv_style_t  *dropdown_list_style;

lv_style_t  *slider_style;
lv_style_t  *slider_indicator_style;
lv_style_t  *slider_knob_style;
lv_style_t  *slider_indicator_edited_style;
lv_style_t  *slider_knob_edited_style;

lv_style_t  *switch_style;
lv_style_t  *switch_indicator_style;
lv_style_t  *switch_knob_style;
lv_style_t  *switch_indicator_checked_style;
lv_style_t  *switch_knob_checked_style;

lv_color_t  bg_color;

lv_font_t   *font_dialog_freq = &jura_44;
lv_font_t   *font_swrscan = &jura_28;
lv_font_t   *font_textarea = &jura_40;
lv_font_t   *font_tx_info = &jura_22;

lv_font_t   *font_msg = &jura_38;
lv_font_t   *font_dialog = &jura_bold_26;
lv_font_t   *font_dialog_list = &jura_bold_26;

static lv_font_t * load_font(const char *path, lv_coord_t font_size) {
    lv_ft_info_t    info;

    info.name = path;
    info.weight = font_size;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;

    lv_ft_font_init(&info);

    return info.font;
}

void styles_init() {
    bg_color = lv_color_hex(0x002550);

    /* * */

    lv_style_init(&rx_finder_style);
    lv_style_set_radius(&rx_finder_style, 0);
    lv_style_set_bg_opa(&rx_finder_style, LV_OPA_0);
    lv_style_set_width(&rx_finder_style, 800);
    lv_style_set_height(&rx_finder_style, 100);
    lv_style_set_x(&rx_finder_style, 0);
    lv_style_set_y(&rx_finder_style, 0);

    lv_style_init(&waterfall_style);
    lv_style_set_bg_color(&waterfall_style, lv_color_hex(0x000000));
    lv_style_set_border_color(&waterfall_style, lv_color_hex(0xAAAAAA));
    lv_style_set_border_width(&waterfall_style, 0);
    lv_style_set_radius(&waterfall_style, 0);
    lv_style_set_width(&waterfall_style, 800);
    lv_style_set_x(&waterfall_style, 0);
    lv_style_set_pad_hor(&waterfall_style, 0);
    lv_style_set_pad_ver(&waterfall_style, 0);

    lv_style_init(&msg_style);
    lv_style_set_text_color(&msg_style, lv_color_white());
    lv_style_set_text_font(&msg_style, font_msg); // 38
    lv_style_set_width(&msg_style, 603);
    lv_style_set_height(&msg_style, 76);
    lv_style_set_x(&msg_style, 800 / 2 - (603 / 2));
    lv_style_set_y(&msg_style, 300);
    lv_style_set_radius(&msg_style, 0);
    lv_style_set_bg_img_src(&msg_style, PATH "images/msg.bin");
    lv_style_set_bg_img_opa(&msg_style, LV_OPA_COVER);
    lv_style_set_pad_ver(&msg_style, 18);

    lv_style_init(&msg_tiny_style);
    lv_style_set_text_color(&msg_tiny_style, lv_color_white());
    lv_style_set_text_font(&msg_tiny_style, load_font("/usr/share/brass/font/Jura.ttf", 40));
    lv_style_set_width(&msg_tiny_style, 324);
    lv_style_set_height(&msg_tiny_style, 76);
    lv_style_set_x(&msg_tiny_style, 800 / 2 - (324 / 2));
    lv_style_set_y(&msg_tiny_style, 160 - 66/2 + 36/2);
    lv_style_set_radius(&msg_tiny_style, 0);
    lv_style_set_bg_img_src(&msg_tiny_style, PATH "images/msg_tiny.bin");

    pannel_style = python_get_style("pannel_style");
    dialog_style = python_get_style("dialog_style");
    dialog_no_buttons_style = python_get_style("dialog_no_buttons_style");
    dialog_grid_style = python_get_style("dialog_grid_style");
    dialog_title_style = python_get_style("dialog_title_style");
    dialog_title_label_style = python_get_style("dialog_title_label_style");
    dialog_label_style = python_get_style("dialog_label_style");
    dialog_item_style = python_get_style("dialog_item_style");
    dialog_item_focus_style = python_get_style("dialog_item_focus_style");
    dialog_item_edited_style = python_get_style("dialog_item_edited_style");
    dialog_item_cursor_style = python_get_style("dialog_item_cursor_style");

    dropdown_list_style = python_get_style("dropdown_list_style");

    slider_style = python_get_style("slider_style");
    slider_indicator_style = python_get_style("slider_indicator_style");
    slider_knob_style = python_get_style("slider_knob_style");
    slider_indicator_edited_style = python_get_style("slider_indicator_edited_style");
    slider_knob_edited_style = python_get_style("slider_knob_edited_style");

    switch_style = python_get_style("switch_style");
    switch_indicator_style = python_get_style("switch_indicator_style");
    switch_knob_style = python_get_style("switch_knob_style");
    switch_indicator_checked_style = python_get_style("switch_indicator_checked_style");
    switch_knob_checked_style = python_get_style("switch_knob_checked_style");

    lv_style_init(&tx_info_style);
    lv_style_set_radius(&tx_info_style, 0);
    lv_style_set_width(&tx_info_style, 377);
    lv_style_set_height(&tx_info_style, 123);
    lv_style_set_x(&tx_info_style, 800 / 2 - (377 / 2));
    lv_style_set_border_width(&tx_info_style, 0);
    lv_style_set_bg_img_src(&tx_info_style, PATH "images/top_big.bin");
    lv_style_set_bg_img_opa(&tx_info_style, LV_OPA_COVER);
    lv_style_set_bg_opa(&tx_info_style, LV_OPA_0);
}
