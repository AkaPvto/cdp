#include "core.hpp"
#include "algorithm/aabb.hpp"

#include <imgui/src/imgui.h>
#include <imgui/src/imgui_impl_glfw.h>
#include <imgui/src/imgui_impl_opengl3.h>
#include <iostream>

namespace CDP{


void Core::update_ui(){
    // User Interfaze management
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::PushFont(render.getHeavyFont());
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

}

void Core::render_ui(){
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Core::AABB_ui(){
    ImGui::Separator();
    ImGui::SetWindowFontScale(1.2f);
    ImGui::Text("AABB Collision Detection Algorithm");
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PushFont(render.getLightFont());


    assert(algth != nullptr);
    AABB& algorithm_AABB = *dynamic_cast<AABB*>(algth);

    if(ImGui::Checkbox("Show algorithm", &draw_algth)) algorithm_AABB.update_all(render, renderPol, renderSegment, renderLine, polygons.at(0), polygons.at(1));

    if(draw_algth){
        ImGui::Indent(20.0f);
        
        ImGui::Checkbox("Axis-independent visualizer", &algorithm_AABB.intersection_F);

        ImGui::Checkbox("Polygon proyections", &algorithm_AABB.projection_F);

        ImGui::Checkbox("Labeled axis", &algorithm_AABB.labels_F);

        ImGui::Unindent(20.0f);

        algorithm_AABB.update(render, renderPol, renderSegment, renderLine, polygons.at(0), polygons.at(1));
    }

    ImGui::PopFont();
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
