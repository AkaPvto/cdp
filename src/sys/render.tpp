#include "render.hpp"

namespace CDP{

template <typename DrawType>
void RenderSystem::update(DrawType* draw_list, int size){
    // Rendering
    glClearColor(   background_color.r_f,
                    background_color.g_f,
                    background_color.b_f,
                    background_color.a_f );
    glClear(GL_COLOR_BUFFER_BIT);
    shader_p.use();

    // Iterate through the list and call draw function
    void* list_end = draw_list+size;
    while(draw_list < list_end){
        draw_list->draw();
        draw_list++;
    }
}

} // namespace CDP