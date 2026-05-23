//
//      Jaidev Bormann
//


#include <stddef.h>
#include <glad/glad.h>

#include "OGA_context.h"
#include "OGA_window.h"
#include "OGA_types.h"


static constptr_string vertex_shader_source = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
static constptr_string fragment_shader_source = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";


int main(void) {

        OGA_context_call();


        struct OGA_window window = {

                .title          = "OhmGameAPI Application",
                .width          = 640,
                .height         = 480,
                .x              = 100,
                .y              = 100,
                .flags          = OGA_FLAG_WINDOW_OPENGL | OGA_FLAG_WINDOW_BORDERLESS | OGA_FLAG_WINDOW_MAXIMIZED | OGA_FLAG_WINDOW_RESIZEABLE,

        };

        OGA_window_hire(&window);


        unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource  (vertex_shader, 1, &vertex_shader_source, NULL);
        glCompileShader (vertex_shader);

        unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource  (fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader (fragment_shader);

        unsigned int shader_program = glCreateProgram();
        glAttachShader  (shader_program, vertex_shader);
        glAttachShader  (shader_program, fragment_shader);
        glLinkProgram   (shader_program);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);


        float32 vertices[] = {

                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f

        };

        unsigned int indices[] = {
        
                0, 1, 2,
                0, 2, 3

        };

        unsigned int vbo;
        unsigned int vao;
        unsigned int ebo;

        glGenVertexArrays       (1, &vao);
        glGenBuffers            (1, &vbo);
        glGenBuffers            (1, &ebo);
        

        glBindVertexArray       (vao);

        glBindBuffer    (GL_ARRAY_BUFFER, vbo);
        glBufferData    (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer    (GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData    (GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer           (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float32), NULL);
        glEnableVertexAttribArray       (0);


        glBindBuffer            (GL_ARRAY_BUFFER, 0);
        glBindVertexArray       (0);
        glBindBuffer            (GL_ELEMENT_ARRAY_BUFFER, 0);


        glClearColor(0.4f, 0.3f, 0.2f, 1.0f);


        while (OGA_context_running()) {

                glClear(GL_COLOR_BUFFER_BIT);

                glUseProgram(shader_program);
                glBindVertexArray(vao);

                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


                OGA_window_swap(&window);
                OGA_context_poll();

        }

        glDeleteVertexArrays    (1, &vao);
        glDeleteBuffers         (1, &vbo);
        glDeleteBuffers         (1, &ebo);
        glDeleteProgram         (shader_program);

        OGA_window_fire         (&window);
        OGA_context_close       ();

        return 0;

}