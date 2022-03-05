
#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>

#include "data.h"

typedef struct {
    SDL_Texture *spriteSheet;
    SDL_Rect glyphTable[ASCII_DISPLAY_HIGH - ASCII_DISPLAY_LOW + 1];
} Font;

void constructFont(Font *font, SDL_Renderer *renderer, const char *path);

#endif
