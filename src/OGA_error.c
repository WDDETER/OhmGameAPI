//
//      Jaidev Bormann
//


#include <stdio.h>
#include <SDL3/SDL_error.h>

#include "OGA_error.h"
#include "OGA_types.h"


void OGA_show_error(constptr_string message) {

        printf("OGA Error: %s\n", message);
        fflush(stdout);

}

void OGA_SDL_show_error(void) {

        constptr_string message = SDL_GetError();

        printf("SDL Error: %s\n", message);
        fflush(stdout);

}