#include "render.hpp"

#include <iostream>

#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"

// Temporal, migrar al input system
#include "types/vector2r.hpp"


#define SHADER_ROUTE "src/render/shaders/"

namespace CDP{

void RenderSystem::init(int width, int height, const char* name){
    // GLFW initialization values/flags
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window creation
    // CHANGE WINDOW TO AN ATTRIBUTE
    window = glfwCreateWindow(width, height, name, NULL, NULL);
    if(window == NULL){
        std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);


    // ImGui initialization and link with the window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = // <== Check if storaging the ImGui ID may be needed in the future 
    ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    // Glad initialization and configuration
    gladLoadGL();

    glViewport(0, 0, width, height);


    // Initialize the shader program
    shader_p.init();
    shader_p.addShader(SHADER_ROUTE"shader.vert", GL_VERTEX_SHADER);
    shader_p.addShader(SHADER_ROUTE"shader.frag", GL_FRAGMENT_SHADER);
    // shader_p.addShader("shader.geom", GL_GEOMETRY_SHADER);
    shader_p.link();
    
}


bool RenderSystem::isOpen(){
    return !glfwWindowShouldClose(window);
}

void RenderSystem::end(){
    // Delete all the vertex objects and the shader program
    shader_p.destroy();

    // Delete the glfw window
    glfwDestroyWindow(window);
    glfwTerminate();
}

void RenderSystem::update_init(){
    // Rendering
    glClearColor(   background_color.r_f,
                    background_color.g_f,
                    background_color.b_f,
                    background_color.a_f );
    glClear(GL_COLOR_BUFFER_BIT);
}

// Swaps the buffer and process the poll events
void RenderSystem::resolve(){
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// Temporal, migrar al input system
void RenderSystem::getMousePos(Vector2r& v){
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    v.x = x;
    v.y = y;

}
bool RenderSystem::isKeyPressed(int key){
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool RenderSystem::isMousePressed(int key){
    return glfwGetMouseButton(window, key) == GLFW_PRESS;
}

void RenderSystem::setBackgroundColor(Color const& c){
    background_color = c;
}
} // namespace CDP
