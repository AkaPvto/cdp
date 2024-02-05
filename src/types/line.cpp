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

void Line::setSmooth(bool smooth){
    this->smooth = smooth;
}
void Line::setStipple(bool stipple, uint8_t stipple_factor, uint16_t stipple_pattern){
    this->stipple = stipple;
    this->stipple_factor = stipple_factor;
    this->stipple_pattern = stipple_pattern;
}


void Line::draw(){
    vao.bind();

    // if(smooth) glEnable(GL_LINE_SMOOTH);
    // if(stipple){
    //     glEnable(GL_LINE_STIPPLE);
    //     glLineStipple(stipple_factor, stipple_pattern);
    // }
    // glPushAttrib(GL_LINE_BIT);

    glLineWidth( width );
    glDrawArrays(GL_LINES, 0, 2);



    // glPopAttrib();
    // glDisable(GL_LINE_SMOOTH);
    // glDisable(GL_LINE_STIPPLE);
}

} // namespace CDP