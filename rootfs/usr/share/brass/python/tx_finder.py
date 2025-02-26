import trx
import lv

from lv_const import *

class TXFinder(lv.finder):
	def __init__(self, y, height, parent = None):
		lv.finder.__init__(self, parent)

		self.makeMainStyle(y, height)
		self.makeIndicatorStyle()

		self.msg_subscribe(trx.MSG_RECORDER, self.msg_recorder)

	def makeMainStyle(self, y, height):
		style = lv.style()

		style.set_bg_opa(LV_OPA_0)
		style.set_radius(0)
		style.set_x(0)
		style.set_y(y)
		style.set_width(800)
		style.set_height(height)

		self.add_style(style, LV_PART_MAIN)

	def makeIndicatorStyle(self):
		style = lv.style()

		style.set_bg_color(0xFF40A0)
		style.set_bg_opa(LV_OPA_50)
		style.set_line_width(1)

		self.add_style(style, LV_PART_INDICATOR)

		style_rec_off = lv.style()

		style_rec_off.set_line_color(0xFFFFFF)
		style_rec_off.set_line_opa(LV_OPA_50)
		self.style_rec_off = style_rec_off

		style_rec_on = lv.style()

		style_rec_on.set_line_color(0xFF0000)
		style_rec_on.set_line_opa(LV_OPA_COVER)
		self.style_rec_on = style_rec_on

		self.add_style(style_rec_off, LV_PART_INDICATOR)

	def msg_recorder(self, msg, on = None):
		if on:
			self.add_style(self.style_rec_on, LV_PART_INDICATOR)
		else:
			self.add_style(self.style_rec_off, LV_PART_INDICATOR)
