#pragma once

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

struct Drawable{
    VBO vbo;
    VAO vao;
    EBO ebo;

    virtual void draw() = 0;
    virtual void init_buffers() = 0;
    virtual void update_buffers() = 0;
    virtual void delete_buffers() = 0;
};