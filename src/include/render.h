
#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

#include "font.h"
#include "la.h"

void renderText(SDL_Renderer *renderer,
                Font *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale);

void renderTextSized(SDL_Renderer *renderer,
                     Font *font,
                     const char *text,
                     size_t textSize,
                     Vec2f pos,
                     Uint32 colour,
                     float scale);

void renderCursor(SDL_Renderer *renderer,
                  size_t *bufferCursor);

#endif
