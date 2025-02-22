import trx
import lv

from lv_const import *
from gui_const import *
from rx_finder import *
from tx_finder import *
from bandinfo import *

class MainSpectrum(lv.spectrum):
	def __init__(self, bandinfo = True, parent = None):
		lv.spectrum.__init__(self, parent)

		self.makeMainStyle()
		self.makeLinesStyle()
		self.makePeakStyle()

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.set_data_size(400)
		self.clear_data()

		height = SPECTRUM_HEIGHT - TOP_HEIGHT
		half_height = int(height / 2)

		self.tx_finder = TXFinder(TOP_HEIGHT, half_height, self)
		trx.connect_tx_finder(self.tx_finder)

		self.rx_finder = RXFinder(TOP_HEIGHT + half_height, half_height, self)
		trx.connect_rx_finder(self.rx_finder)

		if bandinfo:
			self.bandinfo = BandInfo(self)
			self.bandinfo.set_size(800, height)
			self.bandinfo.set_pos(0, SPECTRUM_HEIGHT - height)
			self.bandinfo.makeMarkerStyle(0xAAAAAA, LV_OPA_50)

	def makeMainStyle(self):
		style = lv.style()

		style.set_bg_color(0x000000)
		style.set_bg_opa(LV_OPA_COVER)
		style.set_radius(0)
		style.set_x(0)
		style.set_y(0)
		style.set_width(800)
		style.set_height(SPECTRUM_HEIGHT)
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
