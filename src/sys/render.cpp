#include <vector>
#include <iostream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "render.hpp"


namespace CDP{
RenderStorage::RenderStorage(std::vector<GLfloat>& _v, std::vector<GLuint>& _ib, uint32_t& _li) 
    : vertices{_v}, index_buff{_ib}, last_index{_li}{}

RenderSystem::RenderSystem(const char* name_w, uint32_t width_w, uint32_t height_w, RenderMode rm = RenderMode::STATIC) 
    : window_name{name_w}, window_width{width_w}, window_height{height_w}, render_mode{rm} {

}

void RenderSystem::init(){
    // Initialize glfw flag values
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create glfw window, handling the possible errors
    window = glfwCreateWindow(window_width, window_height, window_name/*"Collision Detection Learning Program"*/, NULL, NULL);
    if(window == NULL){
        std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // ImGui initialization and link with the window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();
    
    // Load opengl and set the viewport to the size of the window
    gladLoadGL();
    glViewport(0, 0, window_width, window_height);


    // Read and load the shaders into the program
    shader_P.addShader("shader.vert", GL_VERTEX_SHADER);
    shader_P.addShader("shader.frag", GL_FRAGMENT_SHADER);
    shader_P.link();

    // Bind the vertex array
    vao.bind();
    // Load the vertices data into the vertex buffer and the element buffer
    vbo.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
    ebo.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
    
    // Set the vertex array attributes needed to read the shaderse propperly
    vao.addAttrib(vbo, 0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    vao.addAttrib(vbo, 1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    
    // Unbind all for more safety
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    // Draw the first background
    glClearColor(background_color.r_f, background_color.g_f, background_color.b_f, background_color.a_f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap to the other buffer to start rendering there
    glfwSwapBuffers(window);
}


void RenderSystem::update(){
    // Draw the background each frame
    glClearColor(background_color.r_f, background_color.g_f, background_color.b_f, background_color.a_f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the programs where the shaders were loaded
    shader_P.use();
    vao.bind();

    // Draw the vertices following the element array buffer
    glDrawElements(GL_TRIANGLES, index_buff.size(), GL_UNSIGNED_INT, 0);

    // // Draw the UI
    // drawUI();

    // Swap to the other buffer to start rendering there
    glfwSwapBuffers(window);

    // Manage the events of the GLFWwindow
    glfwPollEvents();

    // If the mode of the system is dynamic, delete all the vertices data
    if(render_mode == DYNAMIC){
        vertices.clear();
        index_buff.clear();
        last_index = 0;
    }
}

void RenderSystem::end(){
    // Delete the VAO, the VBO, the EBO and the program itself
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader_P.destroy();

    // Destroy and close the window
    glfwDestroyWindow(window);
    glfwTerminate();
}

void RenderSystem::drawUI(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Window Tittle");
    ImGui::Text("Window text!");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool RenderSystem::isOpen(){
    return !glfwWindowShouldClose(window);
}

template <typename T>
void RenderSystem::draw(T drawable){
    drawable.draw(RenderStorage(vertices, index_buff, last_index));
}

} // namespace CDP