
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include "extensions/stb_image.h"

#include "render.h"




SDL_Surface *surfaceFromFile(const char *path){
    int width, height, n, depth, pitch;

    unsigned char *pixels = stbi_load(path, &width, &height, &n, STBI_rgb_alpha); // STBI_rgb_alpha = 4
    
    if(pixels == NULL){
        fprintf(stderr, "ERROR: could not load file %s: %s\n", 
                path, stbi_failure_reason());
        exit(1);
    }

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bmask = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
    #else // little endian, like x86
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
    #endif

    depth = 32;
    pitch = 4*width;

    return scp(SDL_CreateRGBSurfaceFrom((void*) pixels,
                                        width, height,
                                        depth,
                                        pitch,
                                        rmask, gmask, bmask, amask));
} 



Font fontLoadFromFile(const char *path, SDL_Renderer *renderer){
    Font font = {0};

    SDL_Surface *fontSurface = surfaceFromFile(path);

    // This line is causing a segmentation fault (the scp(...) section, specifically)
    /*
    font.spriteSheet = scp(SDL_CreateTextureFromSurface(renderer, 
                                                        fontSurface));

    SDL_FreeSurface(fontSurface);
    */

    for(size_t ascii = ASCII_DISPLAY_LOW; ascii <= ASCII_DISPLAY_HIGH; ascii++){
        const size_t index = ascii - ASCII_DISPLAY_LOW;

        const size_t row = index % FONT_ROWS;
        const size_t col = index % FONT_COLS;

        font.glyphTable[index] = (SDL_Rect) {
            .x = col * FONT_CHAR_WIDTH,
            .y = row * FONT_CHAR_HEIGHT,
            .w = FONT_CHAR_WIDTH,
            .h = FONT_CHAR_HEIGHT
        };
    }

    return font;
}



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

    assert(c >= ASCII_DISPLAY_LOW && c <= ASCII_DISPLAY_HIGH);
    const size_t index = c - ASCII_DISPLAY_LOW;
    scc(SDL_RenderCopy(renderer,
                       font->spriteSheet,
                       &font->glyphTable[index], &destination));
}



void renderText(SDL_Renderer *renderer,
                Font *font,
                const char *text,
                Vec2f pos,
                Uint32 colour,
                float scale){

    scc(SDL_SetTextureColorMod(font->spriteSheet, 
                               colour >> (8 * 3) & 0xFF,
                               colour >> (8 * 2) & 0xFF,
                               colour >> (8 * 1) & 0xFF));
    
    scc(SDL_SetTextureAlphaMod(font->spriteSheet,
                               colour >> (8 * 0) & 0xFF));

    size_t n = strlen(text);
    Vec2f pen = pos;

    for(size_t i = 0; i < n; i++){
        renderChar(renderer,
                   font,
                   text[i],
                   pen,
                   scale);

        pen.x += FONT_CHAR_WIDTH * scale;
    }
}
