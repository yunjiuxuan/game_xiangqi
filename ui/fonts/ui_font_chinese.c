/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font D:/develop/linux/public/YQ_VScode/JieDuan_2/project/assets/ZhiyiSans-Bold.ttf -o D:/develop/linux/public/YQ_VScode/JieDuan_2/project/assets\ui_font_chinese.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_CHINESE
#define UI_FONT_CHINESE 1
#endif

#if UI_FONT_CHINESE

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xcf,

    /* U+0022 "\"" */
    0xff, 0xff, 0xf0,

    /* U+0023 "#" */
    0x2, 0x9, 0x84, 0x82, 0x4f, 0xf9, 0x90, 0xd8,
    0x4c, 0xff, 0x92, 0x19, 0xc, 0x84, 0xc2, 0x60,

    /* U+0024 "$" */
    0x18, 0x7e, 0xe7, 0xc2, 0xc0, 0xf0, 0x7c, 0x1e,
    0x7, 0x3, 0x3, 0xc7, 0x7e, 0x18, 0x18,

    /* U+0025 "%" */
    0x78, 0x6c, 0xcc, 0xcc, 0x8c, 0xd8, 0xcf, 0x7,
    0xae, 0x5, 0xb0, 0xdb, 0x9, 0xb1, 0x1b, 0x31,
    0xb2, 0xe, 0x40, 0x0,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0x98, 0x3c, 0x6, 0x7,
    0x8b, 0x36, 0xc7, 0xb0, 0xce, 0x79, 0xf3,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xcc, 0x66, 0x31,

    /* U+0029 ")" */
    0x8c, 0x66, 0x23, 0x33, 0x33, 0x33, 0x66, 0xc8,

    /* U+002A "*" */
    0x33, 0xcc, 0xf3, 0x0,

    /* U+002B "+" */
    0x8, 0x4, 0x2, 0x1, 0xf, 0xf8, 0x40, 0x20,
    0x10, 0x8, 0x0,

    /* U+002C "," */
    0x6d, 0x2c,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x4, 0x30, 0x82, 0x18, 0x41, 0x8, 0x20, 0x84,
    0x10, 0xc2, 0x8, 0x20,

    /* U+0030 "0" */
    0x3e, 0x31, 0x98, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xb1, 0x98, 0xc7, 0xc0,

    /* U+0031 "1" */
    0x1f, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x80,

    /* U+0032 "2" */
    0x3c, 0x66, 0xc3, 0x43, 0x3, 0x6, 0x1c, 0x38,
    0x70, 0x60, 0xc0, 0xff,

    /* U+0033 "3" */
    0x3e, 0x31, 0xd0, 0x60, 0x30, 0x30, 0xe0, 0xc,
    0x3, 0x1, 0xa0, 0xd8, 0xc7, 0xc0,

    /* U+0034 "4" */
    0x7, 0x3, 0x83, 0xc3, 0x61, 0xb1, 0x99, 0x8d,
    0x86, 0xff, 0x81, 0x80, 0xc0, 0x60,

    /* U+0035 "5" */
    0x7f, 0x30, 0x18, 0xc, 0x5, 0xe3, 0x18, 0x6,
    0x3, 0x1, 0xa0, 0xd8, 0xc7, 0xc0,

    /* U+0036 "6" */
    0x1e, 0x63, 0x40, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3,
    0xc3, 0x43, 0x66, 0x3c,

    /* U+0037 "7" */
    0xff, 0x3, 0x6, 0x6, 0xc, 0xc, 0x18, 0x18,
    0x18, 0x30, 0x30, 0x30,

    /* U+0038 "8" */
    0x3c, 0x33, 0x30, 0xd8, 0x6e, 0x73, 0xe1, 0xf9,
    0xc7, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xe7, 0x3f, 0x3,
    0x3, 0x46, 0xc6, 0x78,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x1b, 0x6b, 0x0,

    /* U+003C "<" */
    0x1, 0x83, 0x87, 0xe, 0xc, 0x3, 0x0, 0x60,
    0xe, 0x1, 0x80, 0x0,

    /* U+003D "=" */
    0xff, 0x80, 0x0, 0x1f, 0xf0,

    /* U+003E ">" */
    0xc0, 0x38, 0x7, 0x0, 0xe0, 0x18, 0x18, 0x30,
    0x60, 0xc0, 0x0, 0x0,

    /* U+003F "?" */
    0x3c, 0x66, 0xc3, 0x43, 0x7, 0xe, 0x1c, 0x18,
    0x18, 0x0, 0x18, 0x18,

    /* U+0040 "@" */
    0xf, 0x83, 0xe, 0x67, 0xe6, 0xdb, 0xd8, 0xbd,
    0x93, 0xd9, 0x3d, 0x96, 0xcf, 0xc6, 0x4, 0x30,
    0xc1, 0xf8,

    /* U+0041 "A" */
    0xc, 0x3, 0x1, 0xe0, 0x78, 0x12, 0xc, 0xc3,
    0x11, 0xfe, 0x61, 0x90, 0x2c, 0xf, 0x3,

    /* U+0042 "B" */
    0xfc, 0xc7, 0xc3, 0xc3, 0xc7, 0xfc, 0xc6, 0xc3,
    0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0043 "C" */
    0x1f, 0xc, 0x76, 0xf, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x18, 0x33, 0x1c, 0x7c,

    /* U+0044 "D" */
    0xfe, 0x30, 0xcc, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x6c, 0x33, 0xf8,

    /* U+0045 "E" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x1f, 0x6, 0x39, 0x83, 0xe0, 0xc, 0x1, 0x80,
    0x30, 0xfe, 0x3, 0xc0, 0x6c, 0xc, 0xc3, 0x8f,
    0xc0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc7, 0xe0,

    /* U+004B "K" */
    0xc3, 0xb1, 0xcc, 0x63, 0x30, 0xd8, 0x3e, 0xf,
    0x83, 0x30, 0xc6, 0x30, 0xcc, 0x33, 0x6,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+004D "M" */
    0xe0, 0x7e, 0x7, 0xf0, 0xff, 0xf, 0xd0, 0xbd,
    0x9b, 0xd9, 0xbc, 0x93, 0xcf, 0x3c, 0x63, 0xc6,
    0x3c, 0x63,

    /* U+004E "N" */
    0xe0, 0xf8, 0x3f, 0xf, 0x63, 0xd8, 0xf3, 0x3c,
    0x6f, 0x1b, 0xc3, 0xf0, 0xfc, 0x1f, 0x3,

    /* U+004F "O" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x6c, 0x18, 0xc6, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc6, 0x6c, 0xf8, 0xc6, 0xf,
    0xf0, 0x2,

    /* U+0052 "R" */
    0xfc, 0x63, 0x30, 0xd8, 0x6c, 0x36, 0x33, 0xf1,
    0x98, 0xc6, 0x61, 0xb0, 0xd8, 0x30,

    /* U+0053 "S" */
    0x3c, 0x67, 0xc2, 0xc0, 0xf0, 0x7c, 0x1e, 0x7,
    0x3, 0x3, 0xc6, 0x7c,

    /* U+0054 "T" */
    0xff, 0xc3, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+0055 "U" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x36, 0x18, 0xfc,

    /* U+0056 "V" */
    0xc0, 0xf0, 0x36, 0x9, 0x86, 0x21, 0x8c, 0xc3,
    0x30, 0x48, 0x1e, 0x7, 0x80, 0xc0, 0x30,

    /* U+0057 "W" */
    0xc1, 0x7, 0x87, 0x9, 0xe, 0x33, 0x14, 0x66,
    0x68, 0xc4, 0xd9, 0xd, 0x36, 0x1a, 0x2c, 0x3c,
    0x70, 0x38, 0xe0, 0x60, 0xc0, 0xc1, 0x0,

    /* U+0058 "X" */
    0x60, 0xcc, 0x18, 0xc6, 0xd, 0x81, 0xb0, 0x1c,
    0x3, 0x80, 0xd8, 0x1b, 0x6, 0x31, 0x83, 0x70,
    0x60,

    /* U+0059 "Y" */
    0xc0, 0xd8, 0x66, 0x18, 0xcc, 0x1e, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0x81, 0xc0, 0xc0, 0xc0, 0xc0, 0x60, 0x60,
    0x60, 0x30, 0x30, 0x30, 0x1f, 0xf0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0x83, 0x4, 0x10, 0x60, 0x82, 0x4, 0x10, 0x40,
    0x82, 0xc, 0x10, 0x41,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x0, 0x18, 0x3c, 0x66, 0xc3, 0x0,

    /* U+005F "_" */
    0xff,

    /* U+0060 "`" */
    0xc9, 0x80,

    /* U+0061 "a" */
    0x3c, 0x6e, 0x46, 0x6, 0x7e, 0xc6, 0xc6, 0xce,
    0x7e,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xe6, 0xfc,

    /* U+0063 "c" */
    0x3c, 0x63, 0xc2, 0xc0, 0xc0, 0xc0, 0xc0, 0x63,
    0x3c,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3f, 0x67, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x67, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x63,
    0x3e,

    /* U+0066 "f" */
    0x3d, 0x86, 0x18, 0xf9, 0x86, 0x18, 0x61, 0x86,
    0x18, 0x60,

    /* U+0067 "g" */
    0x7f, 0xee, 0xc6, 0xc6, 0xc6, 0x7c, 0xc0, 0xc0,
    0x7e, 0xc3, 0xc3, 0x7e,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xf, 0xdc, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x37, 0xe0,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0xc, 0x79, 0xb6, 0x78, 0xf1,
    0xb3, 0x36, 0x6c, 0x60,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x66,

    /* U+006D "m" */
    0xfd, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6,
    0xfc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3f, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x3b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7b, 0x2c, 0x3c, 0x78, 0x70, 0xf3, 0x78,

    /* U+0074 "t" */
    0x3, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x1a, 0x70,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x7e,

    /* U+0076 "v" */
    0xc3, 0xc2, 0x66, 0x66, 0x24, 0x3c, 0x38, 0x18,
    0x18,

    /* U+0077 "w" */
    0xc6, 0x3c, 0x63, 0x47, 0x26, 0xf6, 0x69, 0x62,
    0x94, 0x39, 0xc3, 0xc, 0x10, 0x80,

    /* U+0078 "x" */
    0xc3, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x2c, 0x66,
    0xc3,

    /* U+0079 "y" */
    0xc3, 0xc2, 0x66, 0x66, 0x24, 0x3c, 0x38, 0x18,
    0x18, 0x10, 0x30, 0x60,

    /* U+007A "z" */
    0xfc, 0x31, 0x84, 0x30, 0x86, 0x30, 0xfc,

    /* U+007B "{" */
    0x3b, 0x18, 0xc6, 0x31, 0x98, 0x63, 0x18, 0xc6,
    0x30, 0xe0,

    /* U+007C "|" */
    0xff, 0xff,

    /* U+007D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0xc3, 0x31, 0x8c, 0x63,
    0x1b, 0x80,

    /* U+007E "~" */
    0xf0, 0x99, 0xf
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 69, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 76, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 7, .adv_w = 161, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 161, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 218, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 178, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 49, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 75, .adv_w = 85, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 83, .adv_w = 85, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 91, .adv_w = 95, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 95, .adv_w = 174, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 68, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 108, .adv_w = 92, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 109, .adv_w = 68, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 122, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 161, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 161, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 82, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 82, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 257, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 174, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 274, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 229, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 169, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 186, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 194, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 193, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 192, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 74, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 97, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 165, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 231, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 195, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 204, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 204, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 545, .adv_w = 166, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 150, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 153, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 191, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 238, .box_w = 15, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 176, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 77, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 693, .adv_w = 128, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 705, .adv_w = 77, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 713, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 719, .adv_w = 128, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 720, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 722, .adv_w = 141, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 139, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 146, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 78, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 797, .adv_w = 155, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 69, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 820, .adv_w = 133, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 69, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 837, .adv_w = 223, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 155, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 859, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 880, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 892, .adv_w = 95, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 898, .adv_w = 118, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 89, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 913, .adv_w = 155, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 921, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 930, .adv_w = 193, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 953, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 965, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 972, .adv_w = 84, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 982, .adv_w = 51, .box_w = 1, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 984, .adv_w = 84, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 994, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
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



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_chinese = {
#else
lv_font_t ui_font_chinese = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_CHINESE*/

