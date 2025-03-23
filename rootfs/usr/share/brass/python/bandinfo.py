import trx
import lv

from lv_const import *

class BandInfo(lv.bandinfo):
	def __init__(self, parent = None):
		lv.bandinfo.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)

		style = lv.style()

		style.set_radius(0)
		style.set_border_width(0)
		style.set_bg_opa(LV_OPA_0)

		self.add_style(style, LV_PART_MAIN)

		self.msg_subscribe(trx.MSG_FREQ_FFT_CHANGED, self.msg_fft_changed)
		self.msg_subscribe(trx.MSG_RATE_FFT_CHANGED, self.msg_rate_fft)

	def msg_fft_changed(self, msg, payload = None):
		self.set_center(payload)

	def msg_rate_fft(self, msg, payload = None):
		self.set_span(int(100000 / payload))
		pass

	def makeBandStyle(self):
		font = lv.load_font("/usr/share/brass/font/Jura.ttf", 22)
		style = lv.style()

		style.set_bg_color(0x002550)
		style.set_bg_opa(LV_OPA_50)
		style.set_border_width(2)
		style.set_border_color(0xFFFFFF)
		style.set_border_opa(LV_OPA_50)
		style.set_text_color(0xFFFFFF)
		style.set_text_font(font)

		self.add_style(style, LV_PART_INDICATOR)

	def makeMarkerStyle(self, color, opa):
		font = lv.load_font("/usr/share/brass/font/Jura-Bold.ttf", 22)
		style = lv.style()

		style.set_bg_color(color)
		style.set_bg_opa(opa)
		style.set_text_color(0x000000)
		style.set_text_font(font)

		self.add_style(style, LV_PART_TICKS)
