#include "shaderprogram.hpp"

#include <fstream>
#include <string>
#include <streambuf>
#include <iostream>


std::string read_file(const char* f){
    std::ifstream file(f);
    std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    return str;
}


ShaderProgram::ShaderProgram(){
    program = glCreateProgram();
}

void ShaderProgram::addShader(const char* filename, GLenum type){
    // Create the shader
    GLuint newShader = glCreateShader(type);
    std::string s = read_file(filename);
    char const* shaderSource = s.c_str();
    std::cout << "CHAR: " << shaderSource << "\n";
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