/*******************************************************************************
 * Size: 12 px
 * Bpp: 4
 * Opts: --font jura.ttf -r 0x20-0x7F --format lvgl --no-compress --bpp 4 --size 12 -o jura_12.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef JURA_12
#define JURA_12 1
#endif

#if JURA_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x7, 0x8, 0x8, 0x8, 0x8, 0x8, 0x6, 0x0,
    0x18,

    /* U+0022 "\"" */
    0x26, 0x62, 0x66, 0x26, 0x60, 0x0,

    /* U+0023 "#" */
    0x0, 0x16, 0x7, 0x0, 0x6, 0x14, 0x40, 0x7,
    0xc8, 0xc8, 0x50, 0x8, 0x8, 0x0, 0x1, 0x60,
    0x80, 0x4, 0xb9, 0x9b, 0x70, 0x8, 0x7, 0x10,
    0x0, 0x70, 0x70, 0x0,

    /* U+0024 "$" */
    0x0, 0x5, 0x10, 0x0, 0x39, 0xea, 0x90, 0x8,
    0x6, 0x12, 0x50, 0x70, 0x61, 0x4, 0x7, 0x6,
    0x10, 0x0, 0x18, 0xf9, 0x81, 0x0, 0x7, 0x11,
    0x70, 0x80, 0x71, 0x7, 0x7, 0x8f, 0x99, 0x20,
    0x0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+0025 "%" */
    0x29, 0x86, 0x0, 0x71, 0x61, 0x8, 0x3, 0x60,
    0x52, 0x8, 0x19, 0x0, 0x18, 0x84, 0x91, 0x0,
    0x0, 0x6, 0x37, 0x86, 0x0, 0x36, 0x25, 0x8,
    0x1, 0x90, 0x34, 0x7, 0x7, 0x10, 0x9, 0x88,

    /* U+0026 "&" */
    0x1, 0x98, 0x90, 0x0, 0x6, 0x10, 0x23, 0x0,
    0x5, 0x30, 0x0, 0x0, 0x8, 0xd2, 0x0, 0x0,
    0x25, 0x9, 0x23, 0x0, 0x43, 0x0, 0x8a, 0x0,
    0x16, 0x0, 0xf, 0x30, 0x7, 0x88, 0x93, 0x50,

    /* U+0027 "'" */
    0x25, 0x25, 0x25, 0x0,

    /* U+0028 "(" */
    0x5, 0x72, 0x60, 0x52, 0x6, 0x10, 0x61, 0x6,
    0x10, 0x61, 0x6, 0x10, 0x52, 0x2, 0x60, 0x6,
    0x70,

    /* U+0029 ")" */
    0x76, 0x0, 0x53, 0x1, 0x60, 0x7, 0x0, 0x70,
    0x7, 0x0, 0x70, 0x7, 0x1, 0x60, 0x53, 0x66,
    0x0,

    /* U+002A "*" */
    0x1, 0x71, 0xa, 0xf5, 0x18, 0xc7, 0x0, 0x40,

    /* U+002B "+" */
    0x0, 0x13, 0x0, 0x0, 0x35, 0x0, 0x8, 0xbd,
    0x85, 0x0, 0x35, 0x0, 0x0, 0x35, 0x0, 0x0,
    0x1, 0x0,

    /* U+002C "," */
    0x0, 0x65, 0x80,

    /* U+002D "-" */
    0x8, 0x88, 0x40,

    /* U+002E "." */
    0x18,

    /* U+002F "/" */
    0x0, 0x7, 0x0, 0x34, 0x0, 0x70, 0x0, 0x80,
    0x0, 0x80, 0x2, 0x50, 0x6, 0x10, 0x8, 0x0,
    0x8, 0x0, 0x16, 0x0, 0x52, 0x0,

    /* U+0030 "0" */
    0x7, 0x88, 0x86, 0x3, 0x50, 0x0, 0x71, 0x52,
    0x0, 0x4, 0x35, 0x20, 0x90, 0x43, 0x52, 0x0,
    0x4, 0x35, 0x20, 0x0, 0x43, 0x35, 0x0, 0x7,
    0x10, 0x78, 0x88, 0x60,

    /* U+0031 "1" */
    0x7, 0x65, 0x66, 0x1, 0x60, 0x16, 0x1, 0x60,
    0x16, 0x1, 0x60, 0x16,

    /* U+0032 "2" */
    0x8, 0x88, 0x85, 0x2, 0x50, 0x0, 0x80, 0x0,
    0x0, 0x8, 0x0, 0x0, 0x6, 0x50, 0x0, 0x29,
    0x30, 0x0, 0x47, 0x0, 0x0, 0x9, 0x0, 0x0,
    0x1, 0xb8, 0x88, 0x80,

    /* U+0033 "3" */
    0x7, 0x88, 0x86, 0x0, 0x60, 0x0, 0x80, 0x0,
    0x0, 0x7, 0x0, 0x2, 0x8a, 0x60, 0x0, 0x0,
    0x7, 0x1, 0x0, 0x0, 0x52, 0x34, 0x0, 0x7,
    0x10, 0x88, 0x88, 0x70,

    /* U+0034 "4" */
    0x0, 0x0, 0x66, 0x0, 0x0, 0x38, 0x60, 0x0,
    0x18, 0x16, 0x0, 0x9, 0x1, 0x60, 0x8, 0x10,
    0x26, 0x2, 0xa8, 0x8a, 0xe1, 0x0, 0x0, 0x25,
    0x0, 0x0, 0x2, 0x50,

    /* U+0035 "5" */
    0x1b, 0x88, 0x88, 0x1, 0x60, 0x0, 0x0, 0x1b,
    0x88, 0x84, 0x0, 0x30, 0x0, 0x80, 0x0, 0x0,
    0x6, 0x11, 0x10, 0x0, 0x52, 0x25, 0x0, 0x7,
    0x0, 0x88, 0x88, 0x60,

    /* U+0036 "6" */
    0x8, 0x88, 0x88, 0x3, 0x40, 0x0, 0x40, 0x47,
    0x88, 0x84, 0x4, 0x60, 0x0, 0x80, 0x43, 0x0,
    0x6, 0x14, 0x30, 0x0, 0x52, 0x25, 0x0, 0x7,
    0x0, 0x88, 0x88, 0x60,

    /* U+0037 "7" */
    0x78, 0x88, 0xa0, 0x0, 0x8, 0x0, 0x4, 0x50,
    0x4, 0x60, 0x1, 0x70, 0x0, 0x70, 0x0, 0x8,
    0x0, 0x0, 0x70, 0x0,

    /* U+0038 "8" */
    0x7, 0x88, 0x86, 0x0, 0x70, 0x0, 0x70, 0x7,
    0x0, 0x9, 0x0, 0x99, 0x8a, 0x80, 0x26, 0x0,
    0x5, 0x5, 0x20, 0x0, 0x52, 0x34, 0x0, 0x7,
    0x10, 0x88, 0x88, 0x70,

    /* U+0039 "9" */
    0x8, 0x88, 0x86, 0x3, 0x40, 0x0, 0x70, 0x43,
    0x0, 0x5, 0x22, 0x60, 0x0, 0x82, 0x6, 0x88,
    0x78, 0x21, 0x10, 0x0, 0x52, 0x25, 0x0, 0x7,
    0x10, 0x88, 0x88, 0x70,

    /* U+003A ":" */
    0x18, 0x0, 0x0, 0x0, 0x18,

    /* U+003B ";" */
    0x45, 0x0, 0x0, 0x0, 0x65, 0x80,

    /* U+003C "<" */
    0x0, 0x5, 0x20, 0x29, 0x40, 0x76, 0x0, 0x3,
    0x93, 0x0, 0x0, 0x68, 0x0, 0x0, 0x11,

    /* U+003D "=" */
    0x8, 0x88, 0x85, 0x0, 0x0, 0x0, 0x8, 0x88,
    0x85,

    /* U+003E ">" */
    0x61, 0x0, 0x0, 0x87, 0x0, 0x0, 0x2a, 0x20,
    0x7, 0x80, 0x49, 0x20, 0x2, 0x0, 0x0,

    /* U+003F "?" */
    0x38, 0x88, 0x58, 0x0, 0x8, 0x20, 0x0, 0x80,
    0x0, 0x28, 0x0, 0x28, 0x0, 0x8, 0x0, 0x0,
    0x20, 0x0, 0x9, 0x0,

    /* U+0040 "@" */
    0x5, 0x88, 0x88, 0x81, 0x8, 0x29, 0x8a, 0x7,
    0x7, 0x70, 0x8, 0x8, 0x7, 0x80, 0x8, 0x8,
    0x7, 0x70, 0xa, 0x8, 0x7, 0x18, 0x86, 0x84,
    0x7, 0x88, 0x88, 0x83,

    /* U+0041 "A" */
    0x0, 0xb, 0x0, 0x0, 0x3, 0x76, 0x0, 0x0,
    0x80, 0x80, 0x0, 0x17, 0x5, 0x30, 0x7, 0x10,
    0x8, 0x0, 0xb8, 0x88, 0xb0, 0x44, 0x0, 0x2,
    0x68, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0,

    /* U+0042 "B" */
    0xb8, 0x88, 0x80, 0x80, 0x0, 0x52, 0x80, 0x0,
    0x61, 0xb8, 0x88, 0xb0, 0x80, 0x0, 0x17, 0x80,
    0x0, 0x8, 0x80, 0x0, 0x7, 0xb8, 0x88, 0x91,

    /* U+0043 "C" */
    0x4, 0x88, 0x88, 0x50, 0x8, 0x0, 0x0, 0x80,
    0x7, 0x0, 0x0, 0x10, 0x7, 0x0, 0x0, 0x0,
    0x7, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x10,
    0x8, 0x0, 0x0, 0x80, 0x4, 0x88, 0x88, 0x50,

    /* U+0044 "D" */
    0xb8, 0x88, 0x82, 0x8, 0x0, 0x0, 0x80, 0x80,
    0x0, 0x7, 0x8, 0x0, 0x0, 0x70, 0x80, 0x0,
    0x7, 0x8, 0x0, 0x0, 0x70, 0x80, 0x0, 0x8,
    0xb, 0x88, 0x88, 0x20,

    /* U+0045 "E" */
    0xb8, 0x88, 0x80, 0x80, 0x0, 0x0, 0x80, 0x0,
    0x0, 0xb8, 0x85, 0x0, 0x80, 0x0, 0x0, 0x80,
    0x0, 0x0, 0x80, 0x0, 0x0, 0xb8, 0x88, 0x80,

    /* U+0046 "F" */
    0xb8, 0x88, 0x68, 0x0, 0x0, 0x80, 0x0, 0xb,
    0x88, 0x50, 0x80, 0x0, 0x8, 0x0, 0x0, 0x80,
    0x0, 0x7, 0x0, 0x0,

    /* U+0047 "G" */
    0x4, 0x88, 0x88, 0x50, 0x8, 0x0, 0x0, 0x80,
    0x7, 0x0, 0x0, 0x10, 0x7, 0x0, 0x0, 0x0,
    0x7, 0x0, 0x8, 0xa0, 0x7, 0x0, 0x0, 0x70,
    0x8, 0x0, 0x0, 0x80, 0x4, 0x88, 0x88, 0x50,

    /* U+0048 "H" */
    0x70, 0x0, 0x5, 0x28, 0x0, 0x0, 0x52, 0x80,
    0x0, 0x5, 0x2b, 0x88, 0x88, 0xb2, 0x80, 0x0,
    0x5, 0x28, 0x0, 0x0, 0x52, 0x80, 0x0, 0x5,
    0x27, 0x0, 0x0, 0x52,

    /* U+0049 "I" */
    0x78, 0x88, 0x88, 0x87,

    /* U+004A "J" */
    0x0, 0x0, 0x70, 0x0, 0x8, 0x0, 0x0, 0x80,
    0x0, 0x8, 0x0, 0x0, 0x81, 0x0, 0x7, 0x80,
    0x0, 0x82, 0x98, 0x85,

    /* U+004B "K" */
    0x0, 0x0, 0x0, 0x70, 0x2, 0x70, 0x80, 0x29,
    0x0, 0x81, 0x90, 0x0, 0x8c, 0x20, 0x0, 0xc2,
    0x90, 0x0, 0x80, 0x27, 0x0, 0x80, 0x5, 0x40,
    0x70, 0x0, 0x81, 0x0, 0x0, 0x0,

    /* U+004C "L" */
    0x70, 0x0, 0x8, 0x0, 0x0, 0x80, 0x0, 0x8,
    0x0, 0x0, 0x80, 0x0, 0x8, 0x0, 0x0, 0x80,
    0x0, 0xb, 0x88, 0x84,

    /* U+004D "M" */
    0xb0, 0x0, 0x0, 0x91, 0xa6, 0x0, 0x3, 0xb2,
    0x87, 0x10, 0x9, 0x62, 0x80, 0x80, 0x72, 0x62,
    0x80, 0x47, 0x70, 0x62, 0x80, 0x7, 0x0, 0x62,
    0x80, 0x0, 0x0, 0x62, 0x70, 0x0, 0x0, 0x51,

    /* U+004E "N" */
    0xb0, 0x0, 0x5, 0x2a, 0x80, 0x0, 0x52, 0x85,
    0x50, 0x5, 0x28, 0x8, 0x20, 0x52, 0x80, 0x9,
    0x5, 0x28, 0x0, 0x27, 0x52, 0x80, 0x0, 0x5a,
    0x27, 0x0, 0x0, 0x92,

    /* U+004F "O" */
    0x4, 0x88, 0x88, 0x60, 0x8, 0x0, 0x0, 0x61,
    0x7, 0x0, 0x0, 0x33, 0x7, 0x0, 0x0, 0x34,
    0x7, 0x0, 0x0, 0x34, 0x7, 0x0, 0x0, 0x33,
    0x8, 0x0, 0x0, 0x61, 0x4, 0x88, 0x88, 0x60,

    /* U+0050 "P" */
    0xb8, 0x88, 0x70, 0x80, 0x0, 0x70, 0x80, 0x0,
    0x52, 0x80, 0x0, 0x80, 0xb8, 0x88, 0x40, 0x80,
    0x0, 0x0, 0x80, 0x0, 0x0, 0x70, 0x0, 0x0,

    /* U+0051 "Q" */
    0x4, 0x88, 0x88, 0x60, 0x8, 0x0, 0x0, 0x61,
    0x7, 0x0, 0x0, 0x33, 0x7, 0x0, 0x0, 0x34,
    0x7, 0x0, 0x0, 0x34, 0x7, 0x0, 0x0, 0x33,
    0x8, 0x0, 0x5, 0x71, 0x4, 0x88, 0x8a, 0xf0,
    0x0, 0x0, 0x0, 0x21,

    /* U+0052 "R" */
    0xb8, 0x88, 0x70, 0x80, 0x0, 0x70, 0x80, 0x0,
    0x52, 0x80, 0x0, 0x80, 0xb8, 0x8b, 0x40, 0x80,
    0x8, 0x10, 0x80, 0x1, 0x80, 0x70, 0x0, 0x63,
    0x0, 0x0, 0x1,

    /* U+0053 "S" */
    0x5, 0x88, 0x88, 0x40, 0x80, 0x0, 0x8, 0x8,
    0x0, 0x0, 0x0, 0x38, 0x88, 0x81, 0x0, 0x0,
    0x0, 0x80, 0x40, 0x0, 0x7, 0x8, 0x0, 0x0,
    0x80, 0x58, 0x88, 0x83,

    /* U+0054 "T" */
    0x68, 0x8c, 0x88, 0x30, 0x0, 0x80, 0x0, 0x0,
    0x8, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x8,
    0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x8, 0x0,
    0x0, 0x0, 0x70, 0x0,

    /* U+0055 "U" */
    0x70, 0x0, 0x2, 0x48, 0x0, 0x0, 0x25, 0x80,
    0x0, 0x2, 0x58, 0x0, 0x0, 0x25, 0x80, 0x0,
    0x2, 0x58, 0x0, 0x0, 0x24, 0x80, 0x0, 0x5,
    0x24, 0x98, 0x88, 0x70,

    /* U+0056 "V" */
    0x70, 0x0, 0x0, 0x70, 0x62, 0x0, 0x0, 0x70,
    0x8, 0x0, 0x6, 0x20, 0x7, 0x0, 0x8, 0x0,
    0x1, 0x60, 0x44, 0x0, 0x0, 0x80, 0x80, 0x0,
    0x0, 0x46, 0x60, 0x0, 0x0, 0xb, 0x0, 0x0,

    /* U+0057 "W" */
    0x70, 0x0, 0x56, 0x0, 0x7, 0x70, 0x0, 0x88,
    0x0, 0x8, 0x35, 0x0, 0x87, 0x0, 0x44, 0x8,
    0x3, 0x43, 0x40, 0x80, 0x8, 0x7, 0x0, 0x80,
    0x80, 0x4, 0x48, 0x0, 0x83, 0x50, 0x0, 0xa6,
    0x0, 0x5a, 0x0, 0x0, 0xa1, 0x0, 0xa, 0x0,

    /* U+0058 "X" */
    0x0, 0x0, 0x0, 0x3, 0x60, 0x0, 0x90, 0x8,
    0x20, 0x72, 0x0, 0x9, 0x36, 0x0, 0x0, 0x4b,
    0x0, 0x0, 0x8, 0x82, 0x0, 0x3, 0x50, 0x90,
    0x0, 0x90, 0x3, 0x60, 0x62, 0x0, 0x7, 0x10,
    0x0, 0x0, 0x0,

    /* U+0059 "Y" */
    0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x90, 0x27,
    0x0, 0x44, 0x0, 0x71, 0x8, 0x0, 0x0, 0x87,
    0x20, 0x0, 0x5, 0x70, 0x0, 0x0, 0x25, 0x0,
    0x0, 0x2, 0x50, 0x0, 0x0, 0x24, 0x0, 0x0,

    /* U+005A "Z" */
    0x29, 0x88, 0x8b, 0x45, 0x0, 0x1, 0x80, 0x0,
    0x0, 0x91, 0x0, 0x0, 0x64, 0x0, 0x0, 0x28,
    0x0, 0x0, 0x9, 0x0, 0x0, 0x8, 0x20, 0x0,
    0x62, 0xd8, 0x88, 0x93,

    /* U+005B "[" */
    0x48, 0x6, 0x10, 0x61, 0x6, 0x10, 0x61, 0x6,
    0x10, 0x61, 0x6, 0x10, 0x61, 0x6, 0x10, 0x48,
    0x0,

    /* U+005C "\\" */
    0x52, 0x0, 0x26, 0x0, 0x8, 0x0, 0x8, 0x0,
    0x6, 0x10, 0x2, 0x50, 0x0, 0x80, 0x0, 0x80,
    0x0, 0x70, 0x0, 0x34, 0x0, 0x6,

    /* U+005D "]" */
    0x66, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0x66,

    /* U+005E "^" */
    0x4, 0xa0, 0x8, 0x62, 0x16, 0x7,

    /* U+005F "_" */
    0x28, 0x88, 0x0,

    /* U+0060 "`" */
    0x21, 0x0, 0x90, 0x1, 0x0,

    /* U+0061 "a" */
    0x6, 0x88, 0x85, 0x5, 0x0, 0x8, 0x5, 0x88,
    0x8c, 0x8, 0x0, 0x8, 0x8, 0x0, 0xb, 0x7,
    0x88, 0x89,

    /* U+0062 "b" */
    0x70, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80, 0x0,
    0x0, 0x98, 0x88, 0x80, 0xa0, 0x0, 0x52, 0x80,
    0x0, 0x34, 0x80, 0x0, 0x34, 0xa0, 0x0, 0x52,
    0x88, 0x88, 0x80,

    /* U+0063 "c" */
    0x5, 0x88, 0x86, 0x8, 0x0, 0x4, 0x7, 0x0,
    0x0, 0x7, 0x0, 0x0, 0x8, 0x0, 0x4, 0x5,
    0x88, 0x86,

    /* U+0064 "d" */
    0x0, 0x0, 0x5, 0x20, 0x0, 0x0, 0x52, 0x0,
    0x0, 0x5, 0x20, 0x58, 0x88, 0xb2, 0x8, 0x0,
    0x5, 0x20, 0x70, 0x0, 0x52, 0x7, 0x0, 0x5,
    0x20, 0x80, 0x0, 0x82, 0x5, 0x88, 0x89, 0x20,

    /* U+0065 "e" */
    0x5, 0x88, 0x87, 0x0, 0x70, 0x0, 0x61, 0xc,
    0x88, 0x89, 0x10, 0x70, 0x0, 0x0, 0x9, 0x0,
    0x7, 0x0, 0x69, 0x88, 0x70,

    /* U+0066 "f" */
    0x4, 0x93, 0x8, 0x0, 0x7, 0x0, 0x5c, 0x83,
    0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x8, 0x0,
    0x7, 0x0,

    /* U+0067 "g" */
    0x5, 0x88, 0x8a, 0x10, 0x80, 0x0, 0x72, 0x7,
    0x0, 0x5, 0x20, 0x70, 0x0, 0x52, 0x8, 0x0,
    0x8, 0x20, 0x58, 0x88, 0x82, 0x0, 0x0, 0x5,
    0x20, 0x50, 0x0, 0x61, 0x8, 0x88, 0x89, 0x0,

    /* U+0068 "h" */
    0x70, 0x0, 0x0, 0x80, 0x0, 0x0, 0x80, 0x0,
    0x0, 0x98, 0x88, 0x60, 0xb0, 0x0, 0x70, 0x80,
    0x0, 0x52, 0x80, 0x0, 0x52, 0x80, 0x0, 0x52,
    0x70, 0x0, 0x52,

    /* U+0069 "i" */
    0x1b, 0x0, 0x7, 0x8, 0x8, 0x8, 0x8, 0x7,

    /* U+006A "j" */
    0x1, 0xb0, 0x0, 0x0, 0x70, 0x8, 0x0, 0x80,
    0x8, 0x0, 0x80, 0x8, 0x0, 0x80, 0x7, 0x19,
    0x30,

    /* U+006B "k" */
    0x70, 0x0, 0x8, 0x0, 0x0, 0x80, 0x0, 0x8,
    0x1, 0x90, 0x81, 0x91, 0xa, 0xc1, 0x0, 0xa2,
    0x80, 0x8, 0x3, 0x70, 0x70, 0x5, 0x30, 0x0,
    0x0,

    /* U+006C "l" */
    0x70, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x70,
    0x77,

    /* U+006D "m" */
    0x98, 0x89, 0x68, 0x87, 0x9, 0x0, 0x46, 0x0,
    0x80, 0x80, 0x3, 0x40, 0x7, 0x8, 0x0, 0x34,
    0x0, 0x70, 0x80, 0x3, 0x40, 0x7, 0x7, 0x0,
    0x24, 0x0, 0x70,

    /* U+006E "n" */
    0x98, 0x88, 0x60, 0xb0, 0x0, 0x70, 0x80, 0x0,
    0x52, 0x80, 0x0, 0x52, 0x80, 0x0, 0x52, 0x70,
    0x0, 0x52,

    /* U+006F "o" */
    0x6, 0x98, 0x86, 0x0, 0x80, 0x0, 0x70, 0x7,
    0x0, 0x5, 0x20, 0x70, 0x0, 0x52, 0x8, 0x0,
    0x7, 0x0, 0x58, 0x88, 0x60,

    /* U+0070 "p" */
    0x88, 0x88, 0x80, 0xb0, 0x0, 0x52, 0x80, 0x0,
    0x34, 0x80, 0x0, 0x34, 0x80, 0x0, 0x52, 0xb8,
    0x88, 0x80, 0x80, 0x0, 0x0, 0x80, 0x0, 0x0,
    0x70, 0x0, 0x0,

    /* U+0071 "q" */
    0x5, 0x88, 0x89, 0x10, 0x80, 0x0, 0x82, 0x7,
    0x0, 0x5, 0x20, 0x70, 0x0, 0x52, 0x8, 0x0,
    0x5, 0x20, 0x58, 0x88, 0xb2, 0x0, 0x0, 0x5,
    0x20, 0x0, 0x0, 0x52, 0x0, 0x0, 0x5, 0x20,

    /* U+0072 "r" */
    0x77, 0x81, 0xc1, 0x0, 0x80, 0x0, 0x80, 0x0,
    0x80, 0x0, 0x70, 0x0,

    /* U+0073 "s" */
    0x9, 0x88, 0x84, 0x25, 0x0, 0x4, 0x8, 0x88,
    0x83, 0x0, 0x0, 0x8, 0x33, 0x0, 0x8, 0x9,
    0x88, 0x85,

    /* U+0074 "t" */
    0x3, 0x0, 0x8, 0x0, 0x6c, 0x84, 0x8, 0x0,
    0x8, 0x0, 0x8, 0x0, 0x8, 0x0, 0x3, 0x94,

    /* U+0075 "u" */
    0x7, 0x0, 0x7, 0x0, 0x70, 0x0, 0x70, 0x7,
    0x0, 0x7, 0x0, 0x70, 0x0, 0x70, 0x8, 0x0,
    0xa, 0x0, 0x58, 0x88, 0x90,

    /* U+0076 "v" */
    0x0, 0x0, 0x0, 0x80, 0x0, 0x17, 0x35, 0x0,
    0x71, 0x9, 0x0, 0x80, 0x5, 0x36, 0x20, 0x0,
    0x89, 0x0, 0x0, 0x94, 0x0,

    /* U+0077 "w" */
    0x40, 0x3, 0x70, 0x4, 0x7, 0x0, 0x79, 0x0,
    0x80, 0x25, 0x7, 0x70, 0x35, 0x0, 0x81, 0x53,
    0x47, 0x0, 0x7, 0x60, 0x7, 0x70, 0x0, 0x3a,
    0x0, 0xa4, 0x0,

    /* U+0078 "x" */
    0x0, 0x0, 0x0, 0x25, 0x0, 0x61, 0x8, 0x13,
    0x60, 0x0, 0x98, 0x0, 0x0, 0xa7, 0x0, 0x8,
    0x26, 0x40, 0x44, 0x0, 0x80, 0x0, 0x0, 0x0,

    /* U+0079 "y" */
    0x7, 0x0, 0x7, 0x7, 0x0, 0x8, 0x7, 0x0,
    0x8, 0x7, 0x0, 0x8, 0x8, 0x0, 0xb, 0x6,
    0x88, 0x8a, 0x0, 0x0, 0x8, 0x7, 0x0, 0x8,
    0x7, 0x88, 0x87,

    /* U+007A "z" */
    0x29, 0x88, 0xd1, 0x30, 0x4, 0x60, 0x0, 0x19,
    0x0, 0x0, 0x90, 0x0, 0x7, 0x30, 0x4, 0x2d,
    0x88, 0x95,

    /* U+007B "{" */
    0x0, 0x85, 0x4, 0x30, 0x6, 0x10, 0x7, 0x10,
    0x8, 0x0, 0x58, 0x0, 0x9, 0x0, 0x7, 0x10,
    0x6, 0x10, 0x5, 0x20, 0x0, 0x75,

    /* U+007C "|" */
    0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0x3,

    /* U+007D "}" */
    0x66, 0x0, 0x6, 0x10, 0x4, 0x30, 0x4, 0x30,
    0x4, 0x50, 0x0, 0xb2, 0x3, 0x60, 0x4, 0x30,
    0x4, 0x30, 0x6, 0x10, 0x66, 0x0,

    /* U+007E "~" */
    0x6, 0x82, 0x5, 0x14, 0x6, 0x82
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 40, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 52, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 15, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 35, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 150, .adv_w = 49, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 167, .adv_w = 49, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 184, .adv_w = 74, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 192, .adv_w = 105, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 210, .adv_w = 36, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 213, .adv_w = 88, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 216, .adv_w = 40, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 239, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 110, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 110, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 110, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 40, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 36, .box_w = 2, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 506, .adv_w = 105, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 521, .adv_w = 105, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 530, .adv_w = 105, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 545, .adv_w = 91, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 137, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 625, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 105, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 126, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 43, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 103, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 867, .adv_w = 93, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 947, .adv_w = 132, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 979, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1003, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1039, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1066, .adv_w = 125, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1094, .adv_w = 106, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1122, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1150, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1182, .adv_w = 161, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1222, .adv_w = 107, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1257, .adv_w = 99, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1289, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1317, .adv_w = 36, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1334, .adv_w = 67, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1356, .adv_w = 36, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1367, .adv_w = 71, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 1373, .adv_w = 82, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1376, .adv_w = 45, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1381, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1399, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1426, .adv_w = 108, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1444, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1476, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1497, .adv_w = 59, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1515, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1547, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1574, .adv_w = 43, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1582, .adv_w = 43, .box_w = 3, .box_h = 11, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 1599, .adv_w = 90, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1624, .adv_w = 53, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1633, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1660, .adv_w = 114, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1678, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1699, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1726, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1758, .adv_w = 69, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1770, .adv_w = 104, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1788, .adv_w = 65, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1804, .adv_w = 114, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1825, .adv_w = 94, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1846, .adv_w = 131, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1873, .adv_w = 93, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1897, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1924, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1942, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1964, .adv_w = 39, .box_w = 2, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1975, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1997, .adv_w = 105, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 3}
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
    1, 0, 0, 3, 0, 0, 4, 0,
    5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 16, 16, 0, 0, 0,
    17, 0, 18, 0, 19, 0, 0, 0,
    19, 0, 0, 20, 0, 0, 0, 0,
    19, 0, 19, 0, 2, 21, 0, 22,
    22, 23, 24, 25, 0, 26, 0, 3,
    0, 0, 27, 28, 29, 29, 29, 0,
    29, 28, 0, 30, 28, 28, 31, 31,
    29, 31, 29, 31, 32, 33, 34, 35,
    35, 36, 34, 37, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, -13, -4,
    0, 0, 0, 0, -6, 0, 0, 0,
    0, -4, 0, 0, -10, 0, 0, -4,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -4, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, -4, 0, 0, 0, -12, 0,
    0, 0, 0, 0, 0, 0, -27, -17,
    -17, -21, -13, 0, 0, 0, -6, 0,
    -10, 0, 0, 0, 0, -12, 0, 0,
    0, 0, 0, 0, -6, -6, -6, 0,
    -10, 0, 0, 0, -2, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, -4, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, -6, -2, 0, -6, 0, -4, -13,
    0, 0, -4, 0, 0, 0, 0, 0,
    -4, -6, 0, 0, 0, 0, 0, -2,
    0, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, -10, 0, -8, 0, -4, -15, 0,
    0, 0, 0, -2, -6, 0, -12, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, 0, 0, -8, 0, 0, -12, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -19,
    -6, -19, 0, 0, 0, -13, 0, -2,
    0, 0, 0, -10, 0, 0, 0, 0,
    0, -2, 0, -15, -6, 0, -10, 0,
    0, 0, -4, -4, 0, -2, 0, 0,
    -4, -4, 0, 0, 0, 0, 0, 0,
    0, 0, -8, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    -4, 0, -6, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -4, 0, 0, -4, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -6, 0, 0, 0, -10, 0, 0, 0,
    0, 0, -8, 0, 0, 0, 0, -2,
    0, -2, -8, -4, -4, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -6,
    0, 0, -6, 0, 0, -8, 0, 0,
    0, -4, 0, 0, 0, 0, -4, -2,
    0, -10, 0, 0, -6, 0, 0, 0,
    0, -15, -2, -15, 2, 0, 0, 6,
    0, 0, -10, 0, -13, 0, -13, -12,
    0, -10, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -13, 0, 0, -8, 0, 0,
    -2, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -6, 0, 0, 0, 0,
    -4, -6, 0, 0, -23, 0, -33, -23,
    0, 0, -15, 0, 0, 0, -2, -2,
    -13, -2, -4, 0, 0, 0, -4, 0,
    -17, -13, 0, -19, 0, 0, -4, 0,
    0, 0, 0, 0, -8, -4, -15, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -2, -6, -15, 0, 0, -4, 0, 0,
    0, 0, -12, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -4,
    0, 0, 0, 4, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -2, 0, -2,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, -4, -2, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -27, 0,
    0, -4, 0, -4, -21, 0, 0, 0,
    -8, 0, -15, 0, -15, -8, -19, 0,
    4, 0, 4, 0, 0, -21, -4, -21,
    0, -17, -21, 0, -21, -17, -19, -21,
    0, -6, 0, -13, 0, 0, -4, 0,
    0, -8, 0, 0, 0, -2, 0, -10,
    0, -6, -4, -13, 2, 0, 0, 4,
    0, 0, -12, 0, -13, 0, -4, -10,
    0, -6, 0, 0, 0, 0, 0, 0,
    -17, 0, 0, -6, 0, 0, -2, 0,
    0, -2, -6, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -8, 0, 0, 0, 0, -6, -8,
    0, 0, 0, -6, 0, -21, 0, 0,
    -8, -4, -4, -13, 0, 0, 0, -8,
    0, -13, 0, -10, -5, -15, 0, 8,
    0, 0, 0, 0, -15, 0, -19, 0,
    -13, -10, 0, -6, -2, -10, -8, 0,
    0, 0, -13, 0, 0, -6, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, -12, -6, -4, -4, -10, -6,
    -12, -8, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -12, 0, 0,
    -8, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -12, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, -21, -8, -4, -10, -4, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -4, -6, 0, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -10, 0,
    0, -6, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    4, -6, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -10, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -4, 0, -6, 0, -2, 0, 0, 0,
    0, 0, 0, 0, -15, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -4, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -25, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, -2, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -8,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, 0,
    0, 0, -4, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 43,
    .right_class_cnt     = 37,
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
const lv_font_t jura_12 = {
#else
lv_font_t jura_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JURA_12*/

