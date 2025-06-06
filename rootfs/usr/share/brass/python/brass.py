import trx
import lv

from lv_const import *
from main_spectrum import *
from main_freqs import *
from main_waterfall import *
from msg import *
from msg_tiny import *

class MainScreen(lv.obj):
	def __init__(self, parent = None):
		lv.obj.__init__(self, parent)

		style = lv.style()
		style.set_bg_color(0x002550)

		self.add_style(style, LV_PART_MAIN)
		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		self.spectrum = MainSpectrum(False, self)
		trx.connect_spectrum(self.spectrum)

		self.freqs = MainFreqs(self)

#		self.spectrum3d = MainSpectrum3D(self)
#		self.spectrum3d.makePalette()
#		trx.connect_spectrum3d(self.spectrum3d)

		self.waterfall = MainWaterfall(True, self)
		self.waterfall.makePalette()
		trx.connect_waterfall(self.waterfall)

		self.msg = Msg(self)
		self.msg_tiny = MsgTiny(self)

def main():
	return MainScreen()
