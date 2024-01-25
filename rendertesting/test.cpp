#include "GLFW/glfw3.h"
// #include <iostream>

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Collision Detection Learning Program", NULL, NULL);
    if(window == NULL){
        // std::cout << "Window could not be created!\n"; 
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}