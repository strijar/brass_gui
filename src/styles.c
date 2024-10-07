/*
 *  SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *  Xiegu X6100 LVGL GUI
 *
 *  Copyright (c) 2022-2023 Belousov Oleg aka R1CBU
 */

#include "styles.h"
#include "fonts/jura.h"

#define PATH "A:/usr/share/brass/"

lv_style_t  background_style;
lv_style_t  spectrum_style;
lv_style_t  freq_style;
lv_style_t  freq_main_style;
lv_style_t  waterfall_style;
lv_style_t  btn_style;
lv_style_t  msg_style;
lv_style_t  msg_tiny_style;
lv_style_t  clock_style;
lv_style_t  info_style;
lv_style_t  info_item_style;
lv_style_t  meter_style;
lv_style_t  tx_info_style;
lv_style_t  rx_finder_style;

lv_style_t  panel_top_style;
lv_style_t  panel_mid_style;
lv_style_t  panel_bottom_style;
lv_style_t  pannel_style;

lv_style_t  dialog_style;
lv_style_t  dialog_item_style;
lv_style_t  dialog_item_focus_style;
lv_style_t  dialog_item_edited_style;
lv_style_t  dialog_dropdown_list_style;

lv_color_t  bg_color;

lv_font_t   *font_band_info = &jura_22;
lv_font_t   *font_clock_time = &jura_36;
lv_font_t   *font_clock_power = &jura_28;
lv_font_t   *font_dialog_freq = &jura_44;
lv_font_t   *font_swrscan = &jura_28;
lv_font_t   *font_meter = &jura_22;
lv_font_t   *font_panel = &jura_bold_24;
lv_font_t   *font_textarea = &jura_40;
lv_font_t   *font_tx_info = &jura_22;

lv_font_t   *font_freq = &jura_28;
lv_font_t   *font_freq_main = &jura_bold_34;
lv_font_t   *font_btn = &jura_bold_18;
lv_font_t   *font_msg = &jura_38;
lv_font_t   *font_msg_tiny = &jura_60;
lv_font_t   *font_dialog = &jura_bold_26;
lv_font_t   *font_dialog_list = &jura_bold_26;
lv_font_t   *font_info_item = &jura_bold_18;

