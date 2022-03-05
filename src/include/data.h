
#ifndef DATA_H
#define DATA_H

#define SCREEN_WIDTH  1080
#define SCREEN_HEIGHT 920

#define WINDOW_COLOUR 0x000000FF
#define CURSOR_COLOUR 0xFFFFFF00
#define FONT_COLOUR   0xFFFFFFFF

#define FONT_ROWS 7
#define FONT_COLS 18

#define FONT_WIDTH  128
#define FONT_HEIGHT 64

#define FONT_CHAR_WIDTH  (FONT_WIDTH / FONT_COLS)
#define FONT_CHAR_HEIGHT (FONT_HEIGHT / FONT_ROWS)

#define FONT_SCALE 5

#define ASCII_DISPLAY_LOW  32
#define ASCII_DISPLAY_HIGH 126

#define BUFFER_CAPACITY 1024

#define UNHEX_UINT32_ARGS(hex) (((hex) >> (8 * 3)) & 0xFF), \
                          (((hex) >> (8 * 2)) & 0xFF), \
                          (((hex) >> (8 * 1)) & 0xFF), \
                          (((hex) >> (8 * 0)) & 0xFF)  \

#endif
