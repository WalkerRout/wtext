
#ifndef RENDER_H
#define RENDER_H

#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "data.h"
#include "la.h"



void renderText(SDL_Renderer *renderer,
                SDL_Texture *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale);

#endif