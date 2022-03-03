
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "include/sdlchecks.h"
#include "include/render.h"
#include "include/data.h"
#include "include/la.h"



const SDL_Colour WINDOW_COLOUR = {.r = 0, .g = 0, .b = 0};
const Uint32 FONT_COLOUR = 0x00FF00DD;
const char FONT_PATH[] = "./resources/fonts/oldschool_white.png";



int main(void){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    Font font = fontLoadFromFile(FONT_PATH, renderer);

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
                                   WINDOW_COLOUR.r, WINDOW_COLOUR.g, WINDOW_COLOUR.b, 255));
        scc(SDL_RenderClear(renderer)); // clear the renderer
        
        /*
        renderText(renderer, 
                   &font,
                   "Slugma Nuts",
                   vec2f(0, 0),
                   FONT_COLOUR,
                   5.0f);
        */
       
        SDL_RenderPresent(renderer);
    } // end of event loop


    SDL_Quit();
	return 0;
}


