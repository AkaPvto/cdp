// g++ -c main.cpp && g++ -o main main.o libglfw.so.3 libglad.a libimgui.a 
// g++ -o trg triang_test.cpp libglfw.so.3 libglad.a libimgui.a 
// g++ -c main.cpp && g++ -o main main.o shaderprogram.o EBO.o VAO.o VBO.o libglfw.so.3 libglad.a libimgui.a

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/src/imgui.h"
#include "imgui/src/imgui_impl_glfw.h"
#include "imgui/src/imgui_impl_opengl3.h"

#include <vector>
#include <array>


#include <iostream>
#include <cmath>

#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define RED_CREAM           205_u8, 70_u8 , 56_u8 , 255_u8
#define BLUE_LIGHT          72_u8 , 191_u8, 191_u8, 255_u8
#define SOFT_GREEN          33_u8 , 184_u8, 49_u8 , 255_u8

#define SCREEN_WIDTH        1280
#define SCREEN_HEIGHT       720

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec4 aColor;"
"out vec4 color;"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"   color = aColor;"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 color;"
"void main()\n"
"{\n"
"   FragColor = color;\n"
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
    Color blue(BLUE_LIGHT);




    GLfloat vertices_[] = {
        300, 200,     red.r_f, red.g_f, red.b_f, red.a_f,
        800, 500,      red.r_f, red.g_f, red.b_f, red.a_f,
        // 0.0f, 0.5f * float(sqrt(3)) *2 / 3,    red.r_f, red.g_f, red.b_f, red.a_f
    };

    std::cout << "Empezamos el programa de renderizado\n";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(shaderProgram);

    
    
    GLfloat vertices[24];
    size_t width = 50;

    auto normalize_vertices = [&](){
        size_t vertices_size = sizeof(vertices_)/sizeof(GLfloat);
        float   x_1{vertices_[0]},
                y_1{vertices_[1]},
                x_2{vertices_[6]},
                y_2{vertices_[7]};



        float normal_x = y_1 - y_2;
        float normal_y = x_2 - x_1;
        float normal_module = sqrt(normal_x*normal_x + normal_y*normal_y);
        float normalized_normal_x = normal_x/normal_module;
        float normalized_normal_y = normal_y/normal_module;


        vertices[0] = x_1+(normalized_normal_x*width/2);
        vertices[1] = y_1+(normalized_normal_y*width/2);

        vertices[6] = x_1-(normalized_normal_x*width/2);
        vertices[7] = y_1-(normalized_normal_y*width/2);

        vertices[12] = x_2+(normalized_normal_x*width/2);
        vertices[13] = y_2+(normalized_normal_y*width/2);

        vertices[18] = x_2-(normalized_normal_x*width/2);
        vertices[19] = y_2-(normalized_normal_y*width/2);

        uint32_t norm_width = SCREEN_WIDTH/2;
        uint32_t norm_height = SCREEN_HEIGHT/2;
        for(size_t i{} ; i < 4;i++){
            vertices[6*i]   = (vertices[6*i] - norm_width)/norm_width;
            vertices[6*i+1] = (vertices[6*i+1] - norm_height)/norm_height;
            vertices[6*i+2] = red.r_f;
            vertices[6*i+3] = red.g_f;
            vertices[6*i+4] = red.b_f;
            vertices[6*i+5] = red.a_f;
        }
    };
    normalize_vertices();


    for(size_t i{}; i<4;++i){
        for(size_t j{}; j<6; ++j){
            std::cout << " | " << vertices[i*6+j];
        }

        std::cout << std::endl;
    }
    GLuint index_buff[] = {
        0,1,2,
        1,2,3
    };
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buff), index_buff, GL_STATIC_DRAW);

    // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);


    
    // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(2* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Color bkg(BACKGROUND_COLOR);
    float data[2];
    glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, data);
    std::cout << "Aliased range: " << data[0]  << " | " << data[1]<< "\n";
    
    glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, data);
    std::cout << "Aliased range: " << data[0]  << " | " << data[1]<< "\n";

    std::cout << "Do we start this?\n";
    while(!glfwWindowShouldClose(window)){
        glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}