#pragma once

#include "glad/glad.h"

struct ShaderProgram{
    ShaderProgram();
    void addShader(char const* filename, GLenum type);
    void link();
    void use();
    void destroy();

    private:
        GLuint program;
};