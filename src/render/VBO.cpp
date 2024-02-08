#include "VBO.hpp"

VBO::VBO(){
    glGenBuffers(1, &id);
}

void VBO::dynamic_insert(GLfloat* vertices, GLsizeiptr size){
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void VBO::insert(GLfloat* vertices, GLsizeiptr size){
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::modify(GLfloat* data, GLsizeiptr size, GLintptr offset){
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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