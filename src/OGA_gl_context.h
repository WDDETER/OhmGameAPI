//
//      Jaidev Bormann
//


#ifndef OGA_GL_CONTEXT_H_
#define OGA_GL_CONTEXT_H_


#include "OGA_window.h"
#include "OGA_types.h"


struct OGA_gl_context_impl_;


struct OGA_gl_context {

        struct OGA_window*              window;
        struct OGA_gl_context_impl_*    impl_;

};


s_byte  OGA_gl_context_hire(struct OGA_gl_context* gl_context);
void    OGA_gl_context_fire(struct OGA_gl_context* gl_context);
void    OGA_gl_context_swap(struct OGA_gl_context* gl_context);


#endif // OGA_GL_CONTEXT_H_