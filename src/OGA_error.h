//
//      Jaidev Bormann
//


#ifndef OGA_ERROR_H_
#define OGA_ERROR_H_


#include "OGA_types.h"


#define OGA_ERROR_NONE NULL


typedef enum {

        OGA_FAILURE = -1,
        OGA_SUCCESS = 0,

        //      OGA App
        OGA_APP_SDL_INIT_FAILURE,

        //      OGA Window
        OGA_WINDOW_BAD_POINTER,
        OGA_WINDOW_IMPL_ALLOC_ALREADY,
        OGA_WINDOW_IMPL_ALLOC_FAILURE,
        OGA_WINDOW_SDL_CREATION_FAILURE,
        OGA_WINDOW_SDL_POSITIONING_FAILURE,

        //      OGA GLContext
        OGA_GL_CONTEXT_BAD_POINTER,
        OGA_GL_CONTEXT_IMPL_ALLOC_ALREADY,
        OGA_GL_CONTEXT_IMPL_ALLOC_FAILURE,
        OGA_GL_CONTEXT_SDL_REF_WINDOW_NO_ID,
        OGA_GL_CONTEXT_SDL_CREATION_FAILURE,
        OGA_GL_CONTEXT_SDL_WINDOW_BINDING_FAILURE,
        OGA_GL_CONTEXT_GLAD_LOAD_FAILURE,

} OGA_errors;


void            OGA_error_clear         (void);
OGA_errors      OGA_error_get_code      (void); 
constptr_string OGA_error_get_message   (void);
void            OGA_error_set_          (OGA_errors code, constptr_string format, ...);


#endif // OGA_ERROR_H_