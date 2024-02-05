#include "renderline.hpp"

#include <cassert>

// Number of GLfloats per line
#define VERTEX_SIZE 6

// The number of triangles will always be 2. Indices per triangle (3) * num triangles(2)
#define INDEX_SIZE 6

namespace CDP{
RenderLine::RenderLine(uint32_t _w, uint32_t _h) : width{_w}, height{_h}{

}

void RenderLine::init_buffers(Line& line){
    // Vertex size * number of vertices
    GLfloat buffer_data[VERTEX_SIZE*4];
    GLuint index_data[INDEX_SIZE];

    process_data(line, buffer_data, index_data);

    // openGL buffers data management
    line.vao.bind();
    line.vbo.insert(buffer_data, sizeof(buffer_data));
    line.ebo.insert(index_data, sizeof(index_data));

    line.vbo.bind();
    line.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    line.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    line.vao.unbind();

    line.vbo.unbind();
    line.ebo.unbind();

}

void RenderLine::update_buffers(Line& line){
    // Vertex size * number of vertices
    GLfloat buffer_data[VERTEX_SIZE*4];
    GLuint index_data[INDEX_SIZE];
    
    process_data(line, buffer_data, index_data);

    // openGL buffers data management
    line.vao.bind();
    line.vbo.modify(buffer_data, sizeof(buffer_data), 0);
    line.ebo.modify(index_data, sizeof(index_data), 0);

    line.vbo.bind();
    line.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
    line.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
    line.vao.unbind();

    line.vbo.unbind();
    line.ebo.unbind();

}

void RenderLine::udpate_vertices(Line& line){
    // Vector data array (Vertex size * number of vertices)
    GLfloat buffer_data[VERTEX_SIZE*4];
    GLuint index_aux[INDEX_SIZE];
    uint8_t count = 0;

    // Storage in the array the new values
    process_data(line, buffer_data, index_aux);

    // With the array being a pointer we can use the "+" operator to obtain the memory adress of the item you need. In this case the "count"-th item
    // In the VBO the "x" and "y" bytes of info are storaged before the bytes of the color
    // Since the color is x2 of the coordinades, there is 6 floats of offset per vertex. The ammount of vertices already iterated is count/2
    // Lines only have 4 vertices so we'll manually iterate through them
    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // start vertex + normalized normal
    count+=2;

    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // start vertex - normalized normal
    count+=2;

    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // end vertex + normalized normal
    count+=2;
    
    line.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3)); // end vertex - normalized normal

}

void RenderLine::update_color(Line& line){
    uint8_t count{};
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // start vertex + normalized normal
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // start vertex - normalized normal
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // end vertex + normalized normal
    line.vbo.modify(reinterpret_cast<GLfloat*>(&line.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(count++*VERTEX_SIZE+2));   // end vertex - normalized normal
}

void RenderLine::process_data(Line& line, GLfloat* buffer_data, GLuint* index_data){
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

    // Obtain the normalized permendicular of the vector obtained from the line's vertices
    Vector2r line_vertex = line.end - line.start;
    Vector2r normal = line_vertex.getNormal();
    Vector2r normal_u = normal.getNormalized();
    

    // Insert the data of each vertex into the buffer_data
    // For each of the line's vertices we'll produce 2 vertex,
    // The new vertices will be the both permendiculars of the line, using the line's width as it's module and the normalized normal as the direction
    uint16_t count{};
    buffer_data[count++] = ((line.start.x +normal_u.x*line.width/2)-norm_width)  / norm_width;
    buffer_data[count++] = ((line.start.y +normal_u.y*line.width/2)-norm_height)  / norm_height;
    add_color(count);

    buffer_data[count++] = ((line.start.x -normal_u.x*line.width/2)-norm_width)  / norm_width;
    buffer_data[count++] = ((line.start.y -normal_u.y*line.width/2)-norm_height)  / norm_height;
    add_color(count);

    buffer_data[count++] = ((line.end.x +normal_u.x*line.width/2)-norm_width)   / norm_width;
    buffer_data[count++] = ((line.end.y +normal_u.y*line.width/2)-norm_height)   / norm_height;
    add_color(count);

    buffer_data[count++] = ((line.end.x -normal_u.x*line.width/2)-norm_width)   / norm_width;
    buffer_data[count++] = ((line.end.y -normal_u.y*line.width/2)-norm_height)   / norm_height;
    add_color(count);

    // The index array will always be the same since all lines will be a rectangle made by two mirrored and upside-down triangles
    // 0------1
    // |     /|
    // | A  / |
    // |   /  |
    // |  /   |
    // | /    |
    // |/   B |
    // 2------3
    // The trinales are: triangle A{0, 1, 2} and triangle B{1,2,3}
    index_data[0] = 0;
    index_data[1] = 1;
    index_data[2] = 2;

    index_data[3] = 1;
    index_data[4] = 2;
    index_data[5] = 3;
}

void RenderLine::delete_buffers(Line& line){
    line.vbo.destroy();
    line.vao.destroy();
}

} // namespace CDP