import trx
import lv
from lv_const import *

from info import *
from smeter import *
from clock import *

class Top(lv.obj):
	def __init__(self, parent = None):
		lv.obj.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)
		self.add_style(top_style, LV_PART_MAIN)

		info = Info(self)
		self.info = info

		smeter = SMeter(self)
		self.smeter = smeter

		clock = Clock(self)
		self.clock = clock
