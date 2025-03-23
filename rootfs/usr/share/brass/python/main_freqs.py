import trx
import lv

from lv_const import *
from gui_const import *

class MainFreqs():
	def __init__(self, parent = None):
		self.rx = None
		self.tx = None
		self.fft = None
		self.zoom = None

		self.makeFreq(parent)
		self.makeRange(parent)

	def makeFreq(self, parent):
		font = lv.load_font("/usr/share/brass/font/Jura-Bold.ttf", 32)
		style = lv.style()

		style.set_text_color(0xffffff)
		style.set_text_font(font)
		style.set_pad_ver(0)
		style.set_width(500)
		style.set_height(FREQ_HEIGHT)
		style.set_text_align(LV_TEXT_ALIGN_CENTER)
		style.set_x(150)
		style.set_y(SPECTRUM_HEIGHT)

		freq = lv.label(parent)
		freq.add_style(style, LV_PART_MAIN)

		freq.msg_subscribe(trx.MSG_FREQ_RX_CHANGED, self.msg_freq_rx)
		freq.msg_subscribe(trx.MSG_FREQ_TX_CHANGED, self.msg_freq_tx)
		self.freq = freq

	def makeRange(self, parent):
		font = lv.load_font("/usr/share/brass/font/Jura.ttf", 28)
		style = lv.style()

		style.set_text_color(0xffffff)
		style.set_text_font(font)
		style.set_pad_ver(2)
		style.set_width(150)
		style.set_height(FREQ_HEIGHT)

		style_left = lv.style()
		style_left.set_text_align(LV_TEXT_ALIGN_LEFT)

		left = lv.label(parent)
		left.set_pos(0, SPECTRUM_HEIGHT)
		left.add_style(style, LV_PART_MAIN)
		left.add_style(style_left, LV_PART_MAIN)
		self.left = left

		style_right = lv.style()
		style_right.set_text_align(LV_TEXT_ALIGN_RIGHT)

		right = lv.label(parent)
		right.set_pos(500 + 150, SPECTRUM_HEIGHT)
		right.add_style(style, LV_PART_MAIN)
		right.add_style(style_right, LV_PART_MAIN)
		self.right = right

		left.msg_subscribe(trx.MSG_FREQ_FFT_CHANGED, self.msg_fft_changed)
		left.msg_subscribe(trx.MSG_RATE_FFT_CHANGED, self.msg_rate_fft)

	def view_freq(self):
		if self.rx == self.tx:
			self.freq.set_text(f"{self.rx:,}")
		else:
			self.freq.set_text(f"{self.rx:,}" + "/" + f"{self.tx:,}")

	def view_range(self):
		left = int((self.fft - int(50000 / self.zoom)) / 1000)
		right = int((self.fft + int(50000 / self.zoom)) / 1000)

		self.left.set_text(f"{left:,}")
		self.right.set_text(f"{right:,}")

	def msg_freq_rx(self, msg, payload = None):
		self.rx = payload

		if self.tx:
			self.view_freq()

	def msg_freq_tx(self, msg, payload = None):
		self.tx = payload

		if self.rx:
			self.view_freq()

	def msg_fft_changed(self, msg, payload = None):
		self.fft = payload

		if self.zoom:
			self.view_range()

	def msg_rate_fft(self, msg, payload = None):
		self.zoom = payload

		if self.fft:
			self.view_range()
