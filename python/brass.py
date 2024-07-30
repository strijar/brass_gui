import lv
from lv_const import *

class MainScreen(lv.obj):
	def __init__(self):
		lv.obj.__init__(self)

		style = lv.style()
		style.set_bg_color(0x0040A0)

		self.add_style(style, LV_PART_MAIN)
		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

def main():
	return MainScreen()
