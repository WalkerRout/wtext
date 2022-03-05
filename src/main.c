
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "include/sdlchecks.h"
#include "include/render.h"
#include "include/font.h"
#include "include/data.h"
#include "include/la.h"


const char FONT_PATH[] = "./resources/fonts/oldschool.png";
//const char FONT_PATH[] = "./resources/fonts/cellphone.png";
//const char FONT_PATH[] = "./resources/fonts/futuristic.png";

char buffer[BUFFER_CAPACITY];
size_t bufferCursor = 0;
size_t bufferSize = 0;



int main(void){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    Font font = {0};
    constructFont(&font, renderer, FONT_PATH);

    enum {STOPPED, RUNNING} state = RUNNING;
    while(state){
        SDL_Event event = {0}; // all to 0

        while(SDL_PollEvent(&event)){

            switch(event.type){
                case SDL_QUIT: {
                    state = STOPPED;
                } break;

                case SDL_KEYDOWN: {
                    switch(event.key.keysym.sym){
                        case SDLK_BACKSPACE: {
                            if(bufferSize > 0){
                                bufferSize -= 1;
                            }

                            bufferCursor = bufferSize;
                        } break;

                        case SDLK_RIGHT: {
                            if(bufferCursor >= 0){
                                ++bufferCursor;
                            }
                        } break;

                        case SDLK_LEFT: {
                            if(bufferCursor > 0){
                                --bufferCursor;
                            }
                        } break;

                        default: {}

                    }

                } break;
                
                case SDL_TEXTINPUT: {
                    size_t textSize = strlen(event.text.text);
                    const size_t freeSpace = BUFFER_CAPACITY - bufferSize;

                    // append text into buffer
                    if(textSize > freeSpace){
                        textSize = freeSpace;
                    }

                    memcpy(buffer + bufferSize, event.text.text, textSize);
                    bufferSize += textSize;
                    bufferCursor = bufferSize;
                } break;
                
                default: {}
            } // end of switch
        } // end of pollevent loop

        scc(SDL_SetRenderDrawColor(renderer,
                                   UNHEX_UINT32_ARGS(WINDOW_COLOUR)));
        scc(SDL_RenderClear(renderer)); // clear the renderer
        
        
        renderTextSized(renderer, 
                        &font,
                        buffer,
                        bufferSize,
                        vec2f(0, 0),
                        FONT_COLOUR,
                        FONT_SCALE);

        renderCursor(renderer, 
                     &bufferCursor);

        SDL_RenderPresent(renderer);
    } // end of event loop

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    
    SDL_Quit(); //atexit();
	return 0;
}


