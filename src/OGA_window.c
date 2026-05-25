//
//      Jaidev Bormann
//


#include <stdlib.h>
#include <glad/glad.h>
#include <SDL3/SDL_video.h>

#include "OGA_window.h"
#include "OGA_window_flags.h"
#include "OGA_error.h"
#include "OGA_types.h"


struct OGA_flag_map_ {

        u_int32 oga_flag;
        u_int64 sdl_flag;

};

struct OGA_window_impl_ {

        SDL_Window*     sdl_window;
        SDL_WindowFlags sdl_window_flags;

};


static struct OGA_flag_map_ _flag_table[] = {

        { OGA_FLAG_WINDOW_FULLSCREEN,           SDL_WINDOW_FULLSCREEN           },
        { OGA_FLAG_WINDOW_MAXIMIZED,            SDL_WINDOW_MAXIMIZED            },
        { OGA_FLAG_WINDOW_MINIMIZED,            SDL_WINDOW_MINIMIZED            },
        { OGA_FLAG_WINDOW_RESIZEABLE,           SDL_WINDOW_RESIZABLE            },
        { OGA_FLAG_WINDOW_BORDERLESS,           SDL_WINDOW_BORDERLESS           },
        { OGA_FLAG_WINDOW_INPUT_FOCUS,          SDL_WINDOW_INPUT_FOCUS          },
        { OGA_FLAG_WINDOW_MOUSE_FOCUS,          SDL_WINDOW_MOUSE_FOCUS          },
        { OGA_FLAG_WINDOW_HIGH_DPI,             SDL_WINDOW_HIGH_PIXEL_DENSITY   },
        { OGA_FLAG_WINDOW_OPENGL,               SDL_WINDOW_OPENGL               },
        { OGA_FLAG_WINDOW_OCCLUDED,             SDL_WINDOW_OCCLUDED             },
        { OGA_FLAG_WINDOW_HIDDEN,               SDL_WINDOW_HIDDEN               },
        { OGA_FLAG_WINDOW_MOUSE_GRABBED,        SDL_WINDOW_MOUSE_GRABBED        },
        { OGA_FLAG_WINDOW_MODAL,                SDL_WINDOW_MODAL                },
        { OGA_FLAG_WINDOW_MOUSE_CAPTURE,        SDL_WINDOW_MOUSE_CAPTURE        },
        { OGA_FLAG_WINDOW_MOUSE_RELATIVE_MODE,  SDL_WINDOW_MOUSE_RELATIVE_MODE  },
        { OGA_FLAG_WINDOW_ALWAYS_ON_TOP,        SDL_WINDOW_ALWAYS_ON_TOP        },
        { OGA_FLAG_WINDOW_UTILITY,              SDL_WINDOW_UTILITY              },
        { OGA_FLAG_WINDOW_TOOLTIP,              SDL_WINDOW_TOOLTIP              },
        { OGA_FLAG_WINDOW_POPUP_MENU,           SDL_WINDOW_POPUP_MENU           },
        { OGA_FLAG_WINDOW_KEYBOARD_GRABBED,     SDL_WINDOW_KEYBOARD_GRABBED     },
        { OGA_FLAG_WINDOW_FILL_DOCUMENT,        SDL_WINDOW_FILL_DOCUMENT        },
        { OGA_FLAG_WINDOW_TRANSPARENT,          SDL_WINDOW_TRANSPARENT          },
        { OGA_FLAG_WINDOW_NOT_FOCUSABLE,        SDL_WINDOW_NOT_FOCUSABLE        },

};

static void OGA_window_flags_unpack_(const OGA_window_flags oga_flags, SDL_WindowFlags* sdl_flags);


s_byte OGA_window_hire(struct OGA_window* window) {

        if (!window) {

                OGA_error_set_(OGA_WINDOW_BAD_POINTER, "OGA_window::OGA_window_hire | Provided struct was NULL");

                return OGA_FAILURE;

        }

        if (window->impl_) {

                OGA_error_set_(OGA_WINDOW_IMPL_ALLOC_ALREADY, "OGA_window::OGA_window_hire | Provided struct already hired");

                return OGA_FAILURE;

        }

        window->impl_ = calloc(1, sizeof(struct OGA_window_impl_));

        if (!window->impl_) {

                OGA_error_set_(OGA_WINDOW_IMPL_ALLOC_FAILURE, "OGA_window::OGA_window_hire | PIMPL failed allocation");

                return OGA_FAILURE;

        }


        struct OGA_window_impl_* impl = window->impl_;


        OGA_window_flags_unpack_(window->flags, &impl->sdl_window_flags);

        impl->sdl_window = SDL_CreateWindow(window->title, window->width, window->height, impl->sdl_window_flags);

        if (!impl->sdl_window) {

                OGA_error_set_(OGA_WINDOW_SDL_CREATION_FAILURE, "OGA_window::OGA_window_hire | Failed to create SDL3 window | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }

        if (!SDL_SetWindowPosition(impl->sdl_window, window->x, window->y)) {

                OGA_error_set_(OGA_WINDOW_SDL_POSITIONING_FAILURE, "OGA_window::OGA_window_hire | Failed to position SDL3 window | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }


        window->id = SDL_GetWindowID(impl->sdl_window);


        return OGA_SUCCESS;

}

void OGA_window_fire(struct OGA_window* window) {

        if (!window || !window->impl_ || !window->impl_->sdl_window)
                return;

        SDL_DestroyWindow(window->impl_->sdl_window);

        free(window->impl_);
        window->impl_ = NULL;

}


static void OGA_window_flags_unpack_(const OGA_window_flags oga_flags, SDL_WindowFlags* sdl_flags) {

        size_t flag_table_length = sizeof(_flag_table) / sizeof(_flag_table[0]);

        for (size_t i = 0; i < flag_table_length; i++) {

                if (oga_flags & _flag_table[i].oga_flag)
                        *sdl_flags |= _flag_table[i].sdl_flag;

        }

}