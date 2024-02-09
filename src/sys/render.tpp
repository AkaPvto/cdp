#include "render.hpp"

namespace CDP{

template <typename DrawType>
void RenderSystem::draw(DrawType* draw_list, int size){
    // Use the render shaders linked
    shader_p.use();

    // Iterate through the list and call draw function
    void* list_end = draw_list+size;
    while(draw_list < list_end){
        draw_list->draw();
        draw_list++;
    }
}

} // namespace CDP