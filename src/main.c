
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/extensions/stb_image.h"

#include "include/sdlchecks.h"
#include "include/render.h"
#include "include/data.h"
#include "include/la.h"



const SDL_Colour WINDOW_COLOUR = {.r = 0, .g = 0, .b = 0};
const Uint32 FONT_COLOUR = 0xFFFFFFFF;
const char FONT_PATH[] = "./resources/fonts/oldschool_white.png";

char buffer[BUFFER_CAPACITY];
size_t bufferCursor = 0;
size_t bufferSize = 0;


// Move all these functions to font.h
// ----------------------------------------------------------------------


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



void constructFontSpriteSheet(Font *font, SDL_Renderer *renderer, const char *path){
    SDL_Surface *fontSurface = scp(surfaceFromFile(path));

    font->spriteSheet = scp(SDL_CreateTextureFromSurface(renderer,
                                                         fontSurface));
}



void constructFontGlyphTable(Font *font){

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



Font constructFontFromFile(SDL_Renderer *renderer, const char *path){
    Font font = {0};

    constructFontSpriteSheet(&font, renderer, path);
    constructFontGlyphTable(&font);

    return font;
}

// ----------------------------------------------------------------------




int main(void){

    scc(SDL_Init(SDL_INIT_VIDEO));

    SDL_Window *window = scp(SDL_CreateWindow("WText",
                                             SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                             SCREEN_WIDTH, SCREEN_HEIGHT,
                                             SDL_WINDOW_RESIZABLE));

    SDL_Renderer *renderer = scp(SDL_CreateRenderer(window,
                                                    -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

    Font font = constructFontFromFile(renderer, FONT_PATH);

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
                        } break;
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

                } break;
                
                default: {}
            } // end of switch
        } // end of pollevent loop

        scc(SDL_SetRenderDrawColor(renderer,
                                   WINDOW_COLOUR.r, WINDOW_COLOUR.g, WINDOW_COLOUR.b, 255));
        scc(SDL_RenderClear(renderer)); // clear the renderer
        
        
        renderTextSized(renderer, 
                        &font,
                        buffer,
                        bufferSize,
                        vec2f(0, 0),
                        FONT_COLOUR,
                        FONT_SCALE);

        //renderCursor(renderer);
        
        

        SDL_RenderPresent(renderer);
    } // end of event loop


    SDL_Quit();
	return 0;
}


