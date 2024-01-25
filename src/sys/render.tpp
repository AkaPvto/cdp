#include "render.hpp"
#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"

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

    
    // User Interfaze management
    // UI.update(); // Create a manager class for the user interface using the imgui library
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Window Tittle");
    ImGui::Text("Window text!");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    // Swap the buffer for rendering the next frame and call the events poll
    glfwSwapBuffers(window);
    glfwPollEvents();

}

} // namespace CDP