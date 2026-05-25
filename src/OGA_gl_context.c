//
//      Jaidev Bormann
//


#include <stdlib.h>
#include <glad/glad.h>
#include <SDL3/SDL_video.h>

#include "OGA_GL_context.h"
#include "OGA_error.h"
#include "OGA_types.h"


struct OGA_gl_context_impl_ {

        SDL_GLContext   sdl_gl_context;
        SDL_Window*     ref_sdl_window;

};


s_byte OGA_gl_context_hire(struct OGA_gl_context* gl_context) {

        if (!gl_context) {

                OGA_error_set_(OGA_GL_CONTEXT_BAD_POINTER, "OGA_gl_context::OGA_gl_context_hire | Provided struct was NULL");

                return OGA_FAILURE;

        }

        if (gl_context->impl_) {

                OGA_error_set_(OGA_GL_CONTEXT_IMPL_ALLOC_ALREADY, "OGA_gl_context::OGA_gl_context_hire | Provided struct already hired");

                return OGA_FAILURE;

        }

        gl_context->impl_ = calloc(1, sizeof(struct OGA_gl_context_impl_));

        if (!gl_context->impl_) {

                OGA_error_set_(OGA_GL_CONTEXT_IMPL_ALLOC_FAILURE, "OGA_gl_context::OGA_gl_context_hire | PIMPL failed allocation");

                return OGA_FAILURE;

        }


        struct OGA_gl_context_impl_* impl       = gl_context->impl_;
        u_int16 window_id                       = gl_context->window->id;


        impl->ref_sdl_window = SDL_GetWindowFromID(window_id);

        if (!impl->ref_sdl_window) {    // can never be too sure.

                OGA_error_set_(OGA_GL_CONTEXT_SDL_REF_WINDOW_NO_ID, "OGA_gl_context::OGA_gl_context_hire | Tried to reference an SDL3 window with no ID | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }


        impl->sdl_gl_context = SDL_GL_CreateContext(impl->ref_sdl_window);

        if (!impl->sdl_gl_context) {

                OGA_error_set_(OGA_GL_CONTEXT_SDL_CREATION_FAILURE, "OGA_gl_context::OGA_gl_context_hire | Failed to create SDL3 GLContext | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }

        if (!SDL_GL_MakeCurrent(impl->ref_sdl_window, impl->sdl_gl_context)) {

                OGA_error_set_(OGA_GL_CONTEXT_SDL_WINDOW_BINDING_FAILURE, "OGA_gl_context::OGA_gl_context_hire | Failed to bind the given reference window to the SDL3 GLContext | SDL: %s", SDL_GetError());

                return OGA_FAILURE;

        }

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {

                OGA_error_set_(OGA_GL_CONTEXT_GLAD_LOAD_FAILURE, "OGA_gl_context::OGA_gl_context_hire | Failed to load GLAD");

                return OGA_FAILURE;

        }


        return OGA_SUCCESS;

}

void OGA_gl_context_fire(struct OGA_gl_context* gl_context) {

        if (!gl_context || !gl_context->impl_ || !gl_context->impl_->sdl_gl_context)
                return;

        SDL_GL_DestroyContext(gl_context->impl_->sdl_gl_context);

        free(gl_context->impl_);
        gl_context->impl_ = NULL;

}

void OGA_gl_context_swap(struct OGA_gl_context* gl_context) { 
        
        if (!gl_context || !gl_context->impl_)
                return;

        SDL_GL_SwapWindow(gl_context->impl_->ref_sdl_window);

}