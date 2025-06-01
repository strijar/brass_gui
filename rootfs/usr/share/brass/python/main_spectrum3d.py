import trx
import lv

from lv_const import *
from gui_const import *

class MainSpectrum3D(lv.spectrum3d):
	def __init__(self, parent = None):
		lv.spectrum3d.__init__(self, parent)

		self.y = SPECTRUM_HEIGHT + FREQ_HEIGHT
		self.h = 480 - self.y

		self.makeMainStyle()

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.set_data_size(2048, 100)
		self.clear_data()

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

	def makePalette(self):
		self.set_palette(5)
		self.set_palette_color(0, 0.00, 0x000000)
		self.set_palette_color(1, 0.25, 0x0000FF)
		self.set_palette_color(2, 0.50, 0xFF0000)
		self.set_palette_color(3, 0.75, 0xFFFF00)
		self.set_palette_color(4, 1.00, 0xFFFFFF)

	def makePaletteMatrix(self):
		self.set_palette(3)
		self.set_palette_color(0, 0.00, 0x000000)
		self.set_palette_color(1, 0.50, 0x00FF00)
		self.set_palette_color(2, 1.00, 0xFFFFFF)
