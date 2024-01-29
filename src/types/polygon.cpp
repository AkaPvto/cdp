#include "polygon.hpp"


namespace CDP{

// Constructing a polygon with an array of vertices and a position
Polygon::Polygon(std::vector<Vector2r> const& _vertices, Vector2r const& _pos) : position{_pos}{
    setVertices(_vertices);
}


// ############# GETTERS AND SETTERS #############

int Polygon::getVertexCount() const{
    return n_vertices;
}

Vector2r Polygon::getCenter() const{
    real x{}, y{};

    for(Vector2r const& v : vertices){
        x += v.x;
        y += v.y;
    }

    return Vector2r{x/n_vertices, y/n_vertices};
}

Vector2r Polygon::getVertex(int index) const{
    if(index > n_vertices) return {-1,-1};

    return {vertices.at(index) + position};
}

Vector2r Polygon::getLocalVertex(int index) const{
    if(index > n_vertices) return {-1,-1};

    return vertices.at(index);
}


void Polygon::setVertex(Vector2r const& v, int index){
    if(index > n_vertices) return;

    vertices.at(index) = v;
}

void Polygon::setVertices(std::vector<Vector2r> const& verts){
    if(verts.size() <=0 ) return;

    vertices = verts;
    n_vertices = verts.size();
}

Vector2r Polygon::getPosition() const{
    return position;
}

void Polygon::setPosition(Vector2r const& p){
    position = p;
}

void Polygon::move(Vector2r const& v){
    position += v;
}

real Polygon::getBorder() const{
    return border_size;
}

void Polygon::setBorder(real const& b){
    if(b < 0) return;
    border_size = b;
}

Color const& Polygon::getColor() const{
    return color;
}

void Polygon::setColor(Color const& c){
    color = c;
}

Color const& Polygon::getBorderColor() const{
    return border_color;
}

void Polygon::setBorderColor(Color const& color){
    border_color = color;
}


// ############# CUSTOM METHODS #############

void Polygon::normalize_vertices(uint32_t width, uint32_t height){
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;
    for(auto& v : vertices){
        v.x = (v.x-norm_width)/norm_width;
        v.y = (v.y-norm_height)/norm_height;
    }
}

void Polygon::draw(){
    vao.bind();
    glDrawElements(GL_TRIANGLES, getEBOsize(), GL_UNSIGNED_INT, 0);
}

int Polygon::getEBOsize(){ return (vertices.size()-2)*3; }


// ############# ITERATION METHODS #############

std::vector<Vector2r>::iterator Polygon::begin(){
    return vertices.begin();
}

std::vector<Vector2r>::iterator Polygon::end(){
    return vertices.end();
}

std::vector<Vector2r>::const_iterator Polygon::begin() const{
    return vertices.begin();
}

std::vector<Vector2r>::const_iterator Polygon::end() const{
    return vertices.end();
}
 

} // namespace CDP
