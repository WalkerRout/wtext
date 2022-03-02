
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "include/data.h"


const SDL_Colour windowColour = {.r = 100, .g = 100, .b = 100};

// SDL Check Code -> scc
void scc(int code){
    if(code < 0){
        fprintf(stderr, "SDL ERROR: %s\n",
                SDL_GetError());
        
        exit(1);
    }
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



int main(int argc, char *argv[]){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));



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