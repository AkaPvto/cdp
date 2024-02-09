#pragma once

#include "glad/glad.h"

struct ShaderProgram{
    void init();
    void addShader(char const* filename, GLenum type);
    void link();
    void use();
    GLint getUniform(char const* name);
    void destroy();

    private:
        GLuint program;
};