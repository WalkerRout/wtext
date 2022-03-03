
#ifndef SDLCHECKS_H
#define SDLCHECKS_H

#include <stdio.h>
#include <SDL2/SDL.h>


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

#endif