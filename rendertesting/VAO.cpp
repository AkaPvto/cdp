#include "VAO.hpp"
#include "VBO.hpp"

VAO::VAO(){
    glGenVertexArrays(1, &id);
}

void VAO::addAttrib(GLuint layout, GLuint numComponents, GLenum type, GLint stride, void const* offset){
    // vbo.bind();

    // glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset)
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    
    // vbo.unbind();
}

void VAO::bind(){
    glBindVertexArray(id);
}

void VAO::unbind(){
    glBindVertexArray(0);
}

void VAO::destroy(){
    glDeleteVertexArrays(1, &id);
}