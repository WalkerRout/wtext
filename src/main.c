
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/extensions/stb_image.h"

#include "include/sdlchecks.h"
#include "include/data.h"
#include "include/la.h"



const SDL_Colour windowColour = {.r = 0, .g = 0, .b = 0};
const Uint32 fontColour = 0xFFFFFFFF;
const char fontPath[] = "./resources/fonts/oldschool_white.png";



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



void renderChar(SDL_Renderer *renderer,
                SDL_Texture *font,
                char c,
                Vec2f pos,
                Uint32 colour,
                float scale){

    const size_t index = c - 32;
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

    SDL_SetTextureColorMod(font, 
                           colour >> (8 * 2) & 0xFF,
                           colour >> (8 * 1) & 0xFF,
                           colour >> (8 * 0) & 0xFF);

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



int main(void){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    SDL_Surface *fontSurface = surfaceFromFile(fontPath);
    
    SDL_Texture *fontTexture = scp(SDL_CreateTextureFromSurface(renderer, 
                                                                fontSurface));

    SDL_Rect fontRect = {
        .x = 0,
        .y = 0,
        .w = fontSurface->w,
        .h = fontSurface->h
    };

    enum {STOPPED, RUNNING} state = RUNNING;
    while(state){
        SDL_Event event = {0}; // all to 0

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    state = STOPPED;
                    break;
                
                default: {}
            } // end of switch
        } // end of pollevent loop

        scc(SDL_SetRenderDrawColor(renderer,
                                   windowColour.r, windowColour.g, windowColour.b, 255));
        scc(SDL_RenderClear(renderer)); // clear the renderer

        SDL_Rect outputRect = {
            .x = 0,
            .y = 0,
            .w = fontRect.w * 5,
            .h = fontRect.h * 5
        };

        scc(SDL_RenderCopy(renderer,
                           fontTexture,
                           &outputRect, &outputRect));

        SDL_RenderPresent(renderer);
    } // end of event loop


    SDL_Quit();
	return 0;
}


