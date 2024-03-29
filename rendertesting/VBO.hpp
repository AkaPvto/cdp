#pragma once

#include "glad/glad.h"

// Vertex Buffer Object
struct VBO{
    VBO();

    void insert(GLfloat* vertices, GLsizeiptr size);
    void modify(GLfloat* data, GLsizeiptr size, GLintptr offset);
    void bind();
    void unbind();
    void destroy();
    
    private:
        GLuint id;
};