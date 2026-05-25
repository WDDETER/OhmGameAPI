//
//      Jaidev Bormann
//


#ifndef OGA_WINDOW_H_
#define OGA_WINDOW_H_


#include "OGA_window_flags.h"
#include "OGA_types.h"


struct OGA_window_impl_;

struct OGA_window {

        constptr_string                 title;
        const u_int16                   x;
        const u_int16                   y;
        const u_int16                   width;
        const u_int16                   height;
        OGA_window_flags                flags;

        u_int16                         id;

        struct OGA_window_impl_*        impl_;

};


s_byte  OGA_window_hire(struct OGA_window* window);
void    OGA_window_fire(struct OGA_window* window);
void    OGA_window_swap(struct OGA_window* window);


#endif // OGA_WINDOW_H_