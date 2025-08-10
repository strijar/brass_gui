import lv
from lv_const import *

from style import *

# # #

spectrum_style.set_x(0)
spectrum_style.set_y(59)
spectrum_style.set_width(800)
spectrum_style.set_height(101)
spectrum_style.set_pad_hor(0)

spectrum_tx_finder_style = lv.style()

spectrum_tx_finder_style.set_x(0)
spectrum_tx_finder_style.set_y(0)
spectrum_tx_finder_style.set_width(800)
spectrum_tx_finder_style.set_height(50)

spectrum_rx_finder_style = lv.style()

spectrum_rx_finder_style.set_x(0)
spectrum_rx_finder_style.set_y(50)
spectrum_rx_finder_style.set_width(800)
spectrum_rx_finder_style.set_height(50)

# # #

main_freqs_style.set_x(0)
main_freqs_style.set_y(160 - 20)
main_freqs_style.set_width(800)
main_freqs_style.set_height(82)
main_freqs_style.set_pad_hor(0)
main_freqs_style.set_pad_ver(0)

main_freqs_center_style.set_x(150)
main_freqs_center_style.set_y(20)
main_freqs_center_style.set_width(500)
main_freqs_center_style.set_height(40)

main_freqs_left_style.set_x(20)
main_freqs_left_style.set_y(20)
main_freqs_left_style.set_pad_ver(8)
main_freqs_left_style.set_width(150)
main_freqs_left_style.set_height(60)

main_freqs_right_style.set_x(800 - 150 - 20)
main_freqs_right_style.set_y(20)
main_freqs_right_style.set_pad_ver(8)
main_freqs_right_style.set_width(150)
main_freqs_right_style.set_height(60)

# # #

waterfall_style.set_x(0)
waterfall_style.set_y(161 + 42 - 1)
waterfall_style.set_width(800)
waterfall_style.set_height(221)
waterfall_style.set_pad_hor(0)
waterfall_style.set_pad_ver(0)

waterfall_rx_finder_style = lv.style()

waterfall_rx_finder_style.set_x(0)
waterfall_rx_finder_style.set_y(0)
waterfall_rx_finder_style.set_width(800)
waterfall_rx_finder_style.set_height(221)

waterfall_bandinfo_style = lv.style()

waterfall_bandinfo_style.set_x(0)
waterfall_bandinfo_style.set_y(2)
waterfall_bandinfo_style.set_width(800)
waterfall_bandinfo_style.set_height(24)

# # #

msg_style.set_x(101 - 15)
msg_style.set_y(300)
msg_style.set_width(616)
msg_style.set_height(89)

msg_label_normal_style.set_x(0)
msg_label_normal_style.set_y(20)
msg_label_normal_style.set_width(586)
msg_label_normal_style.set_height(48)

# # #

msg_tiny_style.set_x(int(800/2 - (324/2)))
msg_tiny_style.set_y(int(160 - 66/2 + 36/2))
msg_tiny_style.set_width(324)
msg_tiny_style.set_height(76)

msg_tiny_label_style.set_x(0)
msg_tiny_label_style.set_y(0)
msg_tiny_label_style.set_width(324)
msg_tiny_label_style.set_height(76)

# # #

top_style.set_x(0)
top_style.set_y(0)
top_style.set_width(800)
top_style.set_height(79)
top_style.set_pad_hor(0)
top_style.set_pad_ver(0)

# # #

buttons_style.set_x(0)
buttons_style.set_y(480 - 79)
buttons_style.set_width(800)
buttons_style.set_height(79)
buttons_style.set_pad_hor(0)
buttons_style.set_pad_ver(0)

button_style.set_width(133)
button_style.set_height(59)

# # #

info_style.set_x(20)
info_style.set_y(7)
info_style.set_width(194)
info_style.set_height(45)
info_style.set_pad_hor(0)
info_style.set_pad_ver(0)

info_split_style = lv.style()

info_split_style.set_x(0)
info_split_style.set_y(0)
info_split_style.set_width(59)
info_split_style.set_height(22)

info_mode_style = lv.style()

info_mode_style.set_x(67)
info_mode_style.set_y(0)
info_mode_style.set_width(59)
info_mode_style.set_height(22)

info_agc_style = lv.style()

info_agc_style.set_x(135)
info_agc_style.set_y(0)
info_agc_style.set_width(59)
info_agc_style.set_height(22)

info_pre_style = lv.style()

info_pre_style.set_x(0)
info_pre_style.set_y(23)
info_pre_style.set_width(59)
info_pre_style.set_height(22)

info_att_style = lv.style()

info_att_style.set_x(67)
info_att_style.set_y(23)
info_att_style.set_width(59)
info_att_style.set_height(22)

info_atu_style = lv.style()

info_atu_style.set_x(135)
info_atu_style.set_y(23)
info_atu_style.set_width(59)
info_atu_style.set_height(22)

# # #

smeter_style.set_x(250)
smeter_style.set_y(10)
smeter_style.set_width(340)
smeter_style.set_height(40)

# # #

clock_style.set_x(629)
clock_style.set_y(17)
clock_style.set_width(153)
clock_style.set_height(26)
clock_style.set_pad_hor(0)
clock_style.set_pad_ver(0)

clock_label_style = lv.style()

clock_label_style.set_x(0)
clock_label_style.set_y(0)
clock_label_style.set_width(96)
clock_label_style.set_height(26)

bat_style.set_x(116)
bat_style.set_y(4)
bat_style.set_width(37)
bat_style.set_height(18)

# # # # #

pannel_style.set_x(0)
pannel_style.set_y(480 - 59 - 210 + 8)
pannel_style.set_width(800)
pannel_style.set_height(210)
pannel_style.set_pad_ver(20)
pannel_style.set_pad_hor(16)

# # # # #

dialog_style.set_width(800)
dialog_style.set_height(384)
dialog_style.set_x(0)
dialog_style.set_y(48)
dialog_style.set_pad_ver(0)
dialog_style.set_pad_hor(0)

dialog_no_buttons_style.set_height(432)
