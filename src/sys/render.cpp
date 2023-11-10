#include "render.hpp"
#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
"   glPosition = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";


uint8_t operator ""_u8(unsigned long long i){
    return uint8_t(i);
}
namespace CDP{

void RenderSystem::init(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Collision Detection Learning Program", NULL, NULL);
    if(window == NULL){
        std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


    GLfloat vertices[] = {
        0.2, 0.3, 0.0,
        0.4, 0.5, 0.0,
        0.9, 0.2, 0.0
    };

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    *shaderProgram = glCreateProgram();

    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    Color bkg(BACKGROUND_COLOR);
    glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}


void RenderSystem::update(){
    Color bkg(BACKGROUND_COLOR);
    glClearColor(bkg.r_f, bkg.g_f, bkg.b_f, bkg.a_f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);

    glfwPollEvents();
}

void RenderSystem::end(){
    // Delete the VBO, the VAO and the program itself
    glDeleteBuffers(1, VBO);
    glDeleteVertexArrays(1, VAO);
    glDeleteProgram(*shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
}

bool RenderSystem::isOpen(){
    return !glfwWindowShouldClose(window);
}
} // namespace CDP