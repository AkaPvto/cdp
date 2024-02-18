#include "segment.hpp"

#include <cmath>


namespace CDP{

Segment::Segment(Vector2r const& p, float l, float h, float w, float r, Color const& c) : pos{p}, length{l}, height{h}, width{w}, rotation{r}, color{c} {
    // First end of the segments' vertical line
    segment_lines[0].start = Vector2r{0,-height/2};
    segment_lines[0].end = Vector2r{0,height/2};
    segment_lines[0].width = width;
    segment_lines[0].color = color;

    // Last end of the segments' vertical line
    segment_lines[1].start = Vector2r{length,-height/2};
    segment_lines[1].end = Vector2r{length,height/2};
    segment_lines[1].width = width;
    segment_lines[1].color = color;

    // Horizontal line of the segment
    segment_lines[2].start = Vector2r{0,0};
    segment_lines[2].end = Vector2r{length,0};
    segment_lines[2].width = width;
    segment_lines[2].color = color;

}


Vector2r Segment::getPos() const{
    return pos;
}

void Segment::setPos(Vector2r const& p_){
    pos = p_;
}

Color const& Segment::getColor() const{
    return color;
}

void Segment::setColor(Color const& c){
    color = c;
    segment_lines[0].setColor(c);
    segment_lines[1].setColor(c);
    segment_lines[2].setColor(c);
}

float Segment::getLength() const{
    return length;
}

void Segment::setLength(float l){
    length = l;
    update();
}

float Segment::getHeight() const{
    return height;
}

void Segment::setHeight(float h){
    height = h;
    update();
}

float Segment::getWidth() const{
    return width;
}

void Segment::setWidth(float w){
    width = w;
    segment_lines[0].setWidth(w);
    segment_lines[1].setWidth(w);
    segment_lines[2].setWidth(w);
}

void Segment::update(){
    segment_lines[0].start = Vector2r{0,-height/2};
    segment_lines[0].end = Vector2r{0,height/2};
    segment_lines[1].start = Vector2r{length,-height/2};
    segment_lines[1].end = Vector2r{length,height/2};
    segment_lines[2].start = Vector2r{0,0};
    segment_lines[2].end = Vector2r{length,0};
}


std::array<Line, 3> Segment::getGlobalLines() const{
    std::array<Line, 3> global_lines;
    for(unsigned int i{}; i<global_lines.size();++i){
        global_lines[i] = segment_lines[i];
        global_lines[i].start = global_lines[i].start.getRotated(rotation) + pos;
        global_lines[i].end = global_lines[i].end.getRotated(rotation) + pos;
    }

    return global_lines;
}

std::array<Line, 3>& Segment::getLines(){
    return segment_lines;
}

void Segment::draw(){
    for(unsigned int i{}; i<segment_lines.size();++i){
        segment_lines[i].draw();
    }
}

} // namespace CDP
