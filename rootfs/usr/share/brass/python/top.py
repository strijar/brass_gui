import trx
import lv
from lv_const import *

from info import *
from smeter import *
from mic_meter import *
from clock import *
from tx_reflex import *

class Top(lv.obj):
	def __init__(self, parent = None):
		lv.obj.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)
		self.add_style(top_style, LV_PART_MAIN)

		info = Info(self)
		self.info = info

		smeter = SMeter(self)
		self.smeter = smeter

		mic_meter = MicMeter(self)
		mic_meter.add_flag(LV_OBJ_FLAG_HIDDEN)
		self.mic_meter = mic_meter

		clock = Clock(self)
		self.clock = clock

		self.reflex = TXReflex(self)
		trx.connect_tx_finder(self.reflex)

		self.msg_subscribe(trx.MSG_TX, self.msg_tx)
		self.msg_subscribe(trx.MSG_RX, self.msg_rx)
		self.msg_subscribe(trx.MSG_MIC, self.msg_mic)

	def msg_tx(self, msg, payload = None):
		self.smeter.add_flag(LV_OBJ_FLAG_HIDDEN)
		self.mic_meter.clear_flag(LV_OBJ_FLAG_HIDDEN)

	def msg_rx(self, msg, payload = None):
		self.mic_meter.add_flag(LV_OBJ_FLAG_HIDDEN)
		self.smeter.clear_flag(LV_OBJ_FLAG_HIDDEN)

	def msg_mic(self, msg, enabled = None):
		if enabled:
			self.smeter.add_flag(LV_OBJ_FLAG_HIDDEN)
			self.mic_meter.clear_flag(LV_OBJ_FLAG_HIDDEN)
		else:
			self.mic_meter.add_flag(LV_OBJ_FLAG_HIDDEN)
			self.smeter.clear_flag(LV_OBJ_FLAG_HIDDEN)
