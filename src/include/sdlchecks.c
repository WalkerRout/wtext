
#include "sdlchecks.h"



// SDL Check Pointer -> scp
void* scp(void *ptr){
    if(ptr == NULL){
        fprintf(stderr, "SDL ERROR: %s\n",
                SDL_GetError());
        exit(1);
    }
    return ptr;
}


// SDL Check Code -> scc
int scc(int code){
    if(code < 0){
        fprintf(stderr, "SDL ERROR: %s\n",
                SDL_GetError());
        exit(1);
    }
    return 0;
}