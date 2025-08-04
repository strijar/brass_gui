import lv
from lv_const import *

# # #

bandinfo_indicator_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Medium.ttf", 20)
bandinfo_marker_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Bold.ttf", 20)

freqs_center_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Bold.ttf", 30)
freqs_range_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Regular.ttf", 20)

msg_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Regular.ttf", 36)
msg_tiny_font = lv.load_font("/usr/share/brass/font/Jura.ttf", 52)

button_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Medium.ttf", 15)
pannel_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Regular.ttf", 18)
smeter_font = lv.load_font("/usr/share/brass/font/JetBrainsMono-Medium.ttf", 20)

# # #

spectrum_style = lv.style()

spectrum_style.set_radius(0)
spectrum_style.set_bg_color(0x040A1B)
spectrum_style.set_bg_opa(LV_OPA_COVER)

# # #

spectrum_lines_style = lv.style()

spectrum_lines_style.set_line_width(2)
spectrum_lines_style.set_line_color(0xFFC557)

# # #

spectrum_peaks_style = lv.style()

spectrum_peaks_style.set_line_width(1)
spectrum_peaks_style.set_line_color(0x845000)

# # #

finder_style = lv.style()

finder_style.set_bg_opa(LV_OPA_0)
finder_style.set_radius(0)

# # #

tx_finder_indicator_style = lv.style()

tx_finder_indicator_style.set_bg_color(0xDF1B73)
tx_finder_indicator_style.set_bg_opa(LV_OPA_70)
tx_finder_indicator_style.set_line_width(1)

# # #

rx_finder_indicator_style = lv.style()

rx_finder_indicator_style.set_bg_color(0x0F2946)
rx_finder_indicator_style.set_bg_opa(LV_OPA_70)
rx_finder_indicator_style.set_line_width(1)

# # #

rec_off_style = lv.style()

rec_off_style.set_line_color(0xFFFFFF)
rec_off_style.set_line_opa(LV_OPA_50)

# # #

rec_on_style = lv.style()

rec_on_style.set_line_color(0xFF0000)
rec_on_style.set_line_opa(LV_OPA_COVER)

# # #

waterfall_style = lv.style()

waterfall_style.set_bg_color(0x000000)
waterfall_style.set_bg_opa(LV_OPA_COVER)
waterfall_style.set_radius(0)

# # #

bandinfo_style = lv.style()

bandinfo_style.set_radius(0)
bandinfo_style.set_border_width(0)
bandinfo_style.set_bg_opa(LV_OPA_0)

# # #

bandinfo_indicator_style = lv.style()

bandinfo_indicator_style.set_bg_color(0x141F36)
bandinfo_indicator_style.set_bg_opa(LV_OPA_90)
bandinfo_indicator_style.set_border_width(1)
bandinfo_indicator_style.set_border_color(0xFFCF85)
bandinfo_indicator_style.set_border_opa(LV_OPA_50)
bandinfo_indicator_style.set_text_color(0xFFCF85)
bandinfo_indicator_style.set_text_font(bandinfo_indicator_font)

# # #

bandinfo_marker_style = lv.style()

bandinfo_marker_style.set_bg_color(0xFFCF85)
bandinfo_marker_style.set_bg_opa(LV_OPA_COVER)
bandinfo_marker_style.set_text_color(0x000000)
bandinfo_marker_style.set_text_font(bandinfo_marker_font)

# # #

main_freqs_style = lv.style()

main_freqs_style.set_radius(0)
main_freqs_style.set_border_width(0)
main_freqs_style.set_bg_opa(LV_OPA_TRANSP)
main_freqs_style.set_bg_img_src("A:/usr/share/brass/images/middle.bin")
main_freqs_style.set_bg_img_opa(LV_OPA_COVER)

# # #

main_freqs_center_style = lv.style()

main_freqs_center_style.set_text_color(0xFFC557)
main_freqs_center_style.set_text_font(freqs_center_font)
main_freqs_center_style.set_text_align(LV_TEXT_ALIGN_CENTER)

