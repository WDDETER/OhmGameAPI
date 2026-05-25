//
//      Jaidev Bormann
//


#ifndef OGA_WINDOW_FLAGS_H_
#define OGA_WINDOW_FLAGS_H_


#include "OGA_types.h"


#define OGA_FLAG_WINDOW_NONE                         0
#define OGA_FLAG_WINDOW_FULLSCREEN                   (1 << 0)
#define OGA_FLAG_WINDOW_MAXIMIZED                    (1 << 1)
#define OGA_FLAG_WINDOW_MINIMIZED                    (1 << 2)
#define OGA_FLAG_WINDOW_RESIZEABLE                   (1 << 3)
#define OGA_FLAG_WINDOW_BORDERLESS                   (1 << 4)
#define OGA_FLAG_WINDOW_INPUT_FOCUS                  (1 << 5)
#define OGA_FLAG_WINDOW_MOUSE_FOCUS                  (1 << 6)
#define OGA_FLAG_WINDOW_HIGH_DPI                     (1 << 7)
#define OGA_FLAG_WINDOW_OPENGL                       (1 << 8)
#define OGA_FLAG_WINDOW_OCCLUDED                     (1 << 9)
#define OGA_FLAG_WINDOW_HIDDEN                       (1 << 10)
#define OGA_FLAG_WINDOW_MOUSE_GRABBED                (1 << 11)
#define OGA_FLAG_WINDOW_MODAL                        (1 << 12)
#define OGA_FLAG_WINDOW_MOUSE_CAPTURE                (1 << 13)
#define OGA_FLAG_WINDOW_MOUSE_RELATIVE_MODE          (1 << 14)
#define OGA_FLAG_WINDOW_ALWAYS_ON_TOP                (1 << 15)
#define OGA_FLAG_WINDOW_UTILITY                      (1 << 16)
#define OGA_FLAG_WINDOW_TOOLTIP                      (1 << 17)
#define OGA_FLAG_WINDOW_POPUP_MENU                   (1 << 18)
#define OGA_FLAG_WINDOW_KEYBOARD_GRABBED             (1 << 19)
#define OGA_FLAG_WINDOW_FILL_DOCUMENT                (1 << 20)
#define OGA_FLAG_WINDOW_TRANSPARENT                  (1 << 21)
#define OGA_FLAG_WINDOW_NOT_FOCUSABLE                (1 << 22)


typedef u_int32 OGA_window_flags;


#endif