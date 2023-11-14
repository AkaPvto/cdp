// g++ -c main.cpp && g++ -o main main.o libglfw.so.3 libglad.a libimgui.a 

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <cmath>

#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define RED_CREAM           205_u8, 70_u8 , 56_u8 , 255_u8

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;"
"out vec3 color;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   color = aColor;"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0f);\n"
"}\n\0";


uint8_t operator ""_u8(unsigned long long i){
    return uint8_t(i);
}
struct Color{
    uint8_t r{},g{},b{},a{};
    float   r_f{},g_f{},b_f{},a_f{};
    
    Color() = default;
    
    Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a) :
    r{_r}, g{_g}, b{_b}, a{_a}, r_f{_r/255.0f}, g_f{_g/255.0f}, b_f{_b/255.0f}, a_f{_a/255.0f} {}

    Color(float _r,float _g, float _b,float _a) :
    r{uint8_t(_r*255)}, g{uint8_t(_g*255)}, b{uint8_t(_b*255)}, a{uint8_t(_a*255)}, r_f{_r}, g_f{_g}, b_f{_b}, a_f{_a} {}
};
int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(1280, 720, "Collision Detection Learning Program", NULL, NULL);
    if(window == NULL){
        std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    gladLoadGL();

    glViewport(0, 0, 1280, 720);

    Color red(RED_CREAM);
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0,     red.r_f, red.g_f, red.b_f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0,      red.r_f, red.g_f, red.b_f,
        0.0f, 0.5f * float(sqrt(3)) *2 / 3, 0.0,    red.r_f, red.g_f, red.b_f
    };

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    
    glBindVertexArray(VAO);
    // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Color bkg(BACKGROUND_COLOR);

    while(!glfwWindowShouldClose(window)){
        glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Window Tittle");
        ImGui::Text("Window text!");
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}