# # #

main_freqs_left_style = lv.style()

main_freqs_left_style.set_text_color(0xFFCF85)
main_freqs_left_style.set_text_font(freqs_range_font)
main_freqs_left_style.set_text_align(LV_TEXT_ALIGN_LEFT)

# # #

main_freqs_right_style = lv.style()

main_freqs_right_style.set_text_color(0xFFCF85)
main_freqs_right_style.set_text_font(freqs_range_font)
main_freqs_right_style.set_text_align(LV_TEXT_ALIGN_RIGHT)

# # #

msg_style = lv.style()

msg_style.set_bg_img_src("A:/usr/share/brass/images/msg.bin")
msg_style.set_bg_img_opa(LV_OPA_COVER)
msg_style.set_text_font(msg_font)
msg_style.set_text_align(LV_TEXT_ALIGN_CENTER)

# # #

msg_label_normal_style = lv.style()

msg_label_normal_style.set_text_color(0xFFCF85)

# # #

msg_label_select_style = lv.style()

msg_label_select_style.set_text_color(0x845000)

# # #

msg_tiny_style = lv.style()

msg_tiny_style.set_bg_img_src("A:/usr/share/brass/images/msg_tiny.bin")
msg_tiny_style.set_bg_img_opa(LV_OPA_COVER)

# # #

msg_tiny_label_style = lv.style()

msg_tiny_label_style.set_text_color(0xFFFFFF)
msg_tiny_label_style.set_text_font(msg_tiny_font)
msg_tiny_label_style.set_text_align(LV_TEXT_ALIGN_CENTER)

# # #

top_style = lv.style()

top_style.set_radius(0)
top_style.set_border_width(0)
top_style.set_bg_opa(LV_OPA_TRANSP)
top_style.set_bg_img_src("A:/usr/share/brass/images/top.bin")
top_style.set_bg_img_opa(LV_OPA_COVER)

# # #

buttons_style = lv.style()

buttons_style.set_radius(0)
buttons_style.set_border_width(0)
buttons_style.set_bg_opa(LV_OPA_TRANSP)
buttons_style.set_bg_img_src("A:/usr/share/brass/images/buttons.bin")
buttons_style.set_bg_img_opa(LV_OPA_COVER)

# # #

button_style = lv.style()

button_style.set_radius(0)
button_style.set_border_width(0)
button_style.set_text_color(0xFFCF85)
button_style.set_text_font(button_font)
button_style.set_bg_opa(LV_OPA_TRANSP)

# # #

smeter_style = lv.style()

smeter_style.set_radius(0)
smeter_style.set_border_width(0)
smeter_style.set_bg_opa(LV_OPA_TRANSP)
smeter_style.set_text_color(0xFFCF85)
smeter_style.set_text_font(smeter_font)

smeter_slice_style = lv.style()

smeter_slice_style.set_width(10)
smeter_slice_style.set_pad_column(3)

smeter_part1_style = lv.style()

smeter_part1_style.set_bg_color(0x2E3442)
smeter_part1_style.set_bg_opa(LV_OPA_COVER)

smeter_part2_style = lv.style()

smeter_part2_style.set_bg_color(0x3F526C)
smeter_part2_style.set_bg_opa(LV_OPA_COVER)

smeter_part3_style = lv.style()

smeter_part3_style.set_bg_color(0x5D769A)
smeter_part3_style.set_bg_opa(LV_OPA_COVER)

smeter_part4_style = lv.style()

smeter_part4_style.set_bg_color(0xFFC940)
smeter_part4_style.set_bg_opa(LV_OPA_COVER)

# # # # #

pannel_style = lv.style()

pannel_style.set_radius(0)
pannel_style.set_text_color(0xFFCF85)
pannel_style.set_text_font(pannel_font)
pannel_style.set_bg_img_src("A:/usr/share/brass/images/pannel.bin")
pannel_style.set_bg_img_opa(LV_OPA_COVER)
