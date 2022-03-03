
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/extensions/stb_image.h"
#include "include/data.h"


const SDL_Colour windowColour = {.r = 100, .g = 100, .b = 100};
const char fontPath[] = "./resources/fonts/oldschool_white.png";



// SDL Check Code -> scc
int scc(int code){
    if(code < 0){
        fprintf(stderr, "SDL ERROR: %s\n",
                SDL_GetError());
        
        exit(1);
    }

    return 0;
}



// SDL Check Pointer -> scp
void* scp(void *ptr){
    if(ptr == NULL){
        fprintf(stderr, "SDL ERROR: %s\n",
                SDL_GetError());
        
        exit(1);
    }

    return ptr;
}



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



int main(void){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    SDL_Surface *fontSurface = surfaceFromFile(fontPath);
    SDL_Texture *texture = scp(SDL_CreateTextureFromSurface(renderer, fontSurface));

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
                                   windowColour.r, windowColour.g, windowColour.b, 
                                   255));
        scc(SDL_RenderClear(renderer)); // clear the renderer
        SDL_RenderPresent(renderer);
    } // end of event loop


    SDL_Quit();
	return 0;
}