void styles_init() {
    bg_color = lv_color_hex(0x0040A0);

    /* * */

    lv_style_init(&background_style);
    lv_style_set_bg_color(&background_style, bg_color);

    lv_style_init(&spectrum_style);
    lv_style_set_bg_color(&spectrum_style, lv_color_black());
    lv_style_set_bg_opa(&spectrum_style, LV_OPA_COVER);
    lv_style_set_radius(&spectrum_style, 0);
    lv_style_set_x(&spectrum_style, 0);
    lv_style_set_y(&spectrum_style, 0);
    lv_style_set_width(&spectrum_style, 800);
    lv_style_set_height(&spectrum_style, 480 / 3);
    lv_style_set_pad_hor(&spectrum_style, 0);

    lv_style_init(&rx_finder_style);
    lv_style_set_radius(&rx_finder_style, 0);
    lv_style_set_bg_opa(&rx_finder_style, LV_OPA_0);
    lv_style_set_width(&rx_finder_style, 800);
    lv_style_set_height(&rx_finder_style, 100);
    lv_style_set_x(&rx_finder_style, 0);
    lv_style_set_y(&rx_finder_style, 0);

    lv_style_init(&freq_style);
    lv_style_set_text_color(&freq_style, lv_color_white());
    lv_style_set_text_font(&freq_style, font_freq);
    lv_style_set_pad_ver(&freq_style, 7);
    lv_style_set_width(&freq_style, 150);
    lv_style_set_height(&freq_style, 36);
    lv_style_set_text_align(&freq_style, LV_TEXT_ALIGN_CENTER);

    lv_style_init(&freq_main_style);
    lv_style_set_text_color(&freq_main_style, lv_color_white());
    lv_style_set_text_font(&freq_main_style, font_freq_main);
    lv_style_set_pad_ver(&freq_main_style, 5);
    lv_style_set_width(&freq_main_style, 500);
    lv_style_set_height(&freq_main_style, 36);
    lv_style_set_text_align(&freq_main_style, LV_TEXT_ALIGN_CENTER);

    lv_style_init(&waterfall_style);
    lv_style_set_bg_color(&waterfall_style, lv_color_hex(0x000000));
    lv_style_set_border_color(&waterfall_style, lv_color_hex(0xAAAAAA));
    lv_style_set_border_width(&waterfall_style, 0);
    lv_style_set_radius(&waterfall_style, 0);
    lv_style_set_width(&waterfall_style, 800);
    lv_style_set_x(&waterfall_style, 0);
    lv_style_set_pad_hor(&waterfall_style, 0);
    lv_style_set_pad_ver(&waterfall_style, 0);

    lv_style_init(&btn_style);
    lv_style_set_bg_image_src(&btn_style, PATH "images/btn.bin");
    lv_style_set_bg_image_opa(&btn_style, LV_OPA_COVER);
    lv_style_set_border_width(&btn_style, 0);
    lv_style_set_text_font(&btn_style, font_btn);   // 30
    lv_style_set_text_color(&btn_style, lv_color_white());
    lv_style_set_radius(&btn_style, 0);
    lv_style_set_bg_opa(&btn_style, LV_OPA_0);

    lv_style_init(&msg_style);
    lv_style_set_text_color(&msg_style, lv_color_white());
    lv_style_set_text_font(&msg_style, font_msg); // 38
    lv_style_set_width(&msg_style, 603);
    lv_style_set_height(&msg_style, 66);
    lv_style_set_x(&msg_style, 800 / 2 - (603 / 2));
    lv_style_set_y(&msg_style, 300);
    lv_style_set_radius(&msg_style, 0);
    lv_style_set_bg_image_src(&msg_style, PATH "images/msg.bin");
    lv_style_set_bg_image_opa(&msg_style, LV_OPA_COVER);
    lv_style_set_pad_ver(&msg_style, 18);

    lv_style_init(&msg_tiny_style);
    lv_style_set_text_color(&msg_tiny_style, lv_color_white());
    lv_style_set_text_font(&msg_tiny_style, font_msg_tiny);  // 60
    lv_style_set_width(&msg_tiny_style, 324);
    lv_style_set_height(&msg_tiny_style, 66);
    lv_style_set_x(&msg_tiny_style, 800 / 2 - (324 / 2));
    lv_style_set_y(&msg_tiny_style, 160 - 66/2 + 36/2);
    lv_style_set_radius(&msg_tiny_style, 0);
    lv_style_set_bg_image_src(&msg_tiny_style, PATH "images/msg_tiny.bin");
    lv_style_set_pad_ver(&msg_tiny_style, 12);

    lv_style_init(&pannel_style);
    lv_style_set_text_color(&pannel_style, lv_color_white());
    lv_style_set_text_font(&pannel_style, font_panel);
    lv_style_set_width(&pannel_style, 795);
    lv_style_set_height(&pannel_style, 182);
    lv_style_set_x(&pannel_style, 800 / 2 - (795 / 2));
    lv_style_set_y(&pannel_style, 230);
    lv_style_set_radius(&pannel_style, 0);
    lv_style_set_bg_image_src(&pannel_style, PATH "images/pannel.bin");
    lv_style_set_bg_image_opa(&pannel_style, LV_OPA_COVER);
    lv_style_set_pad_ver(&pannel_style, 10);
    lv_style_set_pad_hor(&pannel_style, 10);

    lv_style_init(&dialog_style);
    lv_style_set_text_color(&dialog_style, lv_color_white());
    lv_style_set_text_font(&dialog_style, font_dialog);    // 36
    lv_style_set_width(&dialog_style, 796);
    lv_style_set_height(&dialog_style, 348);
    lv_style_set_x(&dialog_style, 800 / 2 - (796 / 2));
    lv_style_set_y(&dialog_style, 66);
    lv_style_set_radius(&dialog_style, 0);
    lv_style_set_bg_image_src(&dialog_style, PATH "images/dialog.bin");
    lv_style_set_bg_image_opa(&dialog_style, LV_OPA_COVER);
    lv_style_set_pad_ver(&dialog_style, 0);
    lv_style_set_pad_hor(&dialog_style, 0);

    lv_style_init(&dialog_item_style);
    lv_style_set_bg_opa(&dialog_item_style, LV_OPA_TRANSP);
    lv_style_set_text_color(&dialog_item_style, lv_color_white());

    lv_style_init(&dialog_item_focus_style);
    lv_style_set_bg_opa(&dialog_item_focus_style, 128);
    lv_style_set_text_color(&dialog_item_focus_style, lv_color_black());
    lv_style_set_border_color(&dialog_item_focus_style, lv_color_white());
    lv_style_set_border_width(&dialog_item_focus_style, 2);

    lv_style_init(&dialog_item_edited_style);
    lv_style_set_bg_opa(&dialog_item_edited_style, LV_OPA_COVER);
    lv_style_set_text_color(&dialog_item_edited_style, lv_color_black());

    lv_style_init(&dialog_dropdown_list_style);
    lv_style_set_text_font(&dialog_dropdown_list_style, font_dialog_list);  // 30

    lv_style_init(&clock_style);
    lv_style_set_text_color(&clock_style, lv_color_white());
    lv_style_set_radius(&clock_style, 0);
    lv_style_set_width(&clock_style, 206);
    lv_style_set_height(&clock_style, 61);
    lv_style_set_x(&clock_style, 800 - 206);
    lv_style_set_bg_image_src(&clock_style, PATH "images/top_short.bin");
    lv_style_set_bg_image_opa(&clock_style, LV_OPA_COVER);

    lv_style_init(&info_style);
    lv_style_set_radius(&info_style, 0);
    lv_style_set_width(&info_style, 206);
    lv_style_set_height(&info_style, 61);
    lv_style_set_x(&info_style, 0);
    lv_style_set_y(&info_style, 0);
    lv_style_set_bg_image_src(&info_style, PATH "images/top_short.bin");
    lv_style_set_bg_image_opa(&info_style, LV_OPA_COVER);
    lv_style_set_pad_ver(&info_style, 0);
    lv_style_set_border_width(&info_style, 0);
    lv_style_set_bg_opa(&info_style, LV_OPA_0);

    lv_style_init(&info_item_style);
    lv_style_set_text_font(&info_item_style, font_info_item); // 20
    lv_style_set_pad_ver(&info_item_style, 5);
    lv_style_set_radius(&info_item_style, 0);

    lv_style_init(&meter_style);
    lv_style_set_radius(&meter_style, 0);
    lv_style_set_width(&meter_style, 377);
    lv_style_set_height(&meter_style, 61);
    lv_style_set_x(&meter_style, 800 / 2 - (377 / 2));
    lv_style_set_border_width(&meter_style, 0);
    lv_style_set_bg_image_src(&meter_style, PATH "images/top_long.bin");
    lv_style_set_bg_image_opa(&meter_style, LV_OPA_COVER);
    lv_style_set_bg_opa(&meter_style, LV_OPA_0);

    lv_style_init(&tx_info_style);
    lv_style_set_radius(&tx_info_style, 0);
    lv_style_set_width(&tx_info_style, 377);
    lv_style_set_height(&tx_info_style, 123);
    lv_style_set_x(&tx_info_style, 800 / 2 - (377 / 2));
    lv_style_set_border_width(&tx_info_style, 0);
    lv_style_set_bg_image_src(&tx_info_style, PATH "images/top_big.bin");
    lv_style_set_bg_image_opa(&tx_info_style, LV_OPA_COVER);
    lv_style_set_bg_opa(&tx_info_style, LV_OPA_0);
}

void styles_waterfall_palette(lv_color_t *palette, uint16_t size) {
    lv_grad_dsc_t grad;

    grad.dir = LV_GRAD_DIR_HOR;
    grad.stops_count = 5;

    grad.stops[0].color = lv_color_hex(0x000000);
    grad.stops[1].color = lv_color_hex(0x0000FF);
    grad.stops[2].color = lv_color_hex(0xFF0000);
    grad.stops[3].color = lv_color_hex(0xFFFF00);
    grad.stops[4].color = lv_color_hex(0xFFFFFF);
    
    grad.stops[0].frac  = (size - 1) * 0.00;
    grad.stops[1].frac  = (size - 1) * 0.25;
    grad.stops[2].frac  = (size - 1) * 0.50;
    grad.stops[3].frac  = (size - 1) * 0.75;
    grad.stops[4].frac  = (size - 1) * 1.00;

    lv_opa_t opa;

    for (int i = 0; i < size; i++)
        lv_gradient_color_calculate(&grad, size, i, &palette[i], &opa);
}
