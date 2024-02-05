#include "line.hpp"

namespace CDP{

Line::Line(Vector2r const& s, Vector2r const& e,  Color c, float w) : 
start{s}, end{e}, color{c}, width{w} {

}

void Line::setColor(Color const& color){
    this->color = color;
}

void Line::setWidth(float width){
    this->width = width;
}

// void Line::setSmooth(bool smooth){
//     this->smooth = smooth;
// }
// void Line::setStipple(bool stipple, uint8_t stipple_factor, uint16_t stipple_pattern){
//     this->stipple = stipple;
//     this->stipple_factor = stipple_factor;
//     this->stipple_pattern = stipple_pattern;
// }


void Line::draw(){
    vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

} // namespace CDP