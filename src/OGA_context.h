//
//      Jaidev Bormann
//


#ifndef OGA_CONTEXT_H_
#define OGA_CONTEXT_H_


#include "OGA_types.h"


u_byte  OGA_context_call   (void);
void    OGA_context_close  (void);
void    OGA_context_poll   (void);
bool    OGA_context_running(void);


#endif // OGA_CONTEXT_H_