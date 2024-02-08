#include <glad/glad.h>
#include <iostream>

void checkGLError(const char* file, int line) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error in " << file << " at line " << line << ": ";
        switch (err) {
            case GL_INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                std::cout << "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                std::cout << "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                std::cout << "Unknown error";
                break;
        }
        std::cout << std::endl;
    }
}