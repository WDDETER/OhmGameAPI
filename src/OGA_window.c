//
//      Jaidev Bormann
//


#include <string.h>               // for memset
#include <stdlib.h>

#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL3/SDL_video.h>

#include "OGA_window.h"
#include "OGA_window_flags.h"
#include "OGA_error.h"
#include "OGA_types.h"


struct _OGA_window_impl {

        SDL_Window*     sdl_window;
        SDL_WindowFlags sdl_window_flags;
        SDL_GLContext   gl_context;

};

struct _OGA_flag_map {          // I really don't know how to feel about this, it's honestly kind of the only way.
                                // just putting this whole flag system in OGA_window gives major icks.
        u_int32 oga_flag;
        u_int64 sdl_flag;

};


static struct _OGA_flag_map _flag_table[] = {

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

static void _OGA_window_flags_unpack(OGA_window_flags oga_flags, u_int64* sdl_flags);


u_byte OGA_window_hire(struct OGA_window* window) {

        if (!window) {

                OGA_show_error("OGA_Window BAD POINTER");

                return OGA_WINDOW_BAD_POINTER;

        }


        window->_impl = calloc(1, sizeof(struct _OGA_window_impl));     // reminder: this sets sdl_window_flags in memory to 0.
                                                                        // same thing as if I had did sdl_window_flags = 0, but this is safer.
        if (!window->_impl) {

                OGA_show_error("OGA_Window BAD IMPL ALLOCATION");

                return OGA_WINDOW_BAD_IMPL_ALLOC;

        }

        
        bool window_gl_context_status   = true;
        bool window_bind_status         = true;
        bool window_position_status     = true;
        int glad_load_status            = 1;


        _OGA_window_flags_unpack(window->flags, &window->_impl->sdl_window_flags);

        window->_impl->sdl_window = SDL_CreateWindow(window->title, window->width, window->height, window->_impl->sdl_window_flags);

        if (!window->_impl->sdl_window)
                goto window_creation_failure;


        window->_impl->gl_context = SDL_GL_CreateContext(window->_impl->sdl_window);

        if (!window->_impl->gl_context)
                goto gl_context_creation_failure;


        window_bind_status = SDL_GL_MakeCurrent(window->_impl->sdl_window, window->_impl->gl_context);

        if (!window_bind_status)
                goto window_bind_failure;


        window_position_status = SDL_SetWindowPosition(window->_impl->sdl_window, window->x, window->y);

        if (!window_position_status) 
                goto window_position_failure;


        glad_load_status = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

        if (!glad_load_status)
                goto glad_load_failure;


        return OGA_SUCCESS;


        glad_load_failure:
                OGA_show_error("OGA_window BAD GLAD LOAD");

        window_position_failure:
        window_bind_failure:
                SDL_GL_DestroyContext(window->_impl->gl_context);
        gl_context_creation_failure:
                window_gl_context_status = false;
                SDL_DestroyWindow(window->_impl->sdl_window);

        window_creation_failure:
                OGA_SDL_show_error();

                free(window->_impl);
                window->_impl = NULL;

                if (!glad_load_status)          return OGA_WINDOW_BAD_GLAD_LOAD;
                if (!window_position_status)    return OGA_WINDOW_BAD_POSITION;
                if (!window_bind_status)        return OGA_WINDOW_BAD_GLCONTEXT_BIND;
                if (!window_gl_context_status)  return OGA_WINDOW_BAD_GLCONTEXT_CREATION;
                
                return OGA_WINDOW_BAD_CREATION;


        return OGA_FAILURE;

}

void OGA_window_fire(struct OGA_window* window) {

        if (!window || !window->_impl)
                return;

        if (!window->_impl->sdl_window || !window->_impl->gl_context)
                return;

        SDL_GL_DestroyContext   (window->_impl->gl_context);
        SDL_DestroyWindow       (window->_impl->sdl_window);

        free(window->_impl);

        window->_impl = NULL;

}

void OGA_window_swap(struct OGA_window* window) {

        if (!window || !window->_impl || !window->_impl->sdl_window)
                return;

        SDL_GL_SwapWindow(window->_impl->sdl_window);

}


static void _OGA_window_flags_unpack(OGA_window_flags oga_flags, u_int64* sdl_flags) {

        size_t flag_table_length = sizeof(_flag_table) / sizeof(_flag_table[0]);

        for (size_t i = 0; i < flag_table_length; i++) {

                if (oga_flags & _flag_table[i].oga_flag)
                        *sdl_flags |= _flag_table[i].sdl_flag;

        }

}