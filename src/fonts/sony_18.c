/*******************************************************************************
 * Size: 18 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef SONY_18
#define SONY_18 1
#endif

#if SONY_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xcf, 0xc, 0xf0, 0xcf, 0xc, 0xf0, 0xcf, 0xc,
    0xf0, 0xcf, 0x7, 0x90, 0xcf, 0x0,

    /* U+0022 "\"" */
    0xf, 0x2f, 0x0, 0xd0, 0xd0,

    /* U+0023 "#" */
    0x0, 0x3, 0xf6, 0x6, 0xf2, 0x0, 0x0, 0x7f,
    0x10, 0xae, 0x0, 0xa, 0xff, 0xff, 0xff, 0xff,
    0x90, 0x1, 0xeb, 0x12, 0xf7, 0x10, 0x0, 0x1f,
    0x80, 0x4f, 0x40, 0x3, 0xff, 0xff, 0xff, 0xff,
    0xe0, 0x2, 0x9f, 0x32, 0xbe, 0x21, 0x0, 0xb,
    0xe0, 0xe, 0xb0, 0x0, 0x0, 0xeb, 0x1, 0xf7,
    0x0, 0x0,

    /* U+0024 "$" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x0,
    0x0, 0x8, 0xef, 0xff, 0xff, 0x64, 0xfc, 0x6b,
    0x55, 0x52, 0x6f, 0x50, 0x90, 0x0, 0x5, 0xfa,
    0x19, 0x10, 0x0, 0xc, 0xff, 0xff, 0xfa, 0x0,
    0x2, 0x4b, 0x4b, 0xf5, 0x0, 0x0, 0x90, 0x6f,
    0x62, 0x55, 0x5b, 0x5c, 0xf4, 0x6f, 0xff, 0xff,
    0xe8, 0x0, 0x0, 0x9, 0x0, 0x0,

    /* U+0025 "%" */
    0x3d, 0xff, 0xfb, 0x0, 0x0, 0xdb, 0x0, 0x0,
    0x7f, 0x0, 0x5f, 0x10, 0xa, 0xd1, 0x0, 0x0,
    0x7e, 0x0, 0x4f, 0x20, 0x6f, 0x30, 0x0, 0x0,
    0x7f, 0x0, 0x5f, 0x13, 0xf8, 0xcf, 0xff, 0xa0,
    0x3d, 0xff, 0xfa, 0x1e, 0xa6, 0xf1, 0x5, 0xf1,
    0x0, 0x0, 0x0, 0xbd, 0x7, 0xf0, 0x3, 0xf2,
    0x0, 0x0, 0x7, 0xf2, 0x7, 0xf0, 0x3, 0xf2,
    0x0, 0x0, 0x4f, 0x50, 0x6, 0xf1, 0x5, 0xf1,
    0x0, 0x1, 0xe9, 0x0, 0x2, 0xdf, 0xff, 0xa0,

    /* U+0026 "&" */
    0x0, 0xaf, 0xff, 0xd4, 0x0, 0x0, 0x7f, 0x94,
    0x5f, 0xd0, 0x0, 0x7, 0xf4, 0x0, 0xed, 0x0,
    0x0, 0x1e, 0xd8, 0xdf, 0x50, 0x0, 0x4, 0xcf,
    0xfc, 0x10, 0x64, 0x2, 0xfc, 0x3a, 0xf9, 0x1f,
    0xa0, 0x6f, 0x50, 0x7, 0xfd, 0xf9, 0x4, 0xfc,
    0x65, 0x5b, 0xff, 0x60, 0x6, 0xdf, 0xff, 0xfb,
    0xdf, 0x40,

    /* U+0027 "'" */
    0xf, 0xd, 0x3,

    /* U+0028 "(" */
    0x3f, 0xb0, 0xbf, 0x10, 0xed, 0x0, 0xed, 0x0,
    0xed, 0x0, 0xed, 0x0, 0xed, 0x0, 0xed, 0x0,
    0xed, 0x0, 0xed, 0x0, 0xee, 0x0, 0xbf, 0x10,
    0x3f, 0xb0,

    /* U+0029 ")" */
    0x1d, 0xe1, 0x3, 0xf9, 0x0, 0xfb, 0x0, 0xfb,
    0x0, 0xfb, 0x0, 0xfb, 0x0, 0xfb, 0x0, 0xfb,
    0x0, 0xfb, 0x0, 0xfb, 0x0, 0xfb, 0x3, 0xf9,
    0x1d, 0xe1,

    /* U+002A "*" */
    0x0, 0xf, 0x0, 0x0, 0x40, 0xf0, 0x40, 0x1c,
    0xef, 0xec, 0x20, 0x8, 0xf8, 0x0, 0x3, 0xe2,
    0xe3, 0x0, 0x23, 0x4, 0x20,

    /* U+002B "+" */
    0x0, 0x4, 0xf4, 0x0, 0x0, 0x0, 0x4f, 0x40,
    0x0, 0x6f, 0xff, 0xff, 0xff, 0x60, 0x0, 0x4f,
    0x40, 0x0, 0x0, 0x4, 0xf4, 0x0, 0x0, 0x0,
    0x15, 0x10, 0x0,

    /* U+002C "," */
    0x2b, 0x2, 0xe0, 0x48, 0x0,

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0x38, 0x5, 0xd0,

    /* U+002F "/" */
    0x0, 0x0, 0x0, 0xbc, 0x0, 0x0, 0x0, 0x6f,
    0x20, 0x0, 0x0, 0x2f, 0x60, 0x0, 0x0, 0xb,
    0xb0, 0x0, 0x0, 0x7, 0xf1, 0x0, 0x0, 0x2,
    0xf5, 0x0, 0x0, 0x0, 0xcb, 0x0, 0x0, 0x0,
    0x7e, 0x10, 0x0, 0x0, 0x2f, 0x50, 0x0, 0x0,
    0x0,

    /* U+0030 "0" */
    0x3c, 0xff, 0xff, 0xe8, 0xc, 0xf8, 0x56, 0xed,
    0xf5, 0xed, 0x0, 0x8f, 0x8f, 0x7f, 0xc0, 0x2f,
    0xa4, 0xf7, 0xfc, 0xb, 0xf1, 0x4f, 0x7f, 0xc5,
    0xf6, 0x4, 0xf7, 0xed, 0xcc, 0x0, 0x4f, 0x7d,
    0xfa, 0x75, 0x6c, 0xf5, 0x3c, 0xff, 0xff, 0xe9,
    0x0,

    /* U+0031 "1" */
    0xbf, 0xff, 0x33, 0x5b, 0xf3, 0x0, 0x8f, 0x30,
    0x8, 0xf3, 0x0, 0x8f, 0x30, 0x8, 0xf3, 0x0,
    0x8f, 0x30, 0x8, 0xf3, 0x0, 0x8f, 0x30,

    /* U+0032 "2" */
    0xaf, 0xff, 0xff, 0xd5, 0x3, 0x55, 0x55, 0x6e,
    0xf0, 0x0, 0x0, 0x0, 0x9f, 0x20, 0x0, 0x11,
    0x2d, 0xf1, 0x1c, 0xff, 0xff, 0xf9, 0x8, 0xf9,
    0x44, 0x41, 0x0, 0xaf, 0x10, 0x0, 0x0, 0xa,
    0xf6, 0x55, 0x55, 0x50, 0xaf, 0xff, 0xff, 0xff,
    0x20,

    /* U+0033 "3" */
    0xbf, 0xff, 0xff, 0xd5, 0x4, 0x55, 0x55, 0x6e,
    0xf0, 0x0, 0x0, 0x0, 0xbf, 0x0, 0x0, 0x11,
    0x2d, 0xe0, 0x0, 0x2f, 0xff, 0xf4, 0x0, 0x0,
    0x44, 0x5e, 0xd0, 0x0, 0x0, 0x0, 0xbf, 0x4,
    0x55, 0x55, 0x7f, 0xf0, 0xbf, 0xff, 0xff, 0xd4,
    0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0xee, 0x1c, 0xf0, 0x0, 0xaf, 0x40,
    0xcf, 0x0, 0x5f, 0x80, 0xc, 0xf0, 0x1e, 0xd0,
    0x0, 0xcf, 0xb, 0xf4, 0x11, 0x1c, 0xf0, 0xff,
    0xff, 0xff, 0xff, 0x1, 0x44, 0x44, 0x4d, 0xf0,
    0x0, 0x0, 0x0, 0xcf, 0x0, 0x0, 0x0, 0xc,
    0xf0,

    /* U+0035 "5" */
    0xaf, 0xff, 0xff, 0xff, 0x2a, 0xf6, 0x55, 0x55,
    0x50, 0xaf, 0x21, 0x11, 0x0, 0xa, 0xff, 0xff,
    0xfe, 0x50, 0x34, 0x44, 0x46, 0xff, 0x0, 0x0,
    0x0, 0xa, 0xf1, 0x0, 0x0, 0x0, 0xaf, 0x13,
    0x55, 0x55, 0x7f, 0xe0, 0xaf, 0xff, 0xff, 0xc4,
    0x0,

    /* U+0036 "6" */
    0x4, 0xdf, 0xff, 0xff, 0xf2, 0xe, 0xe6, 0x55,
    0x55, 0x50, 0xf, 0xb1, 0x11, 0x10, 0x0, 0xf,
    0xff, 0xff, 0xff, 0xc1, 0xf, 0xd4, 0x44, 0x5a,
    0xf7, 0xf, 0xb0, 0x0, 0x2, 0xf9, 0xf, 0xb0,
    0x0, 0x2, 0xf9, 0xe, 0xf7, 0x55, 0x5b, 0xf7,
    0x4, 0xcf, 0xff, 0xfe, 0x90,

    /* U+0037 "7" */
    0xcf, 0xff, 0xff, 0xfe, 0x14, 0x55, 0x55, 0x5f,
    0xe0, 0x0, 0x0, 0x6, 0xf6, 0x0, 0x0, 0x0,
    0xed, 0x0, 0x0, 0x0, 0x8f, 0x50, 0x0, 0x0,
    0x1f, 0xc0, 0x0, 0x0, 0xa, 0xf3, 0x0, 0x0,
    0x3, 0xfa, 0x0, 0x0, 0x0, 0xcf, 0x20, 0x0,
    0x0,

    /* U+0038 "8" */
    0x5, 0xdf, 0xff, 0xfe, 0x90, 0xf, 0xe7, 0x66,
    0x6c, 0xf5, 0x2f, 0xa0, 0x0, 0x4, 0xf7, 0xf,
    0xd2, 0x11, 0x19, 0xf5, 0x4, 0xff, 0xff, 0xff,
    0x90, 0xe, 0xe6, 0x44, 0x5b, 0xf3, 0x1f, 0xa0,
    0x0, 0x4, 0xf6, 0xf, 0xe6, 0x55, 0x6b, 0xf5,
    0x6, 0xdf, 0xff, 0xfe, 0x90,

    /* U+0039 "9" */
    0x6, 0xdf, 0xff, 0xfe, 0x80, 0x1f, 0xe6, 0x55,
    0x5b, 0xf5, 0x2f, 0x90, 0x0, 0x4, 0xf7, 0x1f,
    0xc2, 0x11, 0x16, 0xf7, 0xb, 0xff, 0xff, 0xff,
    0xf7, 0x0, 0x24, 0x44, 0x47, 0xf7, 0x0, 0x0,
    0x0, 0x4, 0xf7, 0x4, 0x55, 0x55, 0x6c, 0xf5,
    0xc, 0xff, 0xff, 0xfe, 0x90,

    /* U+003A ":" */
    0x0, 0x1, 0xf1, 0x2, 0x0, 0x0, 0xf, 0x10,
    0x20,

    /* U+003B ";" */
    0x0, 0x1, 0xf1, 0x3, 0x0, 0x0, 0x5, 0x0,
    0xc2, 0xa, 0x0,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x5a, 0x60, 0x0, 0x4a, 0xfc,
    0x61, 0x29, 0xec, 0x61, 0x0, 0x4, 0xed, 0x61,
    0x0, 0x0, 0x0, 0x4a, 0xfb, 0x61, 0x0, 0x0,
    0x0, 0x5b, 0xf5, 0x0, 0x0, 0x0, 0x0, 0x10,

    /* U+003D "=" */
    0x5f, 0xff, 0xff, 0xff, 0x70, 0x33, 0x33, 0x33,
    0x31, 0x4e, 0xee, 0xee, 0xee, 0x70, 0x11, 0x11,
    0x11, 0x10,

    /* U+003E ">" */
    0x0, 0x0, 0x0, 0x0, 0x6, 0xb6, 0x10, 0x0,
    0x0, 0x5, 0xbf, 0xb5, 0x0, 0x0, 0x0, 0x16,
    0xbf, 0xa2, 0x0, 0x0, 0x17, 0xde, 0x40, 0x16,
    0xcf, 0xa4, 0x0, 0x5f, 0xa5, 0x0, 0x0, 0x1,
    0x0, 0x0, 0x0, 0x0,

    /* U+003F "?" */
    0x9f, 0xff, 0xff, 0xe6, 0x3, 0x55, 0x55, 0x6e,
    0xf1, 0x0, 0x0, 0x0, 0x9f, 0x20, 0x0, 0x0,
    0x1b, 0xf2, 0x0, 0x3d, 0xff, 0xfb, 0x0, 0x8,
    0xf6, 0x32, 0x0, 0x0, 0x8f, 0x20, 0x0, 0x0,
    0x2, 0x51, 0x0, 0x0, 0x0, 0x9f, 0x30, 0x0,
    0x0,

    /* U+0040 "@" */
    0x0, 0x4, 0xac, 0xcc, 0xc9, 0x20, 0x0, 0xb,
    0xb3, 0x0, 0x0, 0x4c, 0x60, 0xb, 0x80, 0x3c,
    0xdc, 0x7c, 0xd, 0x33, 0xe0, 0x1f, 0x60, 0x1e,
    0x80, 0x78, 0x5b, 0x6, 0xd0, 0x0, 0xd4, 0x9,
    0x73, 0xd0, 0x3f, 0x10, 0x5f, 0x23, 0xe1, 0xc,
    0x70, 0x5b, 0xb7, 0x5b, 0xa2, 0x0, 0x1c, 0x92,
    0x0, 0x0, 0x3, 0x0, 0x0, 0x5, 0xac, 0xcc,
    0xcc, 0x70, 0x0,

    /* U+0041 "A" */
    0x0, 0x0, 0xb, 0xe5, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xde, 0x0, 0x0, 0x0, 0x0, 0xea, 0x3f,
    0x70, 0x0, 0x0, 0x6, 0xf2, 0xb, 0xe0, 0x0,
    0x0, 0xd, 0xa0, 0x3, 0xf6, 0x0, 0x0, 0x5f,
    0xff, 0xff, 0xfd, 0x0, 0x0, 0xdc, 0x33, 0x33,
    0x6f, 0x50, 0x5, 0xf6, 0x0, 0x0, 0xe, 0xd0,
    0xc, 0xf1, 0x0, 0x0, 0x8, 0xf4,

    /* U+0042 "B" */
    0xf, 0xff, 0xff, 0xfe, 0xa0, 0xf, 0xd5, 0x55,
    0x5b, 0xf6, 0xf, 0xb0, 0x0, 0x2, 0xf8, 0xf,
    0xb1, 0x11, 0x17, 0xf6, 0xf, 0xff, 0xff, 0xff,
    0xc0, 0xf, 0xc4, 0x44, 0x49, 0xf6, 0xf, 0xb0,
    0x0, 0x3, 0xf8, 0xf, 0xc5, 0x55, 0x5a, 0xf7,
    0xf, 0xff, 0xff, 0xff, 0xa0,

    /* U+0043 "C" */
    0x5, 0xdf, 0xff, 0xff, 0xc0, 0xff, 0x75, 0x55,
    0x54, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb, 0x0,
    0x0, 0x0, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb,
    0x0, 0x0, 0x0, 0xf, 0xb0, 0x0, 0x0, 0x0,
    0xef, 0x75, 0x55, 0x54, 0x4, 0xdf, 0xff, 0xff,
    0xc0,

    /* U+0044 "D" */
    0xf, 0xff, 0xff, 0xff, 0xb1, 0xf, 0xc5, 0x55,
    0x5a, 0xf8, 0xf, 0xb0, 0x0, 0x1, 0xfa, 0xf,
    0xb0, 0x0, 0x1, 0xfa, 0xf, 0xb0, 0x0, 0x1,
    0xfa, 0xf, 0xb0, 0x0, 0x1, 0xfa, 0xf, 0xb0,
    0x0, 0x1, 0xfa, 0xf, 0xc5, 0x55, 0x5a, 0xf8,
    0xf, 0xff, 0xff, 0xff, 0xa0,

    /* U+0045 "E" */
    0x4, 0xdf, 0xff, 0xff, 0xc0, 0xef, 0x75, 0x55,
    0x54, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb, 0x11,
    0x11, 0x10, 0xf, 0xff, 0xff, 0xff, 0x60, 0xfc,
    0x44, 0x44, 0x41, 0xf, 0xb0, 0x0, 0x0, 0x0,
    0xff, 0x75, 0x55, 0x54, 0x4, 0xdf, 0xff, 0xff,
    0xc0,

    /* U+0046 "F" */
    0x5, 0xdf, 0xff, 0xff, 0xc0, 0xff, 0x75, 0x55,
    0x54, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb, 0x11,
    0x11, 0x10, 0xf, 0xff, 0xff, 0xff, 0xc0, 0xfc,
    0x44, 0x44, 0x43, 0xf, 0xb0, 0x0, 0x0, 0x0,
    0xfb, 0x0, 0x0, 0x0, 0xf, 0xb0, 0x0, 0x0,
    0x0,

    /* U+0047 "G" */
    0x4, 0xdf, 0xff, 0xff, 0xe0, 0xf, 0xf6, 0x55,
    0x55, 0x40, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xf,
    0xb0, 0x0, 0x0, 0x0, 0xf, 0xb0, 0x0, 0x3,
    0xf8, 0xf, 0xb0, 0x0, 0x3, 0xf8, 0xf, 0xb0,
    0x0, 0x3, 0xf8, 0xf, 0xf6, 0x55, 0x5b, 0xf5,
    0x4, 0xcf, 0xff, 0xfe, 0x90,

    /* U+0048 "H" */
    0xf, 0xb0, 0x0, 0x0, 0xfb, 0xf, 0xb0, 0x0,
    0x0, 0xfb, 0xf, 0xb0, 0x0, 0x0, 0xfb, 0xf,
    0xb1, 0x11, 0x11, 0xfb, 0xf, 0xff, 0xff, 0xff,
    0xfb, 0xf, 0xc4, 0x44, 0x44, 0xfb, 0xf, 0xb0,
    0x0, 0x0, 0xfb, 0xf, 0xb0, 0x0, 0x0, 0xfb,
    0xf, 0xb0, 0x0, 0x0, 0xfb,

    /* U+0049 "I" */
    0xf, 0xb0, 0xfb, 0xf, 0xb0, 0xfb, 0xf, 0xb0,
    0xfb, 0xf, 0xb0, 0xfb, 0xf, 0xb0,

    /* U+004A "J" */
    0x0, 0x9f, 0x20, 0x9, 0xf2, 0x0, 0x9f, 0x20,
    0x9, 0xf2, 0x0, 0x9f, 0x20, 0x9, 0xf2, 0x0,
    0x9f, 0x24, 0x6e, 0xf1, 0xdf, 0xd5, 0x0,

    /* U+004B "K" */
    0xf, 0xb0, 0x0, 0x6f, 0xa0, 0xf, 0xb0, 0x6,
    0xfa, 0x0, 0xf, 0xb0, 0x7f, 0xa0, 0x0, 0xf,
    0xb8, 0xf9, 0x0, 0x0, 0xf, 0xdf, 0xd0, 0x0,
    0x0, 0xf, 0xb6, 0xfb, 0x0, 0x0, 0xf, 0xb0,
    0x6f, 0xb0, 0x0, 0xf, 0xb0, 0x5, 0xfb, 0x0,
    0xf, 0xb0, 0x0, 0x4f, 0xc0,

    /* U+004C "L" */
    0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb, 0x0, 0x0,
    0x0, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb, 0x0,
    0x0, 0x0, 0xf, 0xb0, 0x0, 0x0, 0x0, 0xfb,
    0x0, 0x0, 0x0, 0xf, 0xb0, 0x0, 0x0, 0x0,
    0xef, 0x75, 0x55, 0x54, 0x4, 0xcf, 0xff, 0xff,
    0xc0,

    /* U+004D "M" */
    0xb, 0xf8, 0x0, 0x0, 0x0, 0x9f, 0x90, 0xff,
    0xf3, 0x0, 0x0, 0x4f, 0xff, 0xf, 0xbf, 0xb0,
    0x0, 0xc, 0xfc, 0xf0, 0xfa, 0x9f, 0x20, 0x4,
    0xf8, 0xbf, 0xf, 0xa1, 0xfa, 0x0, 0xcf, 0x1b,
    0xf0, 0xfa, 0x9, 0xf2, 0x3f, 0x80, 0xbf, 0xf,
    0xa0, 0x1f, 0x9b, 0xf1, 0xb, 0xf0, 0xfa, 0x0,
    0x8f, 0xf8, 0x0, 0xbf, 0xf, 0xa0, 0x1, 0xdc,
    0x0, 0xb, 0xf0,

    /* U+004E "N" */
    0xb, 0xf8, 0x0, 0x1, 0xf9, 0xf, 0xff, 0x30,
    0x1, 0xf9, 0xf, 0xad, 0xd0, 0x1, 0xf9, 0xf,
    0xa3, 0xf8, 0x1, 0xf9, 0xf, 0xa0, 0x9f, 0x31,
    0xf9, 0xf, 0xa0, 0xe, 0xc1, 0xf9, 0xf, 0xa0,
    0x4, 0xf8, 0xf9, 0xf, 0xa0, 0x0, 0xaf, 0xf9,
    0xf, 0xa0, 0x0, 0x1d, 0xe4,

    /* U+004F "O" */
    0x3, 0xcf, 0xff, 0xfe, 0x80, 0xe, 0xf7, 0x55,
    0x6c, 0xf4, 0xf, 0xb0, 0x0, 0x6, 0xf5, 0xf,
    0xb0, 0x0, 0x5, 0xf6, 0xf, 0xb0, 0x0, 0x5,
    0xf6, 0xf, 0xb0, 0x0, 0x5, 0xf6, 0xf, 0xb0,
    0x0, 0x5, 0xf5, 0xe, 0xf7, 0x55, 0x6c, 0xf4,
    0x4, 0xdf, 0xff, 0xfe, 0x80,

    /* U+0050 "P" */
    0xf, 0xff, 0xff, 0xff, 0xa1, 0xf, 0xc5, 0x55,
    0x5a, 0xf7, 0xf, 0xb0, 0x0, 0x2, 0xf8, 0xf,
    0xb1, 0x11, 0x17, 0xf8, 0xf, 0xff, 0xff, 0xff,
    0xe2, 0xf, 0xc4, 0x44, 0x43, 0x0, 0xf, 0xb0,
    0x0, 0x0, 0x0, 0xf, 0xb0, 0x0, 0x0, 0x0,
    0xf, 0xb0, 0x0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x4, 0xdf, 0xff, 0xfe, 0x90, 0xe, 0xf7, 0x55,
    0x6c, 0xf5, 0xf, 0xb0, 0x0, 0x4, 0xf7, 0xf,
    0xb0, 0x0, 0x4, 0xf7, 0xf, 0xb0, 0x0, 0x4,
    0xf7, 0xf, 0xb0, 0x0, 0x4, 0xf7, 0xf, 0xb0,
    0x0, 0x4, 0xf7, 0xe, 0xf6, 0x55, 0x5b, 0xf5,
    0x5, 0xdf, 0xff, 0xff, 0x90, 0x0, 0x0, 0x3,
    0xef, 0x50, 0x0, 0x0, 0x0, 0x27, 0x71,

    /* U+0052 "R" */
    0xf, 0xff, 0xff, 0xfe, 0xa0, 0xf, 0xc5, 0x55,
    0x6b, 0xf6, 0xf, 0xb0, 0x0, 0x4, 0xf8, 0xf,
    0xb0, 0x0, 0x6, 0xf7, 0xf, 0xce, 0xff, 0xff,
    0xc1, 0xf, 0xbb, 0xf8, 0x21, 0x0, 0xf, 0xb0,
    0x9f, 0x80, 0x0, 0xf, 0xb0, 0x7, 0xfa, 0x0,
    0xf, 0xb0, 0x0, 0x4f, 0xc1,

    /* U+0053 "S" */
    0x7, 0xef, 0xff, 0xff, 0x73, 0xfd, 0x65, 0x55,
    0x52, 0x5f, 0x70, 0x0, 0x0, 0x4, 0xfb, 0x21,
    0x10, 0x0, 0xb, 0xff, 0xff, 0xfa, 0x0, 0x2,
    0x44, 0x4b, 0xf5, 0x0, 0x0, 0x0, 0x5f, 0x61,
    0x55, 0x55, 0x6c, 0xf5, 0x5f, 0xff, 0xff, 0xe9,
    0x0,

    /* U+0054 "T" */
    0xef, 0xff, 0xff, 0xfd, 0x55, 0x5f, 0xe5, 0x54,
    0x0, 0xe, 0xd0, 0x0, 0x0, 0xe, 0xd0, 0x0,
    0x0, 0xe, 0xd0, 0x0, 0x0, 0xe, 0xd0, 0x0,
    0x0, 0xe, 0xd0, 0x0, 0x0, 0xe, 0xd0, 0x0,
    0x0, 0xe, 0xd0, 0x0,

    /* U+0055 "U" */
    0xf, 0xb0, 0x0, 0x2, 0xf9, 0xf, 0xb0, 0x0,
    0x2, 0xf9, 0xf, 0xb0, 0x0, 0x2, 0xf9, 0xf,
    0xb0, 0x0, 0x2, 0xf9, 0xf, 0xb0, 0x0, 0x2,
    0xf9, 0xf, 0xb0, 0x0, 0x2, 0xf9, 0xf, 0xb0,
    0x0, 0x2, 0xf9, 0xf, 0xf7, 0x55, 0x6b, 0xf7,
    0x4, 0xcf, 0xff, 0xff, 0x90,

    /* U+0056 "V" */
    0xe, 0xe0, 0x0, 0x0, 0xc, 0xf1, 0x6, 0xf6,
    0x0, 0x0, 0x3f, 0x90, 0x0, 0xed, 0x0, 0x0,
    0xbf, 0x10, 0x0, 0x7f, 0x50, 0x3, 0xf9, 0x0,
    0x0, 0xe, 0xc0, 0xa, 0xf1, 0x0, 0x0, 0x7,
    0xf4, 0x2f, 0x90, 0x0, 0x0, 0x0, 0xeb, 0x9f,
    0x20, 0x0, 0x0, 0x0, 0x8f, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0xc, 0xd2, 0x0, 0x0,

    /* U+0057 "W" */
    0xaf, 0x10, 0x1, 0xdd, 0x20, 0x0, 0xfb, 0x5f,
    0x50, 0x7, 0xff, 0x80, 0x4, 0xf7, 0x1f, 0xa0,
    0xb, 0xdc, 0xc0, 0x9, 0xf2, 0xc, 0xf0, 0xf,
    0x98, 0xf1, 0xd, 0xd0, 0x7, 0xf4, 0x4f, 0x43,
    0xf5, 0x2f, 0x80, 0x2, 0xf9, 0x8f, 0x0, 0xfa,
    0x7f, 0x30, 0x0, 0xdd, 0xdc, 0x0, 0xae, 0xce,
    0x0, 0x0, 0x8f, 0xf7, 0x0, 0x6f, 0xfa, 0x0,
    0x0, 0x2d, 0xd1, 0x0, 0x1d, 0xe3, 0x0,

    /* U+0058 "X" */
    0x6f, 0xa0, 0x0, 0xb, 0xf5, 0x8, 0xf8, 0x0,
    0x9f, 0x70, 0x0, 0xaf, 0x57, 0xf9, 0x0, 0x0,
    0xc, 0xff, 0xb0, 0x0, 0x0, 0x3, 0xff, 0x20,
    0x0, 0x0, 0x1d, 0xef, 0xc0, 0x0, 0x0, 0xcf,
    0x35, 0xfb, 0x0, 0xa, 0xf5, 0x0, 0x7f, 0x90,
    0x9f, 0x70, 0x0, 0x9, 0xf7,

    /* U+0059 "Y" */
    0xc, 0xf3, 0x0, 0x0, 0xbf, 0x40, 0x1e, 0xd0,
    0x0, 0x7f, 0x80, 0x0, 0x4f, 0xa0, 0x4f, 0xb0,
    0x0, 0x0, 0x8f, 0x7e, 0xe1, 0x0, 0x0, 0x0,
    0xcf, 0xf3, 0x0, 0x0, 0x0, 0x2, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x2f, 0x90, 0x0, 0x0, 0x0,
    0x2, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x2f, 0x90,
    0x0, 0x0,

    /* U+005A "Z" */
    0x5f, 0xff, 0xff, 0xff, 0x61, 0x55, 0x55, 0x6e,
    0xf4, 0x0, 0x0, 0xa, 0xf5, 0x0, 0x0, 0x9,
    0xf7, 0x0, 0x0, 0x8, 0xf8, 0x0, 0x0, 0x6,
    0xf9, 0x0, 0x0, 0x5, 0xfa, 0x0, 0x0, 0x3,
    0xfe, 0x65, 0x55, 0x52, 0x5f, 0xff, 0xff, 0xff,
    0x60,

    /* U+005B "[" */
    0x9e, 0xda, 0xe1, 0xae, 0xa, 0xe0, 0xae, 0xa,
    0xe0, 0xae, 0xa, 0xe0, 0xae, 0xa, 0xe0, 0xae,
    0xa, 0xe0, 0xaf, 0xd1, 0x11,

    /* U+005C "\\" */
    0x9b, 0x0, 0x0, 0x0, 0x1e, 0x50, 0x0, 0x0,
    0x5, 0xe1, 0x0, 0x0, 0x0, 0xc9, 0x0, 0x0,
    0x0, 0x2f, 0x30, 0x0, 0x0, 0x8, 0xd0, 0x0,
    0x0, 0x0, 0xd7, 0x0, 0x0, 0x0, 0x4f, 0x10,
    0x0, 0x0, 0xa, 0xb0,

    /* U+005D "]" */
    0x2e, 0xe6, 0x3, 0xf6, 0x2, 0xf6, 0x2, 0xf6,
    0x2, 0xf6, 0x2, 0xf6, 0x2, 0xf6, 0x2, 0xf6,
    0x2, 0xf6, 0x2, 0xf6, 0x2, 0xf6, 0x2, 0xf6,
    0x2f, 0xf6, 0x1, 0x10,

    /* U+005E "^" */
    0x0, 0x67, 0x0, 0x6, 0xb8, 0x90, 0x3c, 0x0,
    0xb6,

    /* U+005F "_" */
    0xef, 0xff, 0xff, 0xff, 0xf0, 0x12, 0x22, 0x22,
    0x22, 0x20,

    /* U+0060 "`" */
    0xb, 0x10, 0x78,

    /* U+0061 "a" */
    0xf, 0xff, 0xff, 0xfa, 0x0, 0x33, 0x33, 0x36,
    0xf6, 0x5, 0xdf, 0xff, 0xff, 0x70, 0xfc, 0x22,
    0x24, 0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xfc,
    0x43, 0x37, 0xf6, 0x5, 0xef, 0xff, 0xfb, 0x0,

    /* U+0062 "b" */
    0xf, 0x80, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0,
    0x0, 0xf, 0xff, 0xff, 0xfa, 0x0, 0xf9, 0x33,
    0x36, 0xf7, 0xf, 0x80, 0x0, 0xf, 0x80, 0xf8,
    0x0, 0x0, 0xf8, 0xf, 0x80, 0x0, 0xf, 0x80,
    0xfc, 0x33, 0x36, 0xf7, 0x5, 0xdf, 0xff, 0xfb,
    0x10,

    /* U+0063 "c" */
    0x7, 0xef, 0xff, 0xf0, 0xfb, 0x33, 0x33, 0xf,
    0x80, 0x0, 0x0, 0xf8, 0x0, 0x0, 0xf, 0x80,
    0x0, 0x0, 0xfc, 0x33, 0x33, 0x6, 0xef, 0xff,
    0xf0,

    /* U+0064 "d" */
    0x0, 0x0, 0x0, 0xf, 0x80, 0x0, 0x0, 0x0,
    0xf8, 0x5, 0xef, 0xff, 0xff, 0x80, 0xfc, 0x43,
    0x34, 0xf8, 0xf, 0x80, 0x0, 0xf, 0x80, 0xf8,
    0x0, 0x0, 0xf8, 0xf, 0x80, 0x0, 0xf, 0x80,
    0xfc, 0x43, 0x37, 0xf7, 0x6, 0xef, 0xff, 0xfa,
    0x0,

    /* U+0065 "e" */
    0x6, 0xef, 0xff, 0xfb, 0x0, 0xfc, 0x33, 0x37,
    0xf5, 0xf, 0x80, 0x27, 0xcf, 0x50, 0xfc, 0xdf,
    0xa5, 0x10, 0xf, 0xc4, 0x0, 0x0, 0x0, 0xfc,
    0x33, 0x33, 0x31, 0x5, 0xdf, 0xff, 0xff, 0x60,

    /* U+0066 "f" */
    0x6, 0xdf, 0x70, 0xfb, 0x20, 0xf, 0xff, 0x70,
    0xf9, 0x31, 0xf, 0x80, 0x0, 0xf8, 0x0, 0xf,
    0x80, 0x0, 0xf8, 0x0, 0xf, 0x80, 0x0,

    /* U+0067 "g" */
    0x6, 0xef, 0xff, 0xfb, 0x0, 0xfc, 0x43, 0x37,
    0xf6, 0xf, 0x80, 0x0, 0xf, 0x70, 0xf8, 0x0,
    0x0, 0xf7, 0xf, 0x80, 0x0, 0xf, 0x70, 0xfc,
    0x43, 0x34, 0xf7, 0x5, 0xdf, 0xff, 0xff, 0x70,
    0x0, 0x0, 0x1, 0xf7, 0x4, 0x44, 0x44, 0x9f,
    0x60, 0xff, 0xff, 0xfe, 0xa0,

    /* U+0068 "h" */
    0xf, 0x80, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0,
    0x0, 0xf, 0xff, 0xff, 0xe9, 0x0, 0xfc, 0x77,
    0x7c, 0xf4, 0xf, 0x80, 0x0, 0x2f, 0x60, 0xf8,
    0x0, 0x1, 0xf6, 0xf, 0x80, 0x0, 0x1f, 0x60,
    0xf8, 0x0, 0x1, 0xf6, 0xf, 0x80, 0x0, 0x1f,
    0x60,

    /* U+0069 "i" */
    0x3f, 0x40, 0x30, 0x4f, 0x44, 0xf4, 0x4f, 0x44,
    0xf4, 0x4f, 0x44, 0xf4, 0x4f, 0x40,

    /* U+006A "j" */
    0x0, 0xf, 0x80, 0x0, 0x31, 0x0, 0xf, 0x80,
    0x0, 0xf8, 0x0, 0xf, 0x80, 0x0, 0xf8, 0x0,
    0xf, 0x80, 0x0, 0xf8, 0x0, 0xf, 0x80, 0x0,
    0xf8, 0x3, 0x8f, 0x60, 0xff, 0xa0,

    /* U+006B "k" */
    0xf, 0x80, 0x0, 0x0, 0x0, 0xf8, 0x0, 0x0,
    0x0, 0xf, 0x80, 0x8, 0xf5, 0x0, 0xf8, 0x9,
    0xf4, 0x0, 0xf, 0x8a, 0xf4, 0x0, 0x0, 0xfc,
    0xf8, 0x0, 0x0, 0xf, 0x87, 0xf6, 0x0, 0x0,
    0xf8, 0x7, 0xf7, 0x0, 0xf, 0x80, 0x6, 0xf8,
    0x0,

    /* U+006C "l" */
    0xf, 0x80, 0xf8, 0xf, 0x80, 0xf8, 0xf, 0x80,
    0xf8, 0xf, 0x80, 0xf8, 0xf, 0x80,

    /* U+006D "m" */
    0x5, 0xef, 0xfd, 0x5d, 0xff, 0xd2, 0xe, 0xe8,
    0x8d, 0xfc, 0x78, 0xfb, 0xf, 0x80, 0x6, 0xf3,
    0x0, 0xbe, 0xf, 0x70, 0x5, 0xf3, 0x0, 0xae,
    0xf, 0x70, 0x5, 0xf3, 0x0, 0xae, 0xf, 0x70,
    0x5, 0xf3, 0x0, 0xae, 0xf, 0x70, 0x5, 0xf3,
    0x0, 0xae,

    /* U+006E "n" */
    0xa, 0xff, 0xff, 0xd4, 0x5f, 0xc7, 0x78, 0xfd,
    0x6f, 0x20, 0x0, 0x9f, 0x6f, 0x20, 0x0, 0x8f,
    0x6f, 0x20, 0x0, 0x8f, 0x6f, 0x20, 0x0, 0x8f,
    0x6f, 0x20, 0x0, 0x8f,

    /* U+006F "o" */
    0x8, 0xef, 0xff, 0xf9, 0x2, 0xfa, 0x33, 0x39,
    0xf3, 0x4f, 0x40, 0x0, 0x4f, 0x44, 0xf4, 0x0,
    0x4, 0xf4, 0x4f, 0x40, 0x0, 0x4f, 0x43, 0xfa,
    0x33, 0x3a, 0xf3, 0x8, 0xef, 0xff, 0xf9, 0x0,

    /* U+0070 "p" */
    0x6, 0xef, 0xff, 0xfa, 0x0, 0xfc, 0x33, 0x37,
    0xf5, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0,
    0x1, 0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xf9,
    0x33, 0x37, 0xf5, 0xf, 0xff, 0xff, 0xfa, 0x0,
    0xf8, 0x0, 0x0, 0x0, 0xf, 0x80, 0x0, 0x0,
    0x0, 0xf8, 0x0, 0x0, 0x0,

    /* U+0071 "q" */
    0x6, 0xef, 0xff, 0xfb, 0x0, 0xfc, 0x33, 0x37,
    0xf5, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0,
    0x1, 0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xfc,
    0x32, 0x24, 0xf7, 0x6, 0xef, 0xff, 0xff, 0x70,
    0x0, 0x0, 0x1, 0xf7, 0x0, 0x0, 0x0, 0x1f,
    0x70, 0x0, 0x0, 0x1, 0xf7,

    /* U+0072 "r" */
    0xa, 0xff, 0xd6, 0xf8, 0x32, 0x7f, 0x20, 0x7,
    0xf2, 0x0, 0x7f, 0x20, 0x7, 0xf2, 0x0, 0x7f,
    0x20, 0x0,

    /* U+0073 "s" */
    0x9, 0xff, 0xff, 0xf8, 0x4f, 0x83, 0x33, 0x31,
    0x4f, 0x60, 0x0, 0x0, 0xc, 0xff, 0xff, 0xc1,
    0x0, 0x23, 0x36, 0xf7, 0x13, 0x33, 0x36, 0xf7,
    0x5f, 0xff, 0xff, 0xc1,

    /* U+0074 "t" */
    0xf, 0x80, 0x0, 0xf8, 0x0, 0xf, 0xff, 0x70,
    0xf9, 0x21, 0xf, 0x80, 0x0, 0xf8, 0x0, 0xf,
    0x80, 0x0, 0xf8, 0x0, 0xf, 0x80, 0x0,

    /* U+0075 "u" */
    0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0, 0x1,
    0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0,
    0x1, 0xf7, 0xf, 0x80, 0x0, 0x2f, 0x70, 0xef,
    0x88, 0x8c, 0xf5, 0x5, 0xdf, 0xff, 0xfa, 0x0,

    /* U+0076 "v" */
    0xd, 0xc0, 0x0, 0x0, 0xea, 0x4, 0xf4, 0x0,
    0x7, 0xf2, 0x0, 0xcd, 0x0, 0x1e, 0x90, 0x0,
    0x3f, 0x60, 0x8f, 0x10, 0x0, 0xa, 0xe2, 0xf8,
    0x0, 0x0, 0x2, 0xfe, 0xe0, 0x0, 0x0, 0x0,
    0x7f, 0x50, 0x0,

    /* U+0077 "w" */
    0x9e, 0x0, 0xc, 0xc0, 0x0, 0xda, 0x4f, 0x30,
    0x4f, 0xf5, 0x2, 0xf5, 0xf, 0x80, 0x9c, 0xba,
    0x7, 0xf0, 0xa, 0xd0, 0xe7, 0x6f, 0xd, 0xb0,
    0x5, 0xf6, 0xf2, 0x1f, 0x6f, 0x60, 0x0, 0xff,
    0xd0, 0xc, 0xff, 0x10, 0x0, 0x7e, 0x60, 0x5,
    0xe8, 0x0,

    /* U+0078 "x" */
    0x4f, 0x80, 0x5, 0xf8, 0x0, 0x6f, 0x64, 0xfa,
    0x0, 0x0, 0x8f, 0xfb, 0x0, 0x0, 0x0, 0xef,
    0x30, 0x0, 0x0, 0xbf, 0xdd, 0x10, 0x0, 0x9f,
    0x42, 0xec, 0x0, 0x7f, 0x50, 0x3, 0xfb, 0x0,

    /* U+0079 "y" */
    0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0, 0x1,
    0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xf8, 0x0,
    0x1, 0xf7, 0xf, 0x80, 0x0, 0x1f, 0x70, 0xdf,
    0x88, 0x89, 0xf7, 0x3, 0xdf, 0xff, 0xef, 0x70,
    0x0, 0x0, 0x2, 0xf6, 0x6, 0x88, 0x88, 0xcf,
    0x40, 0xbf, 0xff, 0xff, 0x80,

    /* U+007A "z" */
    0x6f, 0xff, 0xff, 0xfe, 0x21, 0x33, 0x33, 0x7f,
    0xd1, 0x0, 0x0, 0x7f, 0xa0, 0x0, 0x0, 0xaf,
    0x70, 0x0, 0x2, 0xde, 0x40, 0x0, 0x3, 0xee,
    0x53, 0x33, 0x30, 0x5e, 0xff, 0xff, 0xff, 0x10,

    /* U+007B "{" */
    0x1, 0xbe, 0x90, 0x8f, 0x51, 0x9, 0xe0, 0x0,
    0xae, 0x0, 0xa, 0xe0, 0x0, 0xdd, 0x0, 0xaf,
    0x30, 0x1, 0xdb, 0x0, 0xa, 0xe0, 0x0, 0xae,
    0x0, 0xa, 0xe0, 0x0, 0x8f, 0x20, 0x2, 0xef,
    0xa0, 0x0, 0x11,

    /* U+007C "|" */
    0x2, 0x4, 0xf4, 0x4f, 0x44, 0xf4, 0x4f, 0x44,
    0xf4, 0x4f, 0x44, 0xf4, 0x4f, 0x44, 0xf4, 0x4f,
    0x44, 0xf4,

    /* U+007D "}" */
    0x9e, 0xb1, 0x1, 0x5f, 0x80, 0x0, 0xea, 0x0,
    0xe, 0xa0, 0x0, 0xea, 0x0, 0xc, 0xd0, 0x0,
    0x3f, 0x90, 0xb, 0xe2, 0x0, 0xea, 0x0, 0xe,
    0xa0, 0x0, 0xea, 0x0, 0x2f, 0x80, 0xaf, 0xd2,
    0x1, 0x10, 0x0,

    /* U+007E "~" */
    0x2, 0xbf, 0xea, 0x61, 0x5, 0xc0, 0xd, 0x93,
    0x59, 0xef, 0xfd, 0x40, 0x1, 0x0, 0x0, 0x1,
    0x10, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 85, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 71, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 81, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 19, .adv_w = 185, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 123, .adv_w = 256, .box_w = 16, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 173, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 51, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 248, .adv_w = 79, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 274, .adv_w = 78, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 300, .adv_w = 113, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 321, .adv_w = 144, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 348, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 353, .adv_w = 77, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 356, .adv_w = 48, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 168, .box_w = 5, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 168, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 50, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 813, .adv_w = 48, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 144, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 856, .adv_w = 144, .box_w = 9, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 874, .adv_w = 144, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 910, .adv_w = 147, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 211, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1010, .adv_w = 168, .box_w = 12, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1064, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 157, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1150, .adv_w = 170, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1195, .adv_w = 161, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1236, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 168, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1322, .adv_w = 170, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1367, .adv_w = 58, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1381, .adv_w = 82, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1404, .adv_w = 148, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1449, .adv_w = 142, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1490, .adv_w = 223, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1549, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1594, .adv_w = 166, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1639, .adv_w = 167, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1684, .adv_w = 167, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1739, .adv_w = 164, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1784, .adv_w = 153, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1825, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1861, .adv_w = 169, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1906, .adv_w = 162, .box_w = 12, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1960, .adv_w = 225, .box_w = 14, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2023, .adv_w = 159, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2068, .adv_w = 151, .box_w = 11, .box_h = 9, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 2118, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2159, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2180, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2216, .adv_w = 77, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2244, .adv_w = 103, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 2253, .adv_w = 144, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2263, .adv_w = 89, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 2266, .adv_w = 151, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2298, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2339, .adv_w = 121, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2364, .adv_w = 152, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2405, .adv_w = 146, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2437, .adv_w = 87, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2460, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2505, .adv_w = 150, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2546, .adv_w = 56, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2560, .adv_w = 55, .box_w = 5, .box_h = 12, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 2590, .adv_w = 131, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2631, .adv_w = 55, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2645, .adv_w = 206, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2687, .adv_w = 142, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2715, .adv_w = 149, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2747, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2792, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2837, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2855, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2883, .adv_w = 85, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2906, .adv_w = 151, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2938, .adv_w = 142, .box_w = 10, .box_h = 7, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 2973, .adv_w = 193, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3015, .adv_w = 131, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3047, .adv_w = 150, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3092, .adv_w = 141, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3124, .adv_w = 80, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3159, .adv_w = 144, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 3177, .adv_w = 80, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3212, .adv_w = 192, .box_w = 12, .box_h = 3, .ofs_x = 0, .ofs_y = 2}
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


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    14, 53,
    14, 55,
    14, 56,
    14, 57,
    14, 58,
    34, 14,
    34, 53,
    34, 55,
    34, 56,
    34, 58,
    34, 85,
    34, 87,
    34, 88,
    34, 90,
    36, 14,
    37, 13,
    37, 15,
    39, 13,
    39, 15,
    39, 34,
    39, 66,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 87,
    45, 88,
    45, 90,
    48, 13,
    49, 13,
    49, 14,
    49, 15,
    49, 34,
    49, 66,
    49, 68,
    49, 69,
    49, 70,
    49, 72,
    49, 80,
    51, 14,
    51, 68,
    51, 69,
    51, 70,
    51, 80,
    51, 82,
    53, 13,
    53, 14,
    53, 15,
    53, 34,
    53, 66,
    53, 68,
    53, 69,
    53, 70,
    53, 72,
    53, 78,
    53, 79,
    53, 80,
    53, 81,
    53, 82,
    53, 83,
    53, 84,
    53, 86,
    53, 87,
    53, 88,
    53, 89,
    53, 90,
    53, 91,
    55, 14,
    55, 15,
    55, 34,
    55, 66,
    55, 68,
    55, 69,
    55, 70,
    55, 72,
    55, 78,
    55, 79,
    55, 80,
    55, 81,
    55, 82,
    55, 83,
    55, 84,
    55, 86,
    56, 14,
    56, 15,
    56, 34,
    56, 66,
    56, 68,
    56, 69,
    56, 70,
    56, 80,
    56, 82,
    57, 14,
    57, 70,
    57, 80,
    57, 82,
    57, 90,
    58, 14,
    58, 34,
    58, 66,
    58, 68,
    58, 69,
    58, 70,
    58, 72,
    58, 78,
    58, 79,
    58, 80,
    58, 81,
    58, 82,
    58, 83,
    58, 84,
    58, 86,
    71, 13,
    71, 14,
    71, 15,
    76, 14,
    83, 13,
    83, 14,
    83, 15,
    85, 13,
    85, 14,
    85, 15,
    87, 13,
    87, 15,
    88, 13,
    88, 15,
    89, 14,
    90, 13,
    90, 15
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -29, -14, -9, -6, -17, -6, -14, -12,
    -6, -14, -6, -9, -6, -9, -6, -9,
    -9, -14, -14, -9, -6, -17, -17, -14,
    -17, -6, -6, -6, -9, -29, -6, -29,
    -9, -6, -6, -6, -6, -3, -6, -12,
    -6, -6, -6, -6, -6, -26, -29, -26,
    -14, -23, -23, -23, -23, -23, -17, -17,
    -23, -17, -23, -17, -23, -17, -23, -23,
    -17, -20, -17, -14, -23, -12, -12, -12,
    -12, -12, -12, -6, -6, -12, -6, -12,
    -6, -9, -6, -6, -14, -3, -6, -6,
    -6, -6, -6, -6, -6, -6, -6, -6,
    -9, -17, -14, -17, -12, -12, -12, -12,
    -6, -6, -12, -6, -12, -6, -9, -6,
    -12, -12, -12, -12, -17, -9, -17, 6,
    -9, 6, -14, -14, -9, -9, -12, -14,
    -14
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 129,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
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
const lv_font_t sony_18 = {
#else
lv_font_t sony_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if SONY_18*/

