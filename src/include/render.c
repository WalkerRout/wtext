
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "render.h"



void renderChar(SDL_Renderer *renderer,
                Font *font,
                char c,
                Vec2f pos,
                float scale){

    const SDL_Rect destination = {
        .x = (int) floorf(pos.x),
        .y = (int) floorf(pos.y),
        .w = (int) floorf(FONT_CHAR_WIDTH * scale),
        .h = (int) floorf(FONT_CHAR_WIDTH * scale)
    };

    assert(c >= ASCII_DISPLAY_LOW);
    assert(c <= ASCII_DISPLAY_HIGH);

    const size_t index = c - ASCII_DISPLAY_LOW;
    scc(SDL_RenderCopy(renderer,
                       font->spriteSheet,
                       &font->glyphTable[index], &destination));
}



void renderTextSized(SDL_Renderer *renderer,
                     Font *font,
                     const char *text,
                     size_t textSize,
                     Vec2f pos,
                     Uint32 colour,
                     float scale){
    
    scc(SDL_SetTextureColorMod(font->spriteSheet, 
                               colour >> (8 * 3) & 0xFF,
                               colour >> (8 * 2) & 0xFF,
                               colour >> (8 * 1) & 0xFF));
    
    scc(SDL_SetTextureAlphaMod(font->spriteSheet,
                               colour >> (8 * 0) & 0xFF));

    Vec2f pen = pos;

    for(size_t i = 0; i < textSize; i++){
        renderChar(renderer,
                   font,
                   text[i],
                   pen,
                   scale);

        pen.x += FONT_CHAR_WIDTH * scale;
    }
}



void renderText(SDL_Renderer *renderer,
                Font *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale){

    renderTextSized(renderer, 
                    font, 
                    text, 
                    strlen(text), 
                    pos, 
                    colour, 
                    scale);
}
