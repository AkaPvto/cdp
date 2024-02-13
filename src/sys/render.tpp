#pragma once

#include "render.hpp"

namespace CDP{

template <typename DrawType>
void RenderSystem::draw(DrawType* draw_list, int size, bool blending){
    // Use the render shaders
    if(blending){
        glEnable(GL_BLEND);
        blend_shader.use();
    }
    else{
        polygon_shader.use();
    }

    // Iterate through the list and call draw function
    void* list_end = draw_list+size;
    while(draw_list < list_end){
        draw_list->draw();
        draw_list++;
    }
    
    glDisable(GL_BLEND);
}

} // namespace CDP