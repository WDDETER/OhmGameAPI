//
//      Jaidev Bormann
//


#include <string.h>             // for memset

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>

#include "OGA_context.h"
#include "OGA_window.h"
#include "OGA_error.h"
#include "OGA_types.h"


#define _OGA_SDL_INIT_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)


struct OGA_context {

        bool            is_running;
        SDL_Event       sdl_event;

};


static struct OGA_context _OGA_context_singleton;


u_byte OGA_context_call(void) {

        memset(&_OGA_context_singleton, 0, sizeof(struct OGA_context));


        bool sdl_init_status = SDL_Init(_OGA_SDL_INIT_FLAGS);

        if (!sdl_init_status) {

                OGA_SDL_show_error();

                return OGA_CONTEXT_BAD_SDL_INIT;

        }


        _OGA_context_singleton.is_running = true;


        return OGA_SUCCESS;

}

void OGA_context_close(void) {

        SDL_Quit();

}

void OGA_context_poll(void) {

        while (SDL_PollEvent(&_OGA_context_singleton.sdl_event)) {

                if (_OGA_context_singleton.sdl_event.type == SDL_EVENT_QUIT)
                        _OGA_context_singleton.is_running = false;

        }

}

bool OGA_context_running(void) { return _OGA_context_singleton.is_running; }