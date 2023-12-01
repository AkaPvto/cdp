#pragma once

#include "sys/render.hpp"

struct Drawable{
    virtual void draw(RenderStorage const& render) = 0; 
};