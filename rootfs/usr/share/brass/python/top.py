import trx
import lv
from lv_const import *

from style import *

class Top(lv.obj):
	def __init__(self, parent = None):
		lv.obj.__init__(self, parent)

		self.clear_flag(LV_OBJ_FLAG_SCROLLABLE)
		self.add_style(top_style, LV_PART_MAIN)

		smeter = lv.smeter(self)
		smeter.add_style(smeter_style, LV_PART_MAIN)
		smeter.add_style(smeter_slice_style, LV_PART_INDICATOR)
		smeter.add_style(smeter_part1_style, LV_PART_CUSTOM_FIRST)
		smeter.add_style(smeter_part2_style, LV_PART_CUSTOM_FIRST + 0x10000)
		smeter.add_style(smeter_part3_style, LV_PART_CUSTOM_FIRST + 0x20000)
		smeter.add_style(smeter_part4_style, LV_PART_CUSTOM_FIRST + 0x30000)
		smeter.set_value(-73+40)
		trx.connect_smeter(smeter)

		self.smeter = smeter
