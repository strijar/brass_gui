/*******************************************************************************
 * Size: 14 px
 * Bpp: 4
 * Opts: --font jura_bold.ttf -r 0x20-0x7F --format lvgl --no-compress --bpp 4 --size 14 -o jura_bold_14.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef JURA_BOLD_14
#define JURA_BOLD_14 1
#endif

#if JURA_BOLD_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x96, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0xb7, 0x96,
    0x43, 0xb8,

    /* U+0022 "\"" */
    0xb1, 0x85, 0xd2, 0x96, 0xd2, 0x96, 0x81, 0x63,

    /* U+0023 "#" */
    0x0, 0x5, 0x90, 0xc1, 0x0, 0x0, 0xc4, 0x3c,
    0x0, 0x6, 0xff, 0xff, 0xff, 0x30, 0x5, 0xa0,
    0xd3, 0x0, 0x0, 0x96, 0x1e, 0x0, 0x3, 0xff,
    0xff, 0xff, 0x60, 0x2, 0xd0, 0xa6, 0x0, 0x0,
    0x69, 0xe, 0x10, 0x0, 0x9, 0x41, 0xc0, 0x0,
    0x0,

    /* U+0024 "$" */
    0x0, 0x4, 0x10, 0x0, 0x0, 0xb, 0x40, 0x0,
    0x9, 0xef, 0xfd, 0x40, 0x5e, 0x3c, 0x67, 0xe0,
    0x8a, 0xb, 0x40, 0xf1, 0x6c, 0xb, 0x40, 0x20,
    0x1d, 0xff, 0xfd, 0x60, 0x0, 0x1d, 0x55, 0xf1,
    0xc3, 0xc, 0x30, 0xe3, 0xba, 0x2d, 0x55, 0xf1,
    0x2c, 0xff, 0xfe, 0x60, 0x0, 0xb, 0x20, 0x0,

    /* U+0025 "%" */
    0x9, 0xff, 0x90, 0x0, 0x5c, 0x0, 0x1f, 0x22,
    0xf1, 0x3, 0xf5, 0x0, 0x1f, 0x0, 0xf1, 0x1e,
    0x70, 0x0, 0xb, 0xff, 0xb0, 0xca, 0x0, 0x0,
    0x0, 0x11, 0x9, 0xd4, 0xde, 0xa0, 0x0, 0x0,
    0x7e, 0x2c, 0x72, 0xd4, 0x0, 0x4, 0xf4, 0xd,
    0x40, 0xb6, 0x0, 0x2e, 0x60, 0xc, 0x61, 0xd5,
    0x0, 0x89, 0x0, 0x4, 0xef, 0xb0,

    /* U+0026 "&" */
    0x0, 0x7e, 0xfd, 0x20, 0x0, 0x1f, 0x52, 0x9a,
    0x0, 0x2, 0xf1, 0x0, 0x10, 0x0, 0x2f, 0xb0,
    0x0, 0x0, 0xd, 0x9b, 0xc1, 0x0, 0x1, 0xf0,
    0x9, 0xeb, 0x70, 0x1f, 0x10, 0x7, 0xf8, 0x0,
    0xd9, 0x32, 0x6f, 0xf5, 0x2, 0xbf, 0xfd, 0x65,
    0xa0,

    /* U+0027 "'" */
    0xb1, 0xd2, 0xd2, 0x81,

    /* U+0028 "(" */
    0x2, 0xcd, 0x0, 0xc5, 0x0, 0xe, 0x0, 0x1,
    0xe0, 0x0, 0x1e, 0x0, 0x1, 0xe0, 0x0, 0x1e,
    0x0, 0x1, 0xe0, 0x0, 0x1e, 0x0, 0x0, 0xe0,
    0x0, 0xc, 0x50, 0x0, 0x2c, 0xd0,

    /* U+0029 ")" */
    0xad, 0x40, 0x2, 0xe0, 0x0, 0xc3, 0x0, 0xb4,
    0x0, 0xb4, 0x0, 0xb4, 0x0, 0xb4, 0x0, 0xb4,
    0x0, 0xb4, 0x0, 0xc3, 0x3, 0xe0, 0xbd, 0x40,

    /* U+002A "*" */
    0x8, 0x30, 0xce, 0xd7, 0xaf, 0xf4, 0x5b, 0x73,

    /* U+002B "+" */
    0x0, 0x0, 0x0, 0x0, 0x1, 0xd0, 0x0, 0x0,
    0x1e, 0x0, 0x0, 0x1, 0xe0, 0x0, 0xaf, 0xff,
    0xff, 0x30, 0x1, 0xe0, 0x0, 0x0, 0x1d, 0x0,
    0x0,

    /* U+002C "," */
    0x2, 0x0, 0xf6, 0x3f, 0x25, 0xa0,

    /* U+002D "-" */
    0xaf, 0xff, 0xd0,

    /* U+002E "." */
    0x43, 0xb8,

    /* U+002F "/" */
    0x0, 0x8, 0x70, 0x0, 0xd5, 0x0, 0x2f, 0x10,
    0x6, 0xc0, 0x0, 0xa8, 0x0, 0xe, 0x40, 0x3,
    0xf0, 0x0, 0x7c, 0x0, 0xb, 0x70, 0x0, 0xf3,
    0x0, 0x4f, 0x0, 0x6, 0xa0, 0x0,

    /* U+0030 "0" */
    0x3, 0xcf, 0xfe, 0x90, 0xe, 0x82, 0x23, 0xd8,
    0x3f, 0x0, 0x0, 0x6c, 0x4e, 0x0, 0x10, 0x5d,
    0x4e, 0x7, 0xd0, 0x5d, 0x4e, 0x1, 0x30, 0x5d,
    0x3f, 0x0, 0x0, 0x6c, 0xe, 0x82, 0x23, 0xd8,
    0x3, 0xcf, 0xfe, 0x90,

    /* U+0031 "1" */
    0x0, 0x8e, 0x9, 0xff, 0x3b, 0x4f, 0x0, 0x3f,
    0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f, 0x0, 0x3f,
    0x0, 0x2d,

    /* U+0032 "2" */
    0x4, 0xdf, 0xff, 0xa0, 0xe, 0x82, 0x23, 0xd7,
    0x5, 0x0, 0x0, 0x99, 0x0, 0x0, 0x3, 0xe5,
    0x0, 0x1, 0x9f, 0x60, 0x0, 0x6f, 0x91, 0x0,
    0x5, 0xe3, 0x0, 0x0, 0xc, 0x92, 0x22, 0x20,
    0xc, 0xff, 0xff, 0xf6,

    /* U+0033 "3" */
    0x3, 0xcf, 0xfe, 0xa0, 0xc, 0x92, 0x23, 0xd6,
    0x6, 0x10, 0x0, 0x98, 0x0, 0x0, 0x0, 0xc6,
    0x0, 0x7, 0xff, 0xf2, 0x0, 0x0, 0x23, 0xba,
    0x5, 0x0, 0x0, 0x6c, 0x1f, 0x52, 0x23, 0xba,
    0x6, 0xdf, 0xff, 0xb1,

    /* U+0034 "4" */
    0x0, 0x0, 0x1d, 0x90, 0x0, 0x0, 0xb, 0xea,
    0x0, 0x0, 0x7, 0xb8, 0xa0, 0x0, 0x4, 0xe1,
    0x8a, 0x0, 0x1, 0xe3, 0x8, 0xa0, 0x0, 0xc6,
    0x0, 0x8a, 0x0, 0x5f, 0xff, 0xff, 0xfe, 0x0,
    0x22, 0x22, 0x9b, 0x10, 0x0, 0x0, 0x7, 0x80,
    0x0,

    /* U+0035 "5" */
    0xd, 0xff, 0xff, 0xf9, 0xf, 0x52, 0x22, 0x20,
    0xf, 0x30, 0x0, 0x0, 0xe, 0xdf, 0xfe, 0xa1,
    0x6, 0x63, 0x23, 0xc8, 0x0, 0x0, 0x0, 0x7b,
    0x7, 0x0, 0x0, 0x7b, 0xf, 0x62, 0x23, 0xc8,
    0x5, 0xdf, 0xff, 0xa1,

    /* U+0036 "6" */
    0x5, 0xdf, 0xff, 0xb1, 0xf, 0x72, 0x23, 0xb9,
    0x2f, 0x0, 0x0, 0x24, 0x2f, 0xaf, 0xfe, 0xa1,
    0x2f, 0x72, 0x23, 0xc8, 0x2f, 0x0, 0x0, 0x6b,
    0x2f, 0x0, 0x0, 0x7b, 0xf, 0x72, 0x23, 0xc8,
    0x4, 0xdf, 0xff, 0xa1,

    /* U+0037 "7" */
    0xaf, 0xff, 0xff, 0x41, 0x22, 0x22, 0xd4, 0x0,
    0x0, 0x2f, 0x10, 0x0, 0x1c, 0x90, 0x0, 0x2e,
    0xa0, 0x0, 0xb, 0xa0, 0x0, 0x1, 0xf2, 0x0,
    0x0, 0x3f, 0x0, 0x0, 0x2, 0xd0, 0x0, 0x0,

    /* U+0038 "8" */
    0x2, 0xcf, 0xfe, 0xa0, 0xc, 0x92, 0x23, 0xd6,
    0xe, 0x40, 0x0, 0x99, 0xb, 0x70, 0x0, 0xd5,
    0x4, 0xff, 0xff, 0xe0, 0xf, 0x62, 0x23, 0xb9,
    0x3f, 0x0, 0x0, 0x6c, 0x1f, 0x62, 0x23, 0xba,
    0x5, 0xdf, 0xff, 0xb1,

    /* U+0039 "9" */
    0x4, 0xdf, 0xff, 0xa1, 0xe, 0x72, 0x23, 0xc8,
    0x2f, 0x0, 0x0, 0x6b, 0x2f, 0x0, 0x0, 0x7c,
    0xf, 0x50, 0x0, 0xbc, 0x6, 0xff, 0xff, 0xdc,
    0x4, 0x2, 0x21, 0x6b, 0xf, 0x62, 0x23, 0xb9,
    0x5, 0xdf, 0xff, 0xb1,

    /* U+003A ":" */
    0x0, 0xc9, 0x31, 0x0, 0x0, 0x43, 0xb8,

    /* U+003B ";" */
    0x1, 0x0, 0xf6, 0x3, 0x10, 0x0, 0x0, 0x0,
    0x20, 0xf, 0x63, 0xf2, 0x5a, 0x0,

    /* U+003C "<" */
    0x0, 0x1, 0xaa, 0x0, 0x8e, 0x80, 0x2e, 0xa1,
    0x0, 0x9, 0xe7, 0x0, 0x0, 0x2b, 0xd4, 0x0,
    0x0, 0x46,

    /* U+003D "=" */
    0xaf, 0xff, 0xff, 0x30, 0x0, 0x0, 0x0, 0xaf,
    0xff, 0xff, 0x30,

    /* U+003E ">" */
    0x2d, 0x50, 0x0, 0x3, 0xcc, 0x40, 0x0, 0x5,
    0xe9, 0x0, 0x2b, 0xd4, 0x19, 0xe6, 0x0, 0x17,
    0x0, 0x0,

    /* U+003F "?" */
    0x1a, 0xff, 0xe7, 0x8, 0xc3, 0x24, 0xf3, 0xa6,
    0x0, 0xd, 0x50, 0x0, 0x5, 0xf2, 0x0, 0x9,
    0xf6, 0x0, 0x1, 0xf2, 0x0, 0x0, 0x18, 0x0,
    0x0, 0x1, 0x60, 0x0, 0x0, 0x5e, 0x0, 0x0,

    /* U+0040 "@" */
    0x3d, 0xff, 0xff, 0xe8, 0xc, 0x40, 0x0, 0x0,
    0xd2, 0xd1, 0x8e, 0xfc, 0x3b, 0x3e, 0x2e, 0x0,
    0xc4, 0xb4, 0xe2, 0xe0, 0xd, 0x4b, 0x3d, 0x18,
    0xee, 0x8e, 0xd1, 0xc4, 0x0, 0x0, 0x6, 0x4,
    0xdf, 0xff, 0xff, 0xa0,

    /* U+0041 "A" */
    0x0, 0x1, 0xe5, 0x0, 0x0, 0x0, 0x7f, 0xc0,
    0x0, 0x0, 0xd, 0x7f, 0x30, 0x0, 0x5, 0xe0,
    0xaa, 0x0, 0x0, 0xb8, 0x4, 0xf1, 0x0, 0x2f,
    0x20, 0xd, 0x80, 0x9, 0xff, 0xff, 0xfe, 0x1,
    0xf6, 0x22, 0x23, 0xe5, 0x4c, 0x0, 0x0, 0x7,
    0xa0,

    /* U+0042 "B" */
    0x7f, 0xff, 0xfe, 0x50, 0x8a, 0x22, 0x27, 0xf0,
    0x8a, 0x0, 0x4, 0xe0, 0x8f, 0xff, 0xff, 0xb0,
    0x8b, 0x22, 0x24, 0xf4, 0x8a, 0x0, 0x0, 0xb8,
    0x8a, 0x0, 0x0, 0xb7, 0x8a, 0x22, 0x24, 0xf4,
    0x7f, 0xff, 0xfe, 0x80,

    /* U+0043 "C" */
    0x9, 0xef, 0xfe, 0xa1, 0x9c, 0x32, 0x23, 0xc9,
    0xc5, 0x0, 0x0, 0x37, 0xe4, 0x0, 0x0, 0x0,
    0xe4, 0x0, 0x0, 0x0, 0xe4, 0x0, 0x0, 0x0,
    0xc5, 0x0, 0x0, 0x37, 0x9c, 0x32, 0x23, 0xc9,
    0x19, 0xef, 0xff, 0xa1,

    /* U+0044 "D" */
    0x7f, 0xff, 0xfd, 0x80, 0x8a, 0x22, 0x24, 0xd8,
    0x8a, 0x0, 0x0, 0x5d, 0x8a, 0x0, 0x0, 0x3f,
    0x8a, 0x0, 0x0, 0x3f, 0x8a, 0x0, 0x0, 0x3f,
    0x8a, 0x0, 0x0, 0x5d, 0x8a, 0x22, 0x24, 0xd8,
    0x7f, 0xff, 0xfd, 0x80,

    /* U+0045 "E" */
    0x7f, 0xff, 0xff, 0x88, 0xa2, 0x22, 0x20, 0x8a,
    0x0, 0x0, 0x8, 0xa0, 0x0, 0x0, 0x8f, 0xff,
    0xd0, 0x8, 0xb2, 0x21, 0x0, 0x8a, 0x0, 0x0,
    0x8, 0xa2, 0x22, 0x20, 0x7f, 0xff, 0xff, 0x80,

    /* U+0046 "F" */
    0x7f, 0xff, 0xff, 0xa8, 0xa2, 0x22, 0x21, 0x8a,
    0x0, 0x0, 0x8, 0xa0, 0x0, 0x0, 0x8f, 0xff,
    0xe0, 0x8, 0xb2, 0x21, 0x0, 0x8a, 0x0, 0x0,
    0x8, 0xa0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0,

    /* U+0047 "G" */
    0x9, 0xef, 0xff, 0xb1, 0x9c, 0x32, 0x23, 0xb9,
    0xc5, 0x0, 0x0, 0x24, 0xe4, 0x0, 0x0, 0x0,
    0xe4, 0x0, 0xe, 0xfb, 0xe4, 0x0, 0x2, 0x7c,
    0xc5, 0x0, 0x0, 0x6b, 0x9c, 0x32, 0x23, 0xd7,
    0x19, 0xef, 0xfe, 0xa0,

    /* U+0048 "H" */
    0x78, 0x0, 0x0, 0x8, 0x68, 0xa0, 0x0, 0x0,
    0xa8, 0x8a, 0x0, 0x0, 0xa, 0x88, 0xa0, 0x0,
    0x0, 0xa8, 0x8f, 0xff, 0xff, 0xff, 0x88, 0xb2,
    0x22, 0x22, 0xb8, 0x8a, 0x0, 0x0, 0xa, 0x88,
    0xa0, 0x0, 0x0, 0xa8, 0x78, 0x0, 0x0, 0x9,
    0x60,

    /* U+0049 "I" */
    0x78, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a, 0x8a,
    0x78,

    /* U+004A "J" */
    0x0, 0x0, 0x0, 0xc4, 0x0, 0x0, 0x0, 0xd5,
    0x0, 0x0, 0x0, 0xd5, 0x0, 0x0, 0x0, 0xd5,
    0x0, 0x0, 0x0, 0xd5, 0x0, 0x0, 0x0, 0xd5,
    0x46, 0x0, 0x0, 0xe4, 0x5e, 0x42, 0x26, 0xf1,
    0x8, 0xef, 0xfd, 0x50,

    /* U+004B "K" */
    0x78, 0x0, 0x2d, 0x18, 0xa0, 0x2e, 0x80, 0x8a,
    0x3e, 0x80, 0x8, 0xce, 0x80, 0x0, 0x8f, 0xe9,
    0x0, 0x8, 0xa2, 0xf6, 0x0, 0x8a, 0x4, 0xf4,
    0x8, 0xa0, 0x6, 0xf2, 0x78, 0x0, 0x8, 0x90,

    /* U+004C "L" */
    0x78, 0x0, 0x0, 0x8, 0xa0, 0x0, 0x0, 0x8a,
    0x0, 0x0, 0x8, 0xa0, 0x0, 0x0, 0x8a, 0x0,
    0x0, 0x8, 0xa0, 0x0, 0x0, 0x8a, 0x0, 0x0,
    0x8, 0xa2, 0x22, 0x10, 0x7f, 0xff, 0xff, 0x0,

    /* U+004D "M" */
    0x7b, 0x0, 0x0, 0x1, 0xe3, 0x8f, 0x70, 0x0,
    0xb, 0xf4, 0x8d, 0xf3, 0x0, 0x7e, 0xf4, 0x8a,
    0x8d, 0x2, 0xf3, 0xe4, 0x8a, 0xc, 0x9d, 0x80,
    0xe4, 0x8a, 0x1, 0xec, 0x0, 0xe4, 0x8a, 0x0,
    0x10, 0x0, 0xe4, 0x8a, 0x0, 0x0, 0x0, 0xe4,
    0x78, 0x0, 0x0, 0x0, 0xc3,

    /* U+004E "N" */
    0x7b, 0x0, 0x0, 0xe, 0x18, 0xf9, 0x0, 0x0,
    0xf2, 0x8c, 0xf6, 0x0, 0xf, 0x28, 0xa4, 0xf3,
    0x0, 0xf2, 0x8a, 0x7, 0xe1, 0xf, 0x28, 0xa0,
    0xa, 0xd1, 0xf2, 0x8a, 0x0, 0xc, 0xbf, 0x28,
    0xa0, 0x0, 0x1e, 0xf2, 0x78, 0x0, 0x0, 0x3e,
    0x10,

    /* U+004F "O" */
    0x9, 0xef, 0xfe, 0xb2, 0x9, 0xc3, 0x22, 0x3b,
    0xc0, 0xc5, 0x0, 0x0, 0x2f, 0xe, 0x40, 0x0,
    0x1, 0xf1, 0xe4, 0x0, 0x0, 0x1f, 0x1e, 0x40,
    0x0, 0x1, 0xf1, 0xc5, 0x0, 0x0, 0x2f, 0x9,
    0xc3, 0x22, 0x3a, 0xc0, 0x19, 0xef, 0xfe, 0xb2,
    0x0,

    /* U+0050 "P" */
    0x7f, 0xff, 0xfc, 0x28, 0xa2, 0x22, 0x9c, 0x8a,
    0x0, 0x3, 0xf8, 0xa0, 0x0, 0x7d, 0x8f, 0xff,
    0xfe, 0x48, 0xb2, 0x22, 0x0, 0x8a, 0x0, 0x0,
    0x8, 0xa0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x9, 0xef, 0xfe, 0xb2, 0x9, 0xc3, 0x22, 0x3b,
    0xc0, 0xc5, 0x0, 0x0, 0x2f, 0xe, 0x40, 0x0,
    0x1, 0xf1, 0xe4, 0x0, 0x0, 0x1f, 0x1e, 0x40,
    0x0, 0x1, 0xf1, 0xc5, 0x0, 0x3, 0x2f, 0x9,
    0xc3, 0x24, 0xfc, 0xb0, 0x19, 0xef, 0xfe, 0xf6,
    0x0, 0x0, 0x0, 0x3, 0xd0,

    /* U+0052 "R" */
    0x7f, 0xff, 0xfc, 0x28, 0xa2, 0x22, 0x9c, 0x8a,
    0x0, 0x3, 0xf8, 0xa0, 0x0, 0x7d, 0x8f, 0xff,
    0xfe, 0x48, 0xb3, 0x4f, 0x30, 0x8a, 0x0, 0x9c,
    0x8, 0xa0, 0x0, 0xe6, 0x78, 0x0, 0x5, 0xb0,

    /* U+0053 "S" */
    0x9, 0xef, 0xfe, 0x70, 0x4e, 0x32, 0x24, 0xf2,
    0x7b, 0x0, 0x0, 0x41, 0x5d, 0x10, 0x0, 0x0,
    0xb, 0xff, 0xfe, 0x90, 0x0, 0x12, 0x24, 0xe5,
    0x30, 0x0, 0x0, 0xa8, 0xca, 0x22, 0x23, 0xe6,
    0x2c, 0xff, 0xfe, 0x90,

    /* U+0054 "T" */
    0x7f, 0xff, 0xff, 0xff, 0x10, 0x22, 0x6e, 0x22,
    0x20, 0x0, 0x4, 0xe0, 0x0, 0x0, 0x0, 0x4e,
    0x0, 0x0, 0x0, 0x4, 0xe0, 0x0, 0x0, 0x0,
    0x4e, 0x0, 0x0, 0x0, 0x4, 0xe0, 0x0, 0x0,
    0x0, 0x4e, 0x0, 0x0, 0x0, 0x3, 0xc0, 0x0,
    0x0,

    /* U+0055 "U" */
    0x96, 0x0, 0x0, 0xc, 0x3b, 0x70, 0x0, 0x0,
    0xe4, 0xb7, 0x0, 0x0, 0xe, 0x4b, 0x70, 0x0,
    0x0, 0xe4, 0xb7, 0x0, 0x0, 0xe, 0x4b, 0x70,
    0x0, 0x0, 0xe4, 0x98, 0x0, 0x0, 0xf, 0x36,
    0xe4, 0x22, 0x28, 0xe0, 0x8, 0xef, 0xff, 0xc3,
    0x0,

    /* U+0056 "V" */
    0x88, 0x0, 0x0, 0x8, 0x84, 0xf0, 0x0, 0x0,
    0xe4, 0xd, 0x70, 0x0, 0x6d, 0x0, 0x6d, 0x0,
    0xd, 0x60, 0x0, 0xe5, 0x4, 0xe0, 0x0, 0x8,
    0xc0, 0xb7, 0x0, 0x0, 0x1f, 0x5f, 0x10, 0x0,
    0x0, 0x9f, 0x90, 0x0, 0x0, 0x2, 0xe2, 0x0,
    0x0,

    /* U+0057 "W" */
    0x87, 0x0, 0x5, 0xd0, 0x0, 0xd, 0x26, 0xd0,
    0x0, 0xbf, 0x40, 0x4, 0xe0, 0x1f, 0x20, 0xf,
    0xb9, 0x0, 0x99, 0x0, 0xb8, 0x5, 0xc4, 0xe0,
    0xe, 0x40, 0x6, 0xd0, 0xa7, 0xf, 0x34, 0xe0,
    0x0, 0x1f, 0x3f, 0x10, 0xa8, 0x99, 0x0, 0x0,
    0xbc, 0xc0, 0x5, 0xde, 0x40, 0x0, 0x5, 0xf7,
    0x0, 0xf, 0xe0, 0x0, 0x0, 0xe, 0x10, 0x0,
    0x98, 0x0, 0x0,

    /* U+0058 "X" */
    0x1d, 0x20, 0x0, 0x4d, 0x0, 0xac, 0x0, 0x1e,
    0x60, 0x0, 0xd9, 0xc, 0xa0, 0x0, 0x2, 0xfb,
    0xd0, 0x0, 0x0, 0x8, 0xf4, 0x0, 0x0, 0x2,
    0xfc, 0xc0, 0x0, 0x0, 0xca, 0xd, 0x90, 0x0,
    0x8d, 0x0, 0x2f, 0x50, 0xd, 0x30, 0x0, 0x5b,
    0x0,

    /* U+0059 "Y" */
    0x89, 0x0, 0x0, 0x1d, 0x22, 0xf3, 0x0, 0xa,
    0xb0, 0x7, 0xd0, 0x5, 0xe1, 0x0, 0xc, 0x81,
    0xe5, 0x0, 0x0, 0x2f, 0xca, 0x0, 0x0, 0x0,
    0x8e, 0x10, 0x0, 0x0, 0x5, 0xd0, 0x0, 0x0,
    0x0, 0x5d, 0x0, 0x0, 0x0, 0x4, 0xb0, 0x0,
    0x0,

    /* U+005A "Z" */
    0x8, 0xef, 0xff, 0xff, 0x22, 0xf4, 0x22, 0x2c,
    0xa0, 0x1, 0x0, 0x7, 0xc0, 0x0, 0x0, 0x4,
    0xe1, 0x0, 0x0, 0x2, 0xe3, 0x0, 0x0, 0x0,
    0xd6, 0x0, 0x0, 0x0, 0xb9, 0x0, 0x0, 0x10,
    0x8d, 0x22, 0x22, 0x8c, 0xf, 0xff, 0xff, 0xfd,
    0x40,

    /* U+005B "[" */
    0x1f, 0xd0, 0x1e, 0x0, 0x1e, 0x0, 0x1e, 0x0,
    0x1e, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x1e, 0x0,
    0x1e, 0x0, 0x1e, 0x0, 0x1e, 0x0, 0x1f, 0xd0,

    /* U+005C "\\" */
    0xe, 0x10, 0x0, 0xd6, 0x0, 0x9, 0xa0, 0x0,
    0x4e, 0x0, 0x0, 0xf2, 0x0, 0xc, 0x70, 0x0,
    0x8b, 0x0, 0x3, 0xf0, 0x0, 0xf, 0x30, 0x0,
    0xb7, 0x0, 0x7, 0xc0, 0x0, 0x2d,

    /* U+005D "]" */
    0xaf, 0x30, 0xb4, 0xb, 0x40, 0xb4, 0xb, 0x40,
    0xb4, 0xb, 0x40, 0xb4, 0xb, 0x40, 0xb4, 0xb,
    0x4b, 0xf3,

    /* U+005E "^" */
    0xa, 0xa0, 0x1e, 0xe1, 0x79, 0x97, 0xb2, 0x3b,

    /* U+005F "_" */
    0x3f, 0xff, 0xf4, 0x2, 0x22, 0x20,

    /* U+0060 "`" */
    0x4, 0x1, 0xe3, 0x5, 0xa0,

    /* U+0061 "a" */
    0x2b, 0xff, 0xe9, 0x7, 0x82, 0x23, 0xc6, 0x2c,
    0xff, 0xff, 0x9a, 0xa3, 0x22, 0x9a, 0xc5, 0x0,
    0x9, 0xaa, 0xa2, 0x26, 0xfa, 0x2c, 0xff, 0xb9,
    0x80,

    /* U+0062 "b" */
    0x78, 0x0, 0x0, 0x0, 0x8a, 0x0, 0x0, 0x0,
    0x8a, 0x0, 0x0, 0x0, 0x8c, 0xbf, 0xfc, 0x30,
    0x8e, 0x52, 0x28, 0xd0, 0x8a, 0x0, 0x1, 0xf0,
    0x8a, 0x0, 0x1, 0xf1, 0x8a, 0x0, 0x1, 0xf0,
    0x8e, 0x52, 0x28, 0xd0, 0x7a, 0xbf, 0xfc, 0x30,

    /* U+0063 "c" */
    0x1b, 0xff, 0xfa, 0xa, 0xb3, 0x23, 0xc5, 0xd5,
    0x0, 0x0, 0xe, 0x40, 0x0, 0x0, 0xd5, 0x0,
    0x0, 0xa, 0xb3, 0x23, 0xc5, 0x1b, 0xff, 0xfa,
    0x0,

    /* U+0064 "d" */
    0x0, 0x0, 0x5, 0xa0, 0x0, 0x0, 0x6c, 0x0,
    0x0, 0x6, 0xc1, 0xbf, 0xff, 0xfc, 0xab, 0x32,
    0x28, 0xcd, 0x50, 0x0, 0x6c, 0xe4, 0x0, 0x6,
    0xcd, 0x50, 0x0, 0x6c, 0xab, 0x32, 0x4c, 0xc1,
    0xbf, 0xfd, 0xaa,

    /* U+0065 "e" */
    0x1b, 0xff, 0xea, 0xa, 0xb3, 0x23, 0xd7, 0xd5,
    0x0, 0x7, 0xbe, 0xff, 0xff, 0xfb, 0xd7, 0x33,
    0x33, 0x3a, 0xa2, 0x23, 0xb9, 0x1b, 0xff, 0xfb,
    0x10,

    /* U+0066 "f" */
    0x0, 0x4d, 0xc0, 0x1f, 0x61, 0x3, 0xe0, 0x4,
    0xff, 0xfc, 0x6, 0xe2, 0x10, 0x4e, 0x0, 0x4,
    0xe0, 0x0, 0x4e, 0x0, 0x4, 0xe0, 0x0, 0x3c,
    0x0,

    /* U+0067 "g" */
    0x1b, 0xff, 0xeb, 0xaa, 0xb3, 0x23, 0xbc, 0xd5,
    0x0, 0x6, 0xce, 0x40, 0x0, 0x6c, 0xd5, 0x0,
    0x6, 0xca, 0xb3, 0x24, 0xcc, 0x1b, 0xff, 0xca,
    0xc0, 0x0, 0x0, 0x6b, 0xb6, 0x22, 0x29, 0xa5,
    0xef, 0xff, 0xd3,

    /* U+0068 "h" */
    0x69, 0x0, 0x0, 0x0, 0x7b, 0x0, 0x0, 0x0,
    0x7b, 0x0, 0x0, 0x0, 0x7e, 0xdf, 0xfc, 0x20,
    0x7f, 0x62, 0x29, 0xc0, 0x7b, 0x0, 0x2, 0xf0,
    0x7b, 0x0, 0x2, 0xf0, 0x7b, 0x0, 0x2, 0xf0,
    0x7b, 0x0, 0x2, 0xf0, 0x69, 0x0, 0x1, 0xe0,

    /* U+0069 "i" */
    0xbc, 0x78, 0x0, 0x78, 0x8a, 0x8a, 0x8a, 0x8a,
    0x8a, 0x78,

    /* U+006A "j" */
    0x0, 0xbc, 0x0, 0x78, 0x0, 0x0, 0x0, 0x78,
    0x0, 0x8a, 0x0, 0x8a, 0x0, 0x8a, 0x0, 0x8a,
    0x0, 0x8a, 0x0, 0x8a, 0x0, 0x89, 0x2, 0xb8,
    0xe, 0xc1,

    /* U+006B "k" */
    0x78, 0x0, 0x0, 0x8a, 0x0, 0x0, 0x8a, 0x0,
    0x0, 0x8a, 0x0, 0x6c, 0x8a, 0x9, 0xf4, 0x8a,
    0xbe, 0x20, 0x8f, 0xf7, 0x0, 0x8c, 0x5f, 0x40,
    0x8a, 0x6, 0xf3, 0x78, 0x0, 0x7a,

    /* U+006C "l" */
    0x78, 0x0, 0x8a, 0x0, 0x8a, 0x0, 0x8a, 0x0,
    0x8a, 0x0, 0x8a, 0x0, 0x8a, 0x0, 0x8a, 0x0,
    0x7c, 0x20, 0x1c, 0xf1,

    /* U+006D "m" */
    0x7a, 0xcf, 0xe6, 0xaf, 0xfb, 0x18, 0xe4, 0x27,
    0xfa, 0x23, 0xd8, 0x8a, 0x0, 0xf, 0x30, 0x7,
    0xa8, 0xa0, 0x0, 0xf2, 0x0, 0x7b, 0x8a, 0x0,
    0xf, 0x20, 0x7, 0xb8, 0xa0, 0x0, 0xf2, 0x0,
    0x7b, 0x78, 0x0, 0xe, 0x10, 0x6, 0x90,

    /* U+006E "n" */
    0x7a, 0xbf, 0xfb, 0x28, 0xe5, 0x22, 0xab, 0x8a,
    0x0, 0x3, 0xe8, 0xa0, 0x0, 0x3f, 0x8a, 0x0,
    0x3, 0xf8, 0xa0, 0x0, 0x3f, 0x78, 0x0, 0x2,
    0xd0,

    /* U+006F "o" */
    0x1b, 0xff, 0xea, 0xa, 0xb3, 0x23, 0xc8, 0xd5,
    0x0, 0x7, 0xbe, 0x40, 0x0, 0x6c, 0xd5, 0x0,
    0x7, 0xba, 0xb3, 0x23, 0xc8, 0x1b, 0xff, 0xea,
    0x10,

    /* U+0070 "p" */
    0x7a, 0xbf, 0xfc, 0x30, 0x8e, 0x52, 0x28, 0xd0,
    0x8a, 0x0, 0x1, 0xf0, 0x8a, 0x0, 0x1, 0xf1,
    0x8a, 0x0, 0x1, 0xf0, 0x8a, 0x22, 0x28, 0xd0,
    0x8f, 0xff, 0xfc, 0x30, 0x8a, 0x0, 0x0, 0x0,
    0x8a, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0,

    /* U+0071 "q" */
    0x1b, 0xff, 0xd9, 0xaa, 0xb3, 0x24, 0xcc, 0xd5,
    0x0, 0x6, 0xce, 0x40, 0x0, 0x6c, 0xd5, 0x0,
    0x6, 0xca, 0xb3, 0x22, 0x8c, 0x1b, 0xff, 0xff,
    0xc0, 0x0, 0x0, 0x6c, 0x0, 0x0, 0x6, 0xc0,
    0x0, 0x0, 0x5a,

    /* U+0072 "r" */
    0x79, 0x9e, 0x98, 0xf8, 0x30, 0x8b, 0x0, 0x8,
    0xa0, 0x0, 0x8a, 0x0, 0x8, 0xa0, 0x0, 0x78,
    0x0, 0x0,

    /* U+0073 "s" */
    0x4e, 0xff, 0xfb, 0xc, 0x82, 0x23, 0xc3, 0xc6,
    0x0, 0x0, 0x6, 0xff, 0xff, 0xb1, 0x1, 0x22,
    0x3c, 0x6d, 0x62, 0x22, 0xc6, 0x6e, 0xff, 0xfc,
    0x10,

    /* U+0074 "t" */
    0x0, 0x50, 0x0, 0x3, 0xe0, 0x0, 0x6f, 0xff,
    0xf0, 0x5, 0xe2, 0x10, 0x4, 0xe0, 0x0, 0x4,
    0xe0, 0x0, 0x3, 0xf0, 0x0, 0x1, 0xf6, 0x10,
    0x0, 0x5d, 0xe0,

    /* U+0075 "u" */
    0x96, 0x0, 0x4, 0xbb, 0x70, 0x0, 0x5d, 0xb7,
    0x0, 0x5, 0xdb, 0x70, 0x0, 0x5d, 0xa8, 0x0,
    0x5, 0xd7, 0xd3, 0x24, 0xbd, 0xa, 0xef, 0xd8,
    0xb0,

    /* U+0076 "v" */
    0x6a, 0x0, 0x5, 0xc2, 0xf1, 0x0, 0xc8, 0xc,
    0x80, 0x3f, 0x10, 0x5e, 0xb, 0x90, 0x0, 0xe7,
    0xf2, 0x0, 0x8, 0xfb, 0x0, 0x0, 0x1e, 0x30,
    0x0,

    /* U+0077 "w" */
    0x6a, 0x0, 0x5d, 0x0, 0x2e, 0x3, 0xf0, 0xb,
    0xf3, 0x8, 0xb0, 0xe, 0x51, 0xfb, 0x80, 0xd5,
    0x0, 0x8b, 0x5b, 0x5d, 0x3f, 0x0, 0x3, 0xfb,
    0x51, 0xfb, 0x90, 0x0, 0xe, 0xf1, 0xc, 0xf3,
    0x0, 0x0, 0x7a, 0x0, 0x6c, 0x0, 0x0,

    /* U+0078 "x" */
    0xb, 0x50, 0xc, 0x50, 0x5f, 0x29, 0xd0, 0x0,
    0x8e, 0xf2, 0x0, 0x4, 0xfb, 0x0, 0x1, 0xe8,
    0xe7, 0x0, 0xbb, 0x3, 0xf4, 0x2d, 0x10, 0x7,
    0xa0,

    /* U+0079 "y" */
    0x96, 0x0, 0x1, 0xe0, 0xb7, 0x0, 0x1, 0xf1,
    0xb7, 0x0, 0x1, 0xf1, 0xb7, 0x0, 0x1, 0xf1,
    0xa8, 0x0, 0x2, 0xf1, 0x7d, 0x32, 0x3b, 0xf1,
    0xa, 0xef, 0xd8, 0xf1, 0x74, 0x0, 0x1, 0xf0,
    0x9a, 0x22, 0x25, 0xf0, 0x2d, 0xff, 0xfe, 0x70,

    /* U+007A "z" */
    0xb, 0xff, 0xff, 0x80, 0x4c, 0x22, 0x7f, 0x20,
    0x0, 0x2, 0xe4, 0x0, 0x0, 0xd, 0x70, 0x0,
    0x0, 0xba, 0x0, 0x0, 0x8, 0xe3, 0x23, 0xe0,
    0xe, 0xff, 0xff, 0x80,

    /* U+007B "{" */
    0x0, 0x4e, 0xb0, 0xd, 0x30, 0x0, 0xf0, 0x0,
    0xf, 0x0, 0x0, 0xf0, 0x0, 0xcd, 0x0, 0xe,
    0xb0, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x0, 0xd3, 0x0, 0x4, 0xdb,

    /* U+007C "|" */
    0xc3, 0xe4, 0xe4, 0xe4, 0xe4, 0xe4, 0xe4, 0xe4,
    0xe4, 0xe4, 0xe4, 0xd4, 0x0,

    /* U+007D "}" */
    0xae, 0x40, 0x0, 0x3d, 0x0, 0x0, 0xf0, 0x0,
    0xf, 0x0, 0x0, 0xf0, 0x0, 0xc, 0xc0, 0x0,
    0xbe, 0x0, 0xf, 0x0, 0x0, 0xf0, 0x0, 0xf,
    0x0, 0x3, 0xd0, 0xb, 0xd4, 0x0,

    /* U+007E "~" */
    0x2c, 0xd6, 0x1b, 0x29, 0x41, 0xae, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 70, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 60, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 18, .adv_w = 139, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 107, .adv_w = 197, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 53, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 206, .adv_w = 67, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 236, .adv_w = 67, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 260, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 268, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 293, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 299, .adv_w = 115, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 302, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 72, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 334, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 138, .box_w = 4, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 60, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 58, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 698, .adv_w = 136, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 716, .adv_w = 136, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 727, .adv_w = 136, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 745, .adv_w = 114, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 166, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 149, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 151, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 890, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 162, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 994, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 156, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1062, .adv_w = 176, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1103, .adv_w = 65, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1112, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1148, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1180, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1212, .adv_w = 187, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 170, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1298, .adv_w = 163, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1339, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1371, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1416, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1448, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1484, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1525, .adv_w = 169, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 144, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1607, .adv_w = 201, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1666, .adv_w = 140, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1707, .adv_w = 138, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1748, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1789, .adv_w = 51, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1813, .adv_w = 72, .box_w = 5, .box_h = 12, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1843, .adv_w = 51, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1861, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1869, .adv_w = 105, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1875, .adv_w = 56, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1880, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1905, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1945, .adv_w = 132, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1970, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2005, .adv_w = 142, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2030, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2055, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2090, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2130, .adv_w = 65, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2140, .adv_w = 65, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 2166, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2196, .adv_w = 77, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2216, .adv_w = 208, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2255, .adv_w = 148, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2280, .adv_w = 142, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2305, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2345, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2380, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2398, .adv_w = 137, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2423, .adv_w = 94, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2450, .adv_w = 148, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2475, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2500, .adv_w = 168, .box_w = 11, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2539, .adv_w = 119, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2564, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2604, .adv_w = 122, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2632, .adv_w = 80, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2662, .adv_w = 55, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2675, .adv_w = 80, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2705, .adv_w = 136, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4}
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
    0, 0, 0, -11, 0, 0, 0, -16,
    -4, 0, 0, 0, 0, -7, 0, 0,
    0, 0, -4, 0, 0, -11, 0, 0,
    -4, -2, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -4, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, -4, 0, 0,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, -7, -7, 0, -11, 0, 0, 0,
    -2, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, -2,
    0, 0, 0, 0, 0, -9, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    -4, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -7, -2, 0, -7, 0, -4, -16, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, -7, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -31, -11, -11, 0, -9, 0, -4,
    -18, 0, 0, 0, 0, -2, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -13, 0, 0, -9, 0,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -22, -7, -22, 0, 0, 0,
    0, -16, 0, -2, 0, 0, 0, -11,
    0, 0, 0, 0, 0, -2, 0, -18,
    -7, 0, -11, 0, 0, 0, -4, -4,
    0, -2, 0, 0, -4, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -9, -4, 0,
    -7, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -4, 0,
    0, -4, 0, -9, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -7, 0,
    0, 0, 0, -11, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, -2, 0,
    -2, -9, -4, -4, -4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, 0, -4, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -7,
    0, 0, -7, 0, 0, -9, 0, 0,
    0, -4, 0, -20, 0, 0, 0, -4,
    -2, 0, -11, 0, 0, -7, 0, 0,
    0, 0, -18, -2, -18, 2, 0, 0,
    7, 0, 0, -11, 0, -16, 0, -16,
    -13, 0, -11, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -16, 0,
    0, -9, 0, 0, -2, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -7,
    0, 0, 0, 0, -4, -7, 0, 0,
    -27, 0, -38, 0, -27, 0, 0, -18,
    0, 0, 0, -2, -2, -16, -2, -4,
    0, 0, 0, -4, 0, -20, -16, 0,
    -22, 0, 0, -4, 0, 0, 0, 0,
    0, -9, -4, -18, 0, 0, 0, 0,
    0, -29, 0, 0, 0, -4, -2, -7,
    -18, 0, 0, -4, 0, 0, 0, 0,
    -13, 0, -11, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -4, 0, 0,
    0, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -7, -2, 0, -2, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -4, -2, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -25, -31, 0,
    0, -4, 0, -4, -25, 0, 0, 0,
    -9, 0, -18, 0, -18, -9, -22, 0,
    4, 0, 4, 0, 0, -25, -4, -25,
    0, -20, -25, 0, -25, -20, -22, -25,
    0, -7, 0, -22, -16, 0, 0, -4,
    0, 0, -9, 0, 0, 0, -2, 0,
    -11, 0, -7, -4, -16, 2, 0, 0,
    4, 0, 0, -13, 0, -16, 0, -4,
    -11, 0, -7, 0, 0, 0, 0, 0,
    0, 0, -20, 0, 0, -7, 0, 0,
    -2, 0, 0, -2, -7, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, -7, 0, -9, 0, 0, 0, 0,
    -7, -9, 0, 0, 0, -7, 0, -25,
    -25, 0, 0, -9, -4, -4, -16, 0,
    0, 0, -9, 0, -16, 0, -11, -6,
    -18, 0, 9, 0, 0, 0, 0, -18,
    0, -22, 0, -16, -11, 0, -7, -2,
    -11, -9, 0, 0, 0, 0, -16, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, -13,
    -7, -4, -4, -11, -7, -13, -9, -9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -13, 0, 0, -9, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -13, 0, 0, -11,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, -25, -9, -4, -11, -4, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -4,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -11,
    0, 0, -7, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, -16, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 4, -7, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, -9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -11, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, -4, 0, -7,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -25, -18, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 0, -4, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -29, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    -2, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -20, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, -13, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -4, 0, 0, 0, -4, 0, 0,
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
const lv_font_t jura_bold_14 = {
#else
lv_font_t jura_bold_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if JURA_BOLD_14*/

