import trx
import lv
from lv_const import *

from rx_finder import *
from bandinfo import *

class MainWaterfall(lv.waterfall):
	def __init__(self, parent = None):
		lv.waterfall.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.add_style(waterfall_style, LV_PART_MAIN)

		self.set_data_size(2047)
		self.clear_data()

		self.rx_finder = RXFinder(self)
		self.rx_finder.add_style(waterfall_rx_finder_style, LV_PART_MAIN)
		trx.connect_rx_finder(self.rx_finder)

		self.bandinfo = BandInfo(self)
		self.bandinfo.add_style(waterfall_bandinfo_style, LV_PART_MAIN)

	def makePalette(self):
		self.set_palette(5)
		self.set_palette_color(0, 0.00, 0x040A1B)
		self.set_palette_color(1, 0.25, 0x040AFF)
		self.set_palette_color(2, 0.50, 0xFF0A1B)
		self.set_palette_color(3, 0.75, 0xFFFF1B)
		self.set_palette_color(4, 1.00, 0xFFFFFF)
