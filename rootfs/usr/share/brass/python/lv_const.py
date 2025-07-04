LV_PART_MAIN                    = 0x000000
LV_PART_SCROLLBAR               = 0x010000
LV_PART_INDICATOR               = 0x020000
LV_PART_KNOB                    = 0x030000
LV_PART_SELECTED                = 0x040000
LV_PART_ITEMS                   = 0x050000
LV_PART_TICKS                   = 0x060000
LV_PART_CURSOR                  = 0x070000
LV_PART_CUSTOM_FIRST            = 0x080000
LV_PART_ANY                     = 0x0F0000

LV_OBJ_FLAG_HIDDEN              = (1 << 0)
LV_OBJ_FLAG_CLICKABLE           = (1 << 1)
LV_OBJ_FLAG_CLICK_FOCUSABLE     = (1 << 2)
LV_OBJ_FLAG_CHECKABLE           = (1 << 3)
LV_OBJ_FLAG_SCROLLABLE          = (1 << 4)
LV_OBJ_FLAG_SCROLL_ELASTIC      = (1 << 5)
LV_OBJ_FLAG_SCROLL_MOMENTUM     = (1 << 6)
LV_OBJ_FLAG_SCROLL_ONE          = (1 << 7)
LV_OBJ_FLAG_SCROLL_CHAIN_HOR    = (1 << 8)
LV_OBJ_FLAG_SCROLL_CHAIN_VER    = (1 << 9)
LV_OBJ_FLAG_SCROLL_CHAIN        = (LV_OBJ_FLAG_SCROLL_CHAIN_HOR | LV_OBJ_FLAG_SCROLL_CHAIN_VER)
LV_OBJ_FLAG_SCROLL_ON_FOCUS     = (1 << 10)
LV_OBJ_FLAG_SCROLL_WITH_ARROW   = (1 << 11)
LV_OBJ_FLAG_SNAPPABLE           = (1 << 12)
LV_OBJ_FLAG_PRESS_LOCK          = (1 << 13)
LV_OBJ_FLAG_EVENT_BUBBLE        = (1 << 14)
LV_OBJ_FLAG_GESTURE_BUBBLE      = (1 << 15)
LV_OBJ_FLAG_ADV_HITTEST         = (1 << 16)
LV_OBJ_FLAG_IGNORE_LAYOUT       = (1 << 17)
LV_OBJ_FLAG_FLOATING            = (1 << 18)
LV_OBJ_FLAG_OVERFLOW_VISIBLE    = (1 << 19)
LV_OBJ_FLAG_LAYOUT_1            = (1 << 23)
LV_OBJ_FLAG_LAYOUT_2            = (1 << 24)
LV_OBJ_FLAG_WIDGET_1            = (1 << 25)
LV_OBJ_FLAG_WIDGET_2            = (1 << 26)
LV_OBJ_FLAG_USER_1              = (1 << 27)
LV_OBJ_FLAG_USER_2              = (1 << 28)
LV_OBJ_FLAG_USER_3              = (1 << 29)
LV_OBJ_FLAG_USER_4              = (1 << 30)

LV_OPA_TRANSP                   = 0
LV_OPA_0                        = 0
LV_OPA_10                       = 25
LV_OPA_20                       = 51
LV_OPA_30                       = 76
LV_OPA_40                       = 102
LV_OPA_50                       = 127
LV_OPA_60                       = 153
LV_OPA_70                       = 178
LV_OPA_80                       = 204
LV_OPA_90                       = 229
LV_OPA_100                      = 255
LV_OPA_COVER                    = 255

LV_TEXT_ALIGN_AUTO              = 0
LV_TEXT_ALIGN_LEFT              = 1
LV_TEXT_ALIGN_CENTER            = 2
LV_TEXT_ALIGN_RIGHT             = 3

LV_GRAD_DIR_NONE                = 0
LV_GRAD_DIR_VERT                = 1
LV_GRAD_DIR_HOR                 = 2
