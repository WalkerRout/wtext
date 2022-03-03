
#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "data.h"
#include "la.h"



typedef struct {
    SDL_Texture *spriteSheet;
    SDL_Rect glyphTable[ASCII_DISPLAY_HIGH - ASCII_DISPLAY_LOW + 1];
} Font;



Font fontLoadFromFile(const char *path, 
                      SDL_Renderer *renderer);



void renderText(SDL_Renderer *renderer,
                Font *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale);

#endif