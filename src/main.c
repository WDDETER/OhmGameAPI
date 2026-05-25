//
//      Jaidev Bormann
//


#include <glad/glad.h>

#include "OGA_app.h"
#include "OGA_window.h"
#include "OGA_gl_context.h"
#include "OGA_error.h"
#include "OGA_types.h"


int main(void) {

        OGA_app_call();


        struct OGA_window window = {

                .title          = "OhmGameAPI Application",
                .width          = 640,
                .height         = 480,
                .x              = 100,
                .y              = 100,
                .flags          = OGA_FLAG_WINDOW_OPENGL,

        };

        OGA_window_hire(&window);


        struct OGA_gl_context gl_context = { .window = &window };

        OGA_gl_context_hire(&gl_context);


        glClearColor(0.8f, 0.2f, 0.6f, 1.0f);

        while (OGA_app_running()) {

                OGA_app_poll();

                glClear(GL_COLOR_BUFFER_BIT);

                OGA_gl_context_swap(&gl_context);

        }

        
        OGA_gl_context_fire     (&gl_context);
        OGA_window_fire         (&window);
        OGA_app_close           ();


        return 0;

}