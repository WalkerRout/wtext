
#ifndef DATA_H
#define DATA_H

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 920

#define FONT_ROWS 7
#define FONT_COLS 18

#define FONT_WIDTH 128
#define FONT_HEIGHT 64

#define FONT_CHAR_WIDTH (FONT_WIDTH / FONT_COLS)
#define FONT_CHAR_HEIGHT (FONT_HEIGHT / FONT_ROWS)

#define FONT_SCALE 5

#define ASCII_DISPLAY_LOW 32
#define ASCII_DISPLAY_HIGH 126

#define BUFFER_CAPACITY 1024



typedef struct {
    float x, y;
} Vec2f;



typedef struct {
    SDL_Texture *spriteSheet;
    SDL_Rect glyphTable[ASCII_DISPLAY_HIGH - ASCII_DISPLAY_LOW + 1];
} Font;


#endif
