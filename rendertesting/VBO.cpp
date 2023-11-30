#include "VBO.hpp"

VBO::VBO(){
    glGenBuffers(1, &id);
}

void VBO::insert(GLfloat* vertices, GLsizeiptr size){
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}


void VBO::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::destroy(){
    glDeleteBuffers(1, &id);
}