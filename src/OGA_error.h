//
//      Jaidev Bormann
//


#ifndef OGA_ERROR_H_
#define OGA_ERROR_H_


#include "OGA_types.h"


typedef enum {

        OGA_FAILURE = -1,
        OGA_SUCCESS = 0,

        //      OGA_context
        OGA_CONTEXT_BAD_SDL_INIT,

        //      OGA_window
        OGA_WINDOW_BAD_POINTER,
        OGA_WINDOW_BAD_IMPL_ALLOC,
        OGA_WINDOW_BAD_POSITION,
        OGA_WINDOW_BAD_CREATION,
        OGA_WINDOW_BAD_GLCONTEXT_CREATION,
        OGA_WINDOW_BAD_GLCONTEXT_BIND,
        OGA_WINDOW_BAD_GLAD_LOAD,



} OGA_errors;


void OGA_show_error     (constptr_string message);
void OGA_SDL_show_error (void);


#endif // OGA_ERROR_H_