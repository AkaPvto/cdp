#pragma once

#include "glad/glad.h"

struct EBO{
    EBO();
    void insert(GLuint* vertices, GLsizeiptr size);
    void modify(GLuint* data, GLsizeiptr size, GLintptr offset);
    void bind();
    void unbind();
    void destroy();

    private:
        GLuint id;
};
