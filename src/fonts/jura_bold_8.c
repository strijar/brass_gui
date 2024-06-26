/*******************************************************************************
 * Size: 8 px
 * Bpp: 4
 * Opts: --font jura_bold.ttf -r 0x20-0x7F --format lvgl --no-compress --bpp 4 --size 8 -o jura_bold_8.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef JURA_BOLD_8
#define JURA_BOLD_8 1
#endif

#if JURA_BOLD_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x36, 0x46, 0x46, 0x46, 0x13, 0x35,

    /* U+0022 "\"" */
    0x43, 0x75, 0x48, 0x0, 0x0,

    /* U+0023 "#" */
    0x0, 0x88, 0x1, 0xaa, 0xc5, 0x8, 0x27, 0x4,
    0xcb, 0xa2, 0x16, 0x80, 0x0,

    /* U+0024 "$" */
    0x0, 0x70, 0x0, 0x9d, 0xa3, 0x28, 0x80, 0x70,
    0x9d, 0xa4, 0x33, 0x90, 0xa1, 0xbd, 0xa6, 0x0,
    0x40, 0x0,

    /* U+0025 "%" */
    0x4b, 0xa0, 0x47, 0x7, 0x2a, 0x2a, 0x0, 0x3a,
    0x8b, 0x8a, 0x30, 0xa, 0x2a, 0x18, 0x7, 0x40,
    0x9a, 0x40,

    /* U+0026 "&" */
    0x9, 0xa8, 0x0, 0xb, 0x1, 0x0, 0x49, 0xa2,
    0x0, 0x73, 0x2d, 0x50, 0x2b, 0xaa, 0xa0,

    /* U+0027 "'" */
    0x43, 0x53, 0x0,

    /* U+0028 "(" */
    0x29, 0x17, 0x10, 0x71, 0x7, 0x10, 0x71, 0x6,
    0x20, 0x18, 0x10,

    /* U+0029 ")" */
    0x76, 0x9, 0x9, 0x9, 0x8, 0x9, 0x74,

    /* U+002A "*" */
    0x1, 0x4, 0xf7, 0x19, 0x20,

    /* U+002B "+" */
    0x0, 0x30, 0x0, 0x9, 0x0, 0x28, 0xc8, 0x10,
    0x8, 0x0,

    /* U+002C "," */
    0x54, 0x81,

    /* U+002D "-" */
    0x29, 0x93,

    /* U+002E "." */
    0x35,

    /* U+002F "/" */
    0x1, 0x80, 0x65, 0xa, 0x10, 0xb0, 0x28, 0x6,
    0x40, 0x90, 0x0,

    /* U+0030 "0" */
    0x3b, 0xab, 0x28, 0x20, 0x37, 0x91, 0x93, 0x78,
    0x20, 0x37, 0x3b, 0xab, 0x20,

    /* U+0031 "1" */
    0xa, 0x63, 0x76, 0x4, 0x60, 0x46, 0x3, 0x60,

    /* U+0032 "2" */
    0x3b, 0xab, 0x12, 0x10, 0x64, 0x0, 0x78, 0x0,
    0xa2, 0x0, 0x5c, 0xaa, 0x20,

    /* U+0033 "3" */
    0x2b, 0xab, 0x12, 0x10, 0x64, 0x0, 0xad, 0x23,
    0x0, 0x46, 0x4b, 0xab, 0x20,

    /* U+0034 "4" */
    0x0, 0x4b, 0x0, 0x28, 0xa0, 0x19, 0xa, 0x7,
    0xba, 0xe5, 0x0, 0x9, 0x0,

    /* U+0035 "5" */
    0x5c, 0xaa, 0x36, 0xca, 0xa1, 0x0, 0x4, 0x64,
    0x10, 0x46, 0x3b, 0xab, 0x10,

    /* U+0036 "6" */
    0x3b, 0xab, 0x28, 0xaa, 0xb3, 0x83, 0x4, 0x68,
    0x20, 0x46, 0x3b, 0xab, 0x20,

    /* U+0037 "7" */
    0x2a, 0xad, 0x20, 0x0, 0xb0, 0x0, 0x94, 0x0,
    0x46, 0x0, 0x6, 0x30, 0x0,

    /* U+0038 "8" */
    0x2b, 0xab, 0x15, 0x50, 0x64, 0x2d, 0xad, 0x18,
    0x20, 0x46, 0x4b, 0xab, 0x30,

    /* U+0039 "9" */
    0x4b, 0xab, 0x27, 0x20, 0x46, 0x2a, 0xab, 0x73,
    0x0, 0x46, 0x3b, 0xab, 0x20,

    /* U+003A ":" */
    0x35, 0x0, 0x0, 0x35,

    /* U+003B ";" */
    0x44, 0x0, 0x0, 0x54, 0x81,

    /* U+003C "<" */
    0x0, 0x68, 0xc, 0x40, 0x1, 0x96, 0x0, 0x1,

    /* U+003D "=" */
    0x29, 0x98, 0x12, 0x88, 0x81,

    /* U+003E ">" */
    0x9, 0x50, 0x0, 0x6a, 0x8, 0x81, 0x1, 0x0,

    /* U+003F "?" */
    0x7a, 0xb5, 0x70, 0x19, 0x1, 0xb2, 0x4, 0x20,
    0x5, 0x30,

    /* U+0040 "@" */
    0x18, 0x88, 0x80, 0x55, 0x99, 0x64, 0x58, 0x37,
    0x64, 0x55, 0x98, 0x91, 0x2a, 0x99, 0x91,

    /* U+0041 "A" */
    0x0, 0xc2, 0x0, 0x48, 0x90, 0xa, 0xa, 0x12,
    0xda, 0xb7, 0x72, 0x0, 0xa0,

    /* U+0042 "B" */
    0x2d, 0xab, 0x42, 0x80, 0x28, 0x2d, 0xac, 0x72,
    0x80, 0xb, 0x2d, 0xaa, 0x80,

    /* U+0043 "C" */
    0x1b, 0xaa, 0x90, 0x55, 0x0, 0x50, 0x55, 0x0,
    0x0, 0x55, 0x0, 0x50, 0x1b, 0xaa, 0x90,

    /* U+0044 "D" */
    0x2d, 0xaa, 0x80, 0x28, 0x0, 0xa1, 0x28, 0x0,
    0x82, 0x28, 0x0, 0x91, 0x2d, 0xaa, 0x80,

    /* U+0045 "E" */
    0x2d, 0xaa, 0x32, 0x80, 0x0, 0x2d, 0xa3, 0x2,
    0x80, 0x0, 0x2d, 0xaa, 0x20,

    /* U+0046 "F" */
    0x2d, 0xaa, 0x32, 0x80, 0x0, 0x2d, 0xa3, 0x2,
    0x80, 0x0, 0x27, 0x0, 0x0,

    /* U+0047 "G" */
    0x1b, 0xaa, 0x90, 0x55, 0x0, 0x30, 0x55, 0x5,
    0xb0, 0x55, 0x0, 0xa0, 0x1b, 0xaa, 0x90,

    /* U+0048 "H" */
    0x27, 0x0, 0x36, 0x28, 0x0, 0x37, 0x2d, 0xaa,
    0xb7, 0x28, 0x0, 0x37, 0x27, 0x0, 0x36,

    /* U+0049 "I" */
    0x27, 0x28, 0x28, 0x28, 0x27,

    /* U+004A "J" */
    0x0, 0x7, 0x20, 0x0, 0x73, 0x0, 0x7, 0x35,
    0x0, 0x82, 0x6a, 0xaa, 0x0,

    /* U+004B "K" */
    0x27, 0x1a, 0x2, 0x9b, 0x20, 0x2e, 0x90, 0x2,
    0x86, 0x70, 0x27, 0x8, 0x30,

    /* U+004C "L" */
    0x27, 0x0, 0x2, 0x80, 0x0, 0x28, 0x0, 0x2,
    0x80, 0x0, 0x2d, 0xaa, 0x0,

    /* U+004D "M" */
    0x2b, 0x0, 0x1b, 0x2c, 0x70, 0xab, 0x28, 0x9a,
    0x4a, 0x28, 0x5, 0xa, 0x27, 0x0, 0x9,

    /* U+004E "N" */
    0x2b, 0x0, 0x63, 0x2b, 0x90, 0x73, 0x28, 0x67,
    0x73, 0x28, 0x8, 0xb3, 0x27, 0x0, 0xb3,

    /* U+004F "O" */
    0x1b, 0xaa, 0xa0, 0x55, 0x0, 0x82, 0x55, 0x0,
    0x73, 0x55, 0x0, 0x82, 0x1b, 0xaa, 0xa0,

    /* U+0050 "P" */
    0x2d, 0xab, 0x32, 0x80, 0x38, 0x2d, 0xaa, 0x22,
    0x80, 0x0, 0x27, 0x0, 0x0,

    /* U+0051 "Q" */
    0x1b, 0xaa, 0xa0, 0x55, 0x0, 0x82, 0x55, 0x0,
    0x73, 0x55, 0x2, 0x82, 0x1b, 0xad, 0xd0, 0x0,
    0x0, 0x31,

    /* U+0052 "R" */
    0x2d, 0xab, 0x32, 0x80, 0x38, 0x2d, 0xbb, 0x22,
    0x80, 0xb0, 0x27, 0x5, 0x50,

    /* U+0053 "S" */
    0xa, 0xab, 0x61, 0x90, 0x3, 0x9, 0xaa, 0x61,
    0x10, 0xa, 0x2b, 0xaa, 0x80,

    /* U+0054 "T" */
    0x7a, 0xea, 0x60, 0xa, 0x0, 0x0, 0xa0, 0x0,
    0xa, 0x0, 0x0, 0x90, 0x0,

    /* U+0055 "U" */
    0x36, 0x0, 0x54, 0x46, 0x0, 0x64, 0x46, 0x0,
    0x64, 0x37, 0x0, 0x64, 0xa, 0xaa, 0xb0,

    /* U+0056 "V" */
    0x90, 0x0, 0xa4, 0x70, 0x46, 0xb, 0xa, 0x0,
    0x58, 0x70, 0x0, 0xc1, 0x0,

    /* U+0057 "W" */
    0x90, 0xc, 0x10, 0x96, 0x43, 0xc6, 0x19, 0x19,
    0x82, 0xa7, 0x40, 0xaa, 0x9, 0xb0, 0x5, 0x60,
    0x48, 0x0,

    /* U+0058 "X" */
    0x55, 0x5, 0x60, 0xa5, 0xa0, 0x1, 0xf2, 0x0,
    0x96, 0xa0, 0x46, 0x6, 0x50,

    /* U+0059 "Y" */
    0x91, 0x2, 0x81, 0xa0, 0xb0, 0x6, 0xc4, 0x0,
    0xb, 0x0, 0x0, 0x90, 0x0,

    /* U+005A "Z" */
    0x4a, 0xac, 0x80, 0x10, 0x1a, 0x0, 0x0, 0x91,
    0x0, 0x8, 0x30, 0x10, 0x5d, 0xaa, 0xa0,

    /* U+005B "[" */
    0x76, 0x71, 0x71, 0x71, 0x71, 0x71, 0x55,

    /* U+005C "\\" */
    0x9, 0x0, 0xa, 0x0, 0x7, 0x30, 0x3, 0x70,
    0x0, 0xa0, 0x0, 0xa0, 0x0, 0x63,

    /* U+005D "]" */
    0x94, 0x45, 0x45, 0x45, 0x45, 0x45, 0x83,

    /* U+005E "^" */
    0xb, 0x33, 0x68,

    /* U+005F "_" */
    0x5a, 0xa0,

    /* U+0060 "`" */
    0x30, 0x36,

    /* U+0061 "a" */
    0x1b, 0xab, 0x11, 0xaa, 0xc5, 0x45, 0x5, 0x61,
    0xba, 0xb5,

    /* U+0062 "b" */
    0x27, 0x0, 0x2, 0x80, 0x0, 0x2c, 0xab, 0x42,
    0x80, 0x19, 0x28, 0x1, 0x92, 0xca, 0xb4,

    /* U+0063 "c" */
    0x1b, 0xaa, 0x15, 0x50, 0x0, 0x55, 0x0, 0x1,
    0xba, 0xa1,

    /* U+0064 "d" */
    0x0, 0x3, 0x60, 0x0, 0x37, 0x1b, 0xab, 0x75,
    0x50, 0x37, 0x55, 0x3, 0x71, 0xba, 0xb6,

    /* U+0065 "e" */
    0x1b, 0xab, 0x25, 0xcb, 0xb5, 0x55, 0x0, 0x11,
    0xba, 0xb2,

    /* U+0066 "f" */
    0x8, 0x70, 0xa0, 0x6e, 0x70, 0xa0, 0xa, 0x0,
    0x90,

    /* U+0067 "g" */
    0x1b, 0xab, 0x65, 0x50, 0x37, 0x55, 0x3, 0x71,
    0xba, 0xa7, 0x0, 0x3, 0x62, 0xba, 0xb3,

    /* U+0068 "h" */
    0x17, 0x0, 0x2, 0x80, 0x0, 0x2e, 0xbb, 0x32,
    0x90, 0x18, 0x28, 0x1, 0x91, 0x80, 0x18,

    /* U+0069 "i" */
    0x38, 0x0, 0x27, 0x28, 0x28, 0x27,

    /* U+006A "j" */
    0x3, 0x90, 0x0, 0x2, 0x70, 0x28, 0x2, 0x80,
    0x28, 0x2, 0x70, 0xb4,

    /* U+006B "k" */
    0x27, 0x0, 0x28, 0x0, 0x28, 0x2a, 0x2b, 0xb0,
    0x2b, 0xb1, 0x27, 0x29,

    /* U+006C "l" */
    0x27, 0x2, 0x80, 0x28, 0x2, 0x80, 0x28, 0x0,
    0xb3,

    /* U+006D "m" */
    0x2b, 0xab, 0xab, 0x52, 0x80, 0x91, 0xa, 0x28,
    0x9, 0x10, 0xa2, 0x70, 0x81, 0x9,

    /* U+006E "n" */
    0x2b, 0xab, 0x32, 0x80, 0x28, 0x28, 0x2, 0x82,
    0x70, 0x18,

    /* U+006F "o" */
    0x1b, 0xab, 0x25, 0x50, 0x46, 0x55, 0x4, 0x61,
    0xba, 0xb2,

    /* U+0070 "p" */
    0x2c, 0xab, 0x42, 0x80, 0x19, 0x28, 0x1, 0x92,
    0xda, 0xb4, 0x28, 0x0, 0x2, 0x70, 0x0,

    /* U+0071 "q" */
    0x1b, 0xaa, 0x65, 0x50, 0x37, 0x55, 0x3, 0x71,
    0xba, 0xb7, 0x0, 0x3, 0x70, 0x0, 0x36,

    /* U+0072 "r" */
    0x2b, 0xa2, 0x29, 0x0, 0x28, 0x0, 0x27, 0x0,

    /* U+0073 "s" */
    0x3b, 0xab, 0x2, 0xaa, 0xb0, 0x0, 0x6, 0x43,
    0xba, 0xb1,

    /* U+0074 "t" */
    0x9, 0x6, 0xe9, 0xa, 0x0, 0xa0, 0x9, 0x80,

    /* U+0075 "u" */
    0x36, 0x2, 0x64, 0x60, 0x37, 0x37, 0x3, 0x70,
    0xba, 0xa7,

    /* U+0076 "v" */
    0x81, 0xa, 0x47, 0x56, 0xb, 0xb0, 0x6, 0x70,

    /* U+0077 "w" */
    0x80, 0x66, 0x8, 0x55, 0x9a, 0x55, 0xc, 0x89,
    0xb0, 0xa, 0x24, 0x80,

    /* U+0078 "x" */
    0x38, 0x37, 0x8, 0xc0, 0xb, 0xb2, 0x64, 0x19,

    /* U+0079 "y" */
    0x36, 0x0, 0x94, 0x60, 0x19, 0x37, 0x1, 0x90,
    0xba, 0x99, 0x12, 0x1, 0x91, 0xca, 0xb5,

    /* U+007A "z" */
    0x6a, 0xca, 0x0, 0xa, 0x10, 0x9, 0x30, 0x5,
    0xda, 0xa0,

    /* U+007B "{" */
    0x7, 0x50, 0x80, 0x9, 0x5, 0x80, 0x9, 0x0,
    0x80, 0x5, 0x50,

    /* U+007C "|" */
    0x54, 0x55, 0x55, 0x55, 0x55, 0x55, 0x44,

    /* U+007D "}" */
    0x76, 0x0, 0x80, 0x9, 0x0, 0xa3, 0x9, 0x0,
    0x80, 0x74, 0x0,

    /* U+007E "~" */
    0x17, 0x86, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 40, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 35, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 11, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 112, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 83, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 30, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 78, .adv_w = 38, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 89, .adv_w = 38, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 96, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 101, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 111, .adv_w = 33, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 113, .adv_w = 66, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 115, .adv_w = 35, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 41, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 127, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 79, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 35, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 33, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 261, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 78, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 274, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 65, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 95, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 89, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 92, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 77, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 71, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 89, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 100, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 37, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 75, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 69, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 107, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 97, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 93, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 539, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 89, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 97, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 79, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 88, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 29, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 672, .adv_w = 41, .box_w = 4, .box_h = 7, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 686, .adv_w = 29, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 693, .adv_w = 55, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 696, .adv_w = 60, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 698, .adv_w = 32, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 700, .adv_w = 82, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 76, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 81, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 49, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 784, .adv_w = 85, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 799, .adv_w = 37, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 805, .adv_w = 37, .box_w = 3, .box_h = 8, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 817, .adv_w = 65, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 44, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 119, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 852, .adv_w = 85, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 81, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 84, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 887, .adv_w = 83, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 902, .adv_w = 55, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 54, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 85, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 96, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 958, .adv_w = 68, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 966, .adv_w = 87, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 981, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 991, .adv_w = 46, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1002, .adv_w = 31, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1009, .adv_w = 46, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1020, .adv_w = 78, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 2, 0, 0, 0, 0, 3, 0,
    4, 5, 6, 7, 8, 9, 0, 0,
    10, 0, 0, 11, 11, 0, 3, 0,
    0, 0, 12, 13, 14, 15, 16, 17,
    14, 18, 18, 19, 20, 21, 18, 18,
    15, 22, 15, 23, 1, 24, 19, 25,
    25, 26, 27, 28, 2, 29, 0, 0,
    0, 0, 30, 31, 32, 33, 31, 34,
    35, 30, 0, 0, 36, 37, 30, 30,
    31, 31, 0, 38, 39, 40, 35, 41,
    41, 42, 35, 43, 2, 18, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 0, 2, 0, 0,
    1, 0, 0, 3, 0, 4, 5, 4,
    6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 17, 0, 0, 0,
    18, 0, 19, 0, 20, 0, 0, 0,
    20, 0, 0, 21, 0, 0, 0, 0,
    20, 0, 20, 0, 2, 22, 0, 23,
    23, 24, 25, 26, 0, 27, 0, 3,
    0, 0, 28, 29, 30, 30, 30, 0,
    30, 29, 0, 31, 29, 29, 32, 32,
    30, 32, 30, 32, 33, 34, 35, 36,
    36, 37, 35, 38, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, -6, 0, 0, 0, -9,
    -3, 0, 0, 0, 0, -4, 0, 0,
    0, 0, -3, 0, 0, -6, 0, 0,
    -3, -1, 0, 0, 0, 0, 0, 0,
    0, 0, -3, -3, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -3, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -4, -4, 0, -6, 0, 0, 0,
    -1, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, -1,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    -3, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    -4, -1, 0, -4, 0, -3, -9, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, -4, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, -6, -6, 0, -5, 0, -3,
    -10, 0, 0, 0, 0, -1, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, 0, 0, -5, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -13, -4, -13, 0, 0, 0,
    0, -9, 0, -1, 0, 0, 0, -6,
    0, 0, 0, 0, 0, -1, 0, -10,
    -4, 0, -6, 0, 0, 0, -3, -3,
    0, -1, 0, 0, -3, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, -3, 0,
    -4, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -3, 0,
    0, -3, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -4, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, -1, 0,
    -1, -5, -3, -3, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -4,
    0, 0, -4, 0, 0, -5, 0, 0,
    0, -3, 0, -12, 0, 0, 0, -3,
    -1, 0, -6, 0, 0, -4, 0, 0,
    0, 0, -10, -1, -10, 1, 0, 0,
    4, 0, 0, -6, 0, -9, 0, -9,
    -8, 0, -6, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -9, 0,
    0, -5, 0, 0, -1, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -4,
    0, 0, 0, 0, -3, -4, 0, 0,
    -15, 0, -22, 0, -15, 0, 0, -10,
    0, 0, 0, -1, -1, -9, -1, -3,
    0, 0, 0, -3, 0, -12, -9, 0,
    -13, 0, 0, -3, 0, 0, 0, 0,
    0, -5, -3, -10, 0, 0, 0, 0,
    0, -17, 0, 0, 0, -3, -1, -4,
    -10, 0, 0, -3, 0, 0, 0, 0,
    -8, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -3, 0, 0,
    0, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -1, 0, -1, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, -3, -1, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -14, -18, 0,
    0, -3, 0, -3, -14, 0, 0, 0,
    -5, 0, -10, 0, -10, -5, -13, 0,
    3, 0, 3, 0, 0, -14, -3, -14,
    0, -12, -14, 0, -14, -12, -13, -14,
    0, -4, 0, -13, -9, 0, 0, -3,
    0, 0, -5, 0, 0, 0, -1, 0,
    -6, 0, -4, -3, -9, 1, 0, 0,
    3, 0, 0, -8, 0, -9, 0, -3,
    -6, 0, -4, 0, 0, 0, 0, 0,
    0, 0, -12, 0, 0, -4, 0, 0,
    -1, 0, 0, -1, -4, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -5, 0, 0, 0, 0,
    -4, -5, 0, 0, 0, -4, 0, -14,
    -14, 0, 0, -5, -3, -3, -9, 0,
    0, 0, -5, 0, -9, 0, -6, -3,
    -10, 0, 5, 0, 0, 0, 0, -10,
    0, -13, 0, -9, -6, 0, -4, -1,
    -6, -5, 0, 0, 0, 0, -9, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, -8,
    -4, -3, -3, -6, -4, -8, -5, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -8, 0, 0, -5, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, -8, 0, 0, -6,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, -14, -5, -3, -6, -3, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, -4, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 3, -4, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -3, 0, -4,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, -14, -10, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -3, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -17, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    -1, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -12, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -3, 0, 0, 0, -3, 0, 0,
    0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 43,
    .right_class_cnt     = 38,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t jura_bold_8 = {
#else
lv_font_t jura_bold_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 8,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JURA_BOLD_8*/

