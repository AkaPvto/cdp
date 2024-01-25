#pragma once

#include "glad/glad.h"

struct VBO;

// Vertex Array Object
struct VAO{
    VAO();
    void addAttrib(GLuint layout, GLuint numComponents, GLenum type, GLint stride, void const* offset);
    void bind();
    void unbind();
    void destroy();
    
    private:
        GLuint id;
};