#include "EBO.hpp"

EBO::EBO(){
    glGenBuffers(1, &id);
}

void EBO::insert(GLuint* vertices, GLsizeiptr size){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void EBO::bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EBO::unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy(){
    glDeleteBuffers(1, &id);
}