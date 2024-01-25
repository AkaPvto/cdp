#include "shaderprogram.hpp"

#include <fstream>
#include <string>
#include <streambuf>


std::string read_file(const char* f){
    std::ifstream file(f);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return str;
}

void ShaderProgram::init(){
    program = glCreateProgram();
}

void ShaderProgram::addShader(const char* filename, GLenum type){
    // Create the shader
    GLuint newShader = glCreateShader(type);
    std::string s = read_file(filename);
    char const* shaderSource = s.c_str();
    glShaderSource(newShader , 1, &shaderSource, nullptr);

    // Compile the shader
    glCompileShader(newShader);

    // Attach the new shader in the program
    glAttachShader(program, newShader);

    // Delete the shader instance
    glDeleteShader(newShader);
}

void ShaderProgram::link(){
    glLinkProgram(program);
}

void ShaderProgram::use(){
    glUseProgram(program);
}

void ShaderProgram::destroy(){
    glDeleteProgram(program);
}