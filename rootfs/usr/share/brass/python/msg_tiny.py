import trx
import lv

from lv_const import *

class MsgTiny(lv.hiding):
	def __init__(self, parent = None):
		lv.hiding.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)
		self.set_timeout(1000)

		main_style = lv.style()

		main_style.set_width(324)
		main_style.set_height(76)
		main_style.set_x(int(800/2 - (324/2)))
		main_style.set_y(int(160 - 66/2 + 36/2))
		main_style.set_radius(0)
		main_style.set_bg_img_src("A:/usr/share/brass/images/msg_tiny.bin")
		main_style.set_bg_img_opa(LV_OPA_COVER)

		self.add_style(main_style, LV_PART_MAIN)
		self.set_style_opa(0, LV_PART_MAIN)

		label = lv.label(self)
		font = lv.load_font("/usr/share/brass/font/Jura.ttf", 52)
		label_style = lv.style()

		label_style.set_text_color(0xFFFFFF)
		label_style.set_text_font(font)
		label_style.set_text_align(LV_TEXT_ALIGN_CENTER)
		label_style.set_width(324)
		label_style.set_height(76)
		label_style.set_x(0)
		label_style.set_y(0)

		label.add_style(label_style, LV_PART_MAIN)
		label.set_text("")

		self.label = label
		self.msg_subscribe(trx.MSG_MSG_TINY, self.msg_msg_tiny)

	def msg_msg_tiny(self, msg, payload = None):
		self.move_foreground()
		self.label.set_text(payload)
		self.touch()
