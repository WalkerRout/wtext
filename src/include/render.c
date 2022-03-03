
#include "render.h"



void renderChar(SDL_Renderer *renderer,
                SDL_Texture *font,
                char c,
                Vec2f pos,
                Uint32 colour,
                float scale){

    const size_t index = c - ASCII_DISPLAY_LOW;
    
    const size_t row = index / FONT_COLS;
    const size_t col = index % FONT_COLS;

    const SDL_Rect source = {
        .x = col * FONT_CHAR_WIDTH,
        .y = row * FONT_CHAR_HEIGHT,
        .w = FONT_CHAR_WIDTH,
        .h = FONT_CHAR_HEIGHT
    };

    const SDL_Rect destination = {
        .x = (int) floorf(pos.x),
        .y = (int) floorf(pos.y),
        .w = (int) floorf(FONT_CHAR_WIDTH * scale),
        .h = (int) floorf(FONT_CHAR_WIDTH * scale)
    };

    scc(SDL_SetTextureColorMod(font, 
                               colour >> (8 * 3) & 0xFF,
                               colour >> (8 * 2) & 0xFF,
                               colour >> (8 * 1) & 0xFF));
    
    scc(SDL_SetTextureAlphaMod(font,
                               colour >> (8 * 0) & 0xFF));

    scc(SDL_RenderCopy(renderer,
                       font,
                       &source, &destination));
}



void renderText(SDL_Renderer *renderer,
                SDL_Texture *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale){

    size_t n = strlen(text);
    Vec2f pen = pos;

    for(size_t i = 0; i < n; ++i){
        renderChar(renderer,
                   font,
                   text[i],
                   pen,
                   colour,
                   scale);

        pen.x += FONT_CHAR_WIDTH * scale;
    }
}
