#include "renderline.hpp"

#include <cassert>

// Number of GLfloats per line
#define VERTEX_SIZE 6

namespace CDP{
RenderLine::RenderLine(uint32_t _w, uint32_t _h) : width{_w}, height{_h}{

}

void RenderLine::init_buffers(Line& line){
    // Vertex size * number of vertices
    int buffer_size = VERTEX_SIZE*2;

    GLfloat* buffer_data = new GLfloat[buffer_size];

    process_data(line, buffer_data, buffer_size);

    // openGL buffers data management
    line.vao.bind();
    line.vbo.insert(buffer_data, sizeof(GLfloat)*buffer_size);

    line.vbo.bind();
    line.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    line.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    line.vao.unbind();

    line.vbo.unbind();

    delete []buffer_data;
}

void RenderLine::update_buffers(Line& line){
    // Vertex size * number of vertices
    int buffer_size = VERTEX_SIZE*2;

    GLfloat* buffer_data = new GLfloat[buffer_size];

    process_data(line, buffer_data, buffer_size);

    // openGL buffers data management
    line.vao.bind();
    line.vbo.modify(buffer_data, sizeof(GLfloat)*buffer_size, 0);

    line.vbo.bind();
    line.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    line.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    line.vao.unbind();

    line.vbo.unbind();

    delete []buffer_data;
}

void RenderLine::udpate_vertices(Line& line){
    // Obtain the normalized value of the polygon's position
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;

    // Vector data array (size = 2*number of vertices)
    GLfloat* buffer_data = new GLfloat[2*VERTEX_SIZE];
    uint8_t count = 0;
    // Storage in the array the x and y values
    buffer_data[count]    = (line.start.x-norm_width) /norm_width;
    buffer_data[count+1]  = (line.start.y-norm_height)/norm_height;
    // With the array being a pointer we can use the "+" operator to obtain the memory adress of the item you need. In this case the "count"-th item
    // In the VBO the "x" and "y" bytes of info are storaged before the bytes of the color
    // Since the color is x2 of the coordinades, there is 6 floats of offset per vertex. The ammount of vertices already iterated is count/2
    // Lines only have 2 vertices instances so we'll manually iterate through the two
    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // start vertex
    count+=2;

    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // end vertex
    
    delete []buffer_data;
}

void RenderLine::update_color(Line& line){
    uint8_t count{};
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // start vertex
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // end vertex
}

void RenderLine::process_data(Line& line, GLfloat* buffer_data, GLsizeiptr buffer_size){
    // Obtain the normalized value of the polygon's position
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;

    // Add the vertex color byte-data to the buffer_data
    auto add_color = [&](uint16_t& count){
        buffer_data[count++] = line.color.r_f;
        buffer_data[count++] = line.color.g_f;
        buffer_data[count++] = line.color.b_f;
        buffer_data[count++] = line.color.a_f;
    };

    // Insert the data of each vertex into the buffer_data
    uint16_t count{};
    buffer_data[count++] = (line.start.x-norm_width)  / norm_width;
    buffer_data[count++] = (line.start.y-norm_width)  / norm_width;
    add_color(count);

    buffer_data[count++] = (line.end.x-norm_height)   / norm_height;
    buffer_data[count++] = (line.end.y-norm_height)   / norm_height;
    add_color(count);
}

void RenderLine::delete_buffers(Line& line){
    line.vbo.destroy();
    line.vao.destroy();
}

} // namespace CDP