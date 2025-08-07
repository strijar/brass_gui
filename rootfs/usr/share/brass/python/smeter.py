import trx
import lv
from lv_const import *

from style import *

class SMeter(lv.smeter):
	def __init__(self, parent = None):
		lv.smeter.__init__(self, parent)

		self.add_style(smeter_style, LV_PART_MAIN)
		self.add_style(smeter_slice_style, LV_PART_INDICATOR)
		self.add_style(smeter_part1_style, LV_PART_CUSTOM_FIRST)
		self.add_style(smeter_part2_style, LV_PART_CUSTOM_FIRST + 0x10000)
		self.add_style(smeter_part3_style, LV_PART_CUSTOM_FIRST + 0x20000)
		self.add_style(smeter_part4_style, LV_PART_CUSTOM_FIRST + 0x30000)

		trx.connect_smeter(self)
