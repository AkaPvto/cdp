#include "core.hpp"
#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"

namespace CDP{


void Core::update_ui(){
    // User Interfaze management
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Collision Detection Program");
    if(ImGui::Button("AABB")) {
        mode_index = 0;
        delete_shapes();
        initialize(mode_index);
        draw_algth = false;
    }
    ImGui::SameLine();
    if(ImGui::Button("SAT")) {
        mode_index = 1;
        delete_shapes();
        initialize(mode_index);
        draw_algth = false;
    }
    ImGui::SameLine();
    if(ImGui::Button("GJK")) {
        mode_index = 2;
        delete_shapes();
        initialize(mode_index);
        draw_algth = false;
    }

    (this->*mode_ui.at(mode_index))();


    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Core::AABB_ui(){
    ImGui::Text("AABB Collision Detection Algorithm");
    ImGui::Checkbox("Show algorithm", &draw_algth);
}

void Core::SAT_ui(){
    ImGui::Text("SAT Collision Detection Algorithm");
    ImGui::Checkbox("Show algorithm", &draw_algth);
}

void Core::GJK_ui(){
    ImGui::Text("GJK Collision Detection Algorithm");
    ImGui::Checkbox("Show algorithm", &draw_algth);
}



} // namespace CDP
