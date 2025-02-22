import trx
import lv

from lv_const import *
from gui_const import *
from rx_finder import *
from bandinfo import *

class MainWaterfall(lv.waterfall):
	def __init__(self, bandinfo = False, parent = None):
		lv.waterfall.__init__(self, parent)

		self.y = SPECTRUM_HEIGHT + FREQ_HEIGHT
		self.h = 480 - self.y

		self.makeMainStyle()

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.set_data_size(2047)
		self.clear_data()

		self.rx_finder = RXFinder(0, self.h - BUTTONS_HEIGHT, self)
		trx.connect_rx_finder(self.rx_finder)

		if bandinfo:
			self.bandinfo = BandInfo(self)
			self.bandinfo.set_size(800, 24)
			self.bandinfo.set_pos(0, 2)
			self.bandinfo.makeBandStyle()
			self.bandinfo.makeMarkerStyle(0xAAAAAA, LV_OPA_COVER)

	def makeMainStyle(self):
		style = lv.style()

		style.set_bg_color(0x000000)
		style.set_bg_opa(LV_OPA_COVER)
		style.set_radius(0)
		style.set_x(0)
		style.set_y(self.y)
		style.set_width(800)
		style.set_height(self.h)
		style.set_pad_hor(0)
		style.set_pad_ver(0)

		self.add_style(style, LV_PART_MAIN)
