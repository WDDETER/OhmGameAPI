//
//      Jaidev Bormann
//


#ifndef OGA_CONTEXT_H_
#define OGA_CONTEXT_H_


#include "OGA_types.h"


s_byte  OGA_app_call    (void);
void    OGA_app_close   (void);
void    OGA_app_poll    (void);
bool    OGA_app_running (void);


#endif // OGA_CONTEXT_H_