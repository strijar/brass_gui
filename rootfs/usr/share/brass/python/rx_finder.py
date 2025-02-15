import lv
from lv_const import *

class RXFinder(lv.finder):
	def __init__(self, y, height, parent = None):
		lv.finder.__init__(self, parent)

		self.makeMainStyle(y, height)
		self.makeIndicatorStyle()

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

		style.set_bg_color(0x0040A0)
		style.set_bg_opa(LV_OPA_50)

		style.set_line_width(1)
		style.set_line_color(0xFFFFFF)
		style.set_line_opa(LV_OPA_50)

		self.add_style(style, LV_PART_INDICATOR)
