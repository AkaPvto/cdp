// g++ -c main.cpp && g++ -o main main.o libglfw.so.3 libglad.a libimgui.a 
// g++ -c main.cpp && g++ -o main main.o shaderprogram.o EBO.o VAO.o VBO.o libglfw.so.3 libglad.a libimgui.a

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "shaderprogram.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include <vector>


#include <iostream>
#include <cmath>

#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define RED_CREAM           205_u8, 70_u8 , 56_u8 , 255_u8
#define BLUE_LIGHT          72_u8 , 191_u8, 191_u8, 255_u8

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

    struct Vector2r{
        float x{}, y{};

        Vector2r(Vector2r const&) = default;
        Vector2r(Vector2r&&) = default;
        Vector2r() = default;
    };
    
    struct Polygon{
        Polygon(std::vector<Vector2r> v, Color c) : vertices{v}, color{c}{}
        std::vector<Vector2r> vertices;
        Color color;

        void normalize_vertices(uint32_t width, uint32_t height){
            uint32_t norm_width = width/2;
            uint32_t norm_height = height/2;
            for(auto& v : vertices){
                v.x = (v.x-norm_width)/norm_width;
                v.y = (v.y-norm_height)/norm_height;
            }
        }
    };
    std::vector<Polygon> polygons;
    
    std::vector<Vector2r> v2{{150, 50}, {300,50}, {400,200}, {300,350}, {150,350}, {50,200}};
    polygons.emplace_back(v2, blue);
    polygons.back().normalize_vertices(1280, 720);

    std::vector<Vector2r> verts{{200,50}, {340,155}, {300,350}, {100,350}, {50,150}};
    polygons.emplace_back(verts, red);
    polygons.back().normalize_vertices(1280, 720);




    // GLfloat vertices[] = {
    //     -0.5f, -0.5f * float(sqrt(3)) / 3,     red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f, -0.5f * float(sqrt(3)) / 3,      red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, 0.5f * float(sqrt(3)) *2 / 3,    red.r_f, red.g_f, red.b_f, red.a_f
    // };
    GLuint last_vertex_num = 0;
    std::vector<GLfloat> vertices;
    // GLfloat vertices[] = {
    //     -0.5f, -0.5f * float(sqrt(3)) / 3,     red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f, -0.5f * float(sqrt(3)) / 3,      red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, 0.5f * float(sqrt(3)) *2 / 3,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     -0.5f / 2, 0.5f * float(sqrt(3)) / 6,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.5f / 2, 0.5f * float(sqrt(3)) / 6,    red.r_f, red.g_f, red.b_f, red.a_f,
    //     0.0f, -0.5f * float(sqrt(3)) / 3,    red.r_f, red.g_f, red.b_f, red.a_f

    // };
    std::vector<GLuint> index_buff;
    // GLuint index_buff[] = {
    //     0, 3, 5,
    //     3, 2, 4,
    //     5, 4, 1
    // };
    // Probar idea:
    // Utilizar un std::vector<GLfloat> para almacenar los vertices de los poligonos
    // Pasar a la funcion de openGL la direccion de memoria del inicio del vector usando vector.begin()
    // Y el tamaño usando vector.size()
    // Con esto deberia de ser suficiente para que openGL no se coje y utilice los datos de std::vector
    auto add_polygons = [&](){
        for(auto& p : polygons){
            for(auto v : p.vertices){
                vertices.push_back(v.x);
                vertices.push_back(v.y);
                vertices.push_back(p.color.r_f);
                vertices.push_back(p.color.g_f);
                vertices.push_back(p.color.b_f);
                vertices.push_back(p.color.a_f);
            }
            for(size_t i = last_vertex_num+1; i<(last_vertex_num+p.vertices.size()-1); ++i){
                index_buff.push_back(last_vertex_num);
                index_buff.push_back(i);
                index_buff.push_back(i+1);
            }

            last_vertex_num += p.vertices.size(); 
        }

    };

    add_polygons();

    int count = 0;
    for(auto v : vertices){
        std::cout << "Vertex " << count << ": " << v << "\n";
        if(++count >= 6){
            count = 0;
            std::cout << std::endl;
        }
    }
    count = 0;
    for(auto i : index_buff){
        std::cout << "Vertex " << count << ": " << i << "\n";
        if(++count >= 3){
            count = 0;
            std::cout << std::endl;
        }
    }

    std::cout << "Empezamos el programa de renderizado\n";

    ShaderProgram shader_P{};
    shader_P.addShader("shader.vert", GL_VERTEX_SHADER);
    shader_P.addShader("shader.frag", GL_FRAGMENT_SHADER);
    // shader_P.addShader("shader.geom", GL_GEOMETRY_SHADER);
    shader_P.link();

    // GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    // GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);

    // GLuint shaderProgram = glCreateProgram();

    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragmentShader);

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);
    // glLinkProgram(shaderProgram);
    
    VAO vao{};
    VBO vbo{};
    EBO ebo{};
    
    vao.bind();
    vbo.insert(vertices.data(), sizeof(GLfloat)*vertices.size());
    ebo.insert(index_buff.data(), sizeof(GLuint)*index_buff.size());
    
    
    vao.addAttrib(vbo, 0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    vao.addAttrib(vbo, 1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    
    
    // GLuint VAO;
    // GLuint VBO;
    // GLuint EBO;

    // glGenVertexArrays(1, &VAO);

    // glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);
    
    // glBindVertexArray(VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
    // // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*index_buff.size(), index_buff.data(), GL_STATIC_DRAW);

    // // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);


    
    // // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(2* sizeof(float)));
    // glEnableVertexAttribArray(1);
    
    
    // glBindVertexArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Color bkg(BACKGROUND_COLOR);
    std::cout << "Do we start this?\n";
    while(!glfwWindowShouldClose(window)){
        glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
        glClear(GL_COLOR_BUFFER_BIT);
        shader_P.use();
        // glUseProgram(shaderProgram);
        vao.bind();
        // glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // // glDrawElements(primitive, numIndices, typeIndices, index of indices (?))
        glDrawElements(GL_TRIANGLES, index_buff.size(), GL_UNSIGNED_INT, 0);

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

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shader_P.destroy();


    glfwDestroyWindow(window);
    glfwTerminate();
}



// void init(){
//     // GLFW initialization values/flags
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//     // Window creation
//     // CHANGE WINDOW TO AN ATTRIBUTE
//     GLFWwindow* window = glfwCreateWindow(1280, 720, "Collision Detection Learning Program", NULL, NULL);
//     if(window == NULL){
//         std::cout << "Window could not be created!\n"; 
//         glfwTerminate();
//     }
//     glfwMakeContextCurrent(window);


//     // ImGui initialization and link with the window
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO();
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 130");
//     ImGui::StyleColorsDark();

//     // Glad initialization and configuration
//     gladLoadGL();

//     glViewport(0, 0, 1280, 720);

// }

// void drawAll(){
//     glUseProgram(shaderProgram);
//     glBindVertexArray(VAO);
//     glDrawArrays(GL_TRIANGLES, 0, 3);
// }

// void draw(){

// }

// void drawUI(){
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();

//     ImGui::Begin("Window Tittle");
//     ImGui::Text("Window text!");
//     ImGui::End();

//     ImGui::Render();
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// }

// void render(){
//     // Draw the background
//     glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
//     glClear(GL_COLOR_BUFFER_BIT);   

//     // Draw all the polygons
//     // This function will draw all the polygons storaged in the class
//     drawAll();

//     // Draw the interface
//     // This function will execute all the logic behind the UI
//     drawUI();


//     // Swap the buffer and call the events at the end of the render iteration
//     glfwSwapBuffers(window);
//     glfwPollEvents();
// }

// void end(){
//     // IMPLEMENT THIS LATER
//     // // Delete all the vertex objects and the shader program
//     // glDeleteBuffers(1, &VBO);
//     // glDeleteVertexArrays(1, &VAO);
//     // glDeleteProgram(shaderProgram);
    

//     // // Delete the glfw window
//     // glfwDestroyWindow(window);
//     // glfwTerminate();
// }
