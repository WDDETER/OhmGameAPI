//
//      Jaidev Bormann
//


#include <string.h>             // for memset
#include <SDL3/SDL.h>

#include "OGA_app.h"
#include "OGA_window.h"
#include "OGA_error.h"
#include "OGA_types.h"


#define _OGA_SDL_INIT_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO)


struct OGA_app_ {

        bool            is_running;
        SDL_Event       sdl_event;

};


static struct OGA_app_ OGA_app_singleton_;

// need to check if OGA app has already been called?
s_byte OGA_app_call(void) {

        memset(&OGA_app_singleton_, 0, sizeof(struct OGA_app_));


        if (!SDL_Init(_OGA_SDL_INIT_FLAGS)) {

                OGA_error_set_(OGA_APP_SDL_INIT_FAILURE, "OGA_app::OGA_app_call | Failed to initalize SDL3 | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }

        OGA_app_singleton_.is_running = true;


        return OGA_SUCCESS;

}

// need to check if the app was already closed.
void OGA_app_close(void) {

        SDL_Quit();

}

void OGA_app_poll(void) {

        while (SDL_PollEvent(&OGA_app_singleton_.sdl_event)) {

                if (OGA_app_singleton_.sdl_event.type == SDL_EVENT_QUIT)
                        OGA_app_singleton_.is_running = false;

        }

}

bool OGA_app_running(void) { return OGA_app_singleton_.is_running; }