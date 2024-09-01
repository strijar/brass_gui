import trx
import lv
from lv_const import *

class MainSpectrum(lv.spectrum):
	def __init__(self, parent = None):
		lv.spectrum.__init__(self, parent)

		self.makeMainStyle()
		self.makeLinesStyle()
		self.makePeakStyle()

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.set_data_size(800)
		self.clear_data()

#		self.set_peak(True)
#		self.set_peak_hold(2000)
#		self.set_peak_speed(0.5)

	def makeMainStyle(self):
		style = lv.style()

		style.set_bg_color(0x000000)
		style.set_bg_opa(LV_OPA_COVER)
		style.set_radius(0)
		style.set_x(0)
		style.set_y(0)
		style.set_width(800)
		style.set_height(160)
		style.set_pad_hor(0)

		self.add_style(style, LV_PART_MAIN)

	def makeLinesStyle(self):
		style = lv.style()

		style.set_line_width(2)
		style.set_line_color(0xAAAAAA)

		self.add_style(style, LV_PART_INDICATOR)

	def makePeakStyle(self):
		style = lv.style()

		style.set_line_width(1)
		style.set_line_color(0x555555)

		self.add_style(style, LV_PART_TICKS)

class MainScreen(lv.obj):
	def __init__(self, parent = None):
		lv.obj.__init__(self, parent)

		style = lv.style()
		style.set_bg_color(0x0040A0)

		self.add_style(style, LV_PART_MAIN)
		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.spectrum = MainSpectrum(self)
		trx.connect_spectrum(self.spectrum)

def main():
	return MainScreen()
