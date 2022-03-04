
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "extensions/stb_image.h"

#include "font.h"
#include "sdlchecks.h"



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

    return SDL_CreateRGBSurfaceFrom((void*) pixels,
                                    width, height,
                                    depth,
                                    pitch,
                                    rmask, gmask, bmask, amask);
}



void constructFont(Font *font, SDL_Renderer *renderer, const char *path){

    SDL_Surface *fontSurface = scp(surfaceFromFile(path));

    font->spriteSheet = scp(SDL_CreateTextureFromSurface(renderer,
                                                         fontSurface));

    SDL_FreeSurface(fontSurface);

    for(size_t ascii = ASCII_DISPLAY_LOW; ascii <= ASCII_DISPLAY_HIGH; ascii++){
        const size_t index = ascii - ASCII_DISPLAY_LOW;

        const size_t row = index / FONT_COLS;
        const size_t col = index % FONT_COLS;

        font->glyphTable[index] = (SDL_Rect) {
            .x = col * FONT_CHAR_WIDTH,
            .y = row * FONT_CHAR_HEIGHT,
            .w = FONT_CHAR_WIDTH,
            .h = FONT_CHAR_HEIGHT
        };
    }
}
