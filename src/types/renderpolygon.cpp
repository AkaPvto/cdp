#include "renderpolygon.hpp"

#include <stdexcept>
#include <iostream>


// (x + y + color data (4 values))
#define VERTEX_SIZE 6

namespace CDP{
RenderPolygon::RenderPolygon(uint32_t w, uint32_t h) : width{w}, height{h}{

}

void RenderPolygon::update_color(Polygon& polygon){
    for(size_t i{};i<polygon.vertices.size();++i){
        polygon.vbo.modify(reinterpret_cast<GLfloat*>(&polygon.color.r_f), sizeof(GLfloat)*4, sizeof(GLfloat)*(i*VERTEX_SIZE+2));
    }
}

void RenderPolygon::update_position(Polygon& polygon){
    // Obtain the normalized value of the polygon's position
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;

    // Vector data array (size = 2*number of vertices)
    GLfloat* buffer_data = new GLfloat[polygon.vertices.size()*6];
    try{
        int count = 0;
        for(auto v : polygon.vertices){
            // Storage in the array the x and y values
            buffer_data[count] = ((v.x+polygon.position.x)-norm_width)/norm_width;
            buffer_data[count+1] = ((v.y+polygon.position.y)-norm_height)/norm_height;
            // With the array, being a pointer, can use the "+" operator to obtein the memory adress of the item you need. In this case the "count"-th item
            // In the VBO the "x" and "y" bytes of info are storaged before the bytes of the color
            // Since the color is x2 of the coordinades, there is 6 floats of offset per vertex. The ammount of vertices already iterated is count/2 
            polygon.vbo.modify((buffer_data + count), sizeof(GLfloat)*2, sizeof(GLfloat)*(count*3));

            count+=2;
        }
    }catch(std::exception const& e){
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }

    delete[] buffer_data;
}

void RenderPolygon::update_buffers(Polygon& polygon){
    // Vertices size * vertex size
    size_t buffer_size = polygon.vertices.size()*(VERTEX_SIZE);
    //(Ammount of triangles after teselating a polygon)*(number of vertices of a triangle) => (n_vertices-2)*(3)
    int index_size = polygon.getEBOsize();

    GLfloat* buffer_data = new GLfloat[buffer_size];
    GLuint*  index_data = new GLuint[index_size];

    try{
        process_data(polygon, buffer_data, index_data, buffer_size, index_size);

        polygon.vao.bind();
        polygon.vbo.modify(buffer_data, sizeof(GLfloat)*buffer_size, 0);
        polygon.ebo.modify(index_data,  sizeof(GLuint)*index_size, 0);

        polygon.vbo.bind();
        polygon.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
        polygon.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
        polygon.vao.unbind();

        polygon.vbo.unbind();
        polygon.ebo.unbind();
    }catch(std::exception const& e){
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }

    delete(buffer_data);
    delete(index_data);

}

void RenderPolygon::init_buffers(Polygon& polygon){
    // Vertices size * vertex size
    int buffer_size = polygon.vertices.size()*(VERTEX_SIZE);
    //(Ammount of triangles after teselating a polygon)*(number of vertices of a triangle) => (n_vertices-2)*(3)
    int index_size = polygon.getEBOsize();

    GLfloat* buffer_data = new GLfloat[buffer_size];
    GLuint*  index_data = new GLuint[index_size];

    try{
        process_data(polygon, buffer_data, index_data, buffer_size, index_size);

        polygon.vao.bind();
        polygon.vbo.insert(buffer_data, sizeof(GLfloat)*buffer_size);
        polygon.ebo.insert(index_data,  sizeof(GLuint)*index_size);

        polygon.vbo.bind();
        polygon.vao.addAttrib(0, 2, GL_FLOAT, 6*sizeof(float), (void*)0);
        polygon.vao.addAttrib(1, 4, GL_FLOAT, 6*sizeof(float), (void*)(2*sizeof(float)));
        polygon.vao.unbind();

        polygon.vbo.unbind();
        polygon.ebo.unbind();
    }catch(std::exception const& e){
        std::cerr << "Exception thrown: " << e.what() << std::endl;
    }

    delete[] buffer_data;
    delete[] index_data;
}


void RenderPolygon::process_data(Polygon& polygon, GLfloat* buffer_data, GLuint* index_data, GLsizeiptr buffer_size, GLsizeiptr index_size){
    // Obtain the normalized value of the polygon's position
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;

    // Insert the data of each vertex into the buffer_data
    int count = 0;
    for(auto v : polygon.vertices){
        buffer_data[count++] = ((v.x+polygon.position.x)-norm_width)/norm_width;
        buffer_data[count++] = ((v.y+polygon.position.y)-norm_height)/norm_height;
        buffer_data[count++] = polygon.color.r_f;
        buffer_data[count++] = polygon.color.g_f;
        buffer_data[count++] = polygon.color.b_f;
        buffer_data[count++] = polygon.color.a_f;
    }
    count = 0;
    
    // Insert the index of each vertex into the index_data
    for(size_t i = 1; i<polygon.vertices.size()-1; ++i){
        index_data[count++] = 0;
        index_data[count++] = i;
        index_data[count++] = i+1;
    }
}


void RenderPolygon::delete_buffers(Polygon& polygon){
    polygon.vbo.destroy();
    polygon.ebo.destroy();
    polygon.vao.destroy();
}


} // namespace CDP