#include <SFML/Graphics.hpp>
#include "polygon.hpp"

namespace CDP{

// Contructing a polygon based on a sf::Shape
Polygon::Polygon(sf::ConvexShape const& s) : shape{s}{
    fill();
}

// Constructing a polygon with an array of vertices and a position
Polygon::Polygon(std::vector<Vector2r> const& _vertices, Vector2r const& _pos) : position{_pos}{
    setVertices(_vertices);
    update();
}


// Getters and setters
sf::ConvexShape const& Polygon::getShape() const{
    return shape;
}

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

    return {vertices.at(index).x + position.x, vertices.at(index).y + position.y};
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
    update();
}

Vector2r Polygon::getPosition() const{
    return position;
}

void Polygon::setPosition(Vector2r const& p){
    position = p;
}

real Polygon::getBorder() const{
    return shape.getOutlineThickness();
}

void Polygon::setBorder(real const& b){
    if(b < 0) return;
    shape.setOutlineThickness(b);
}

sf::Color const& Polygon::getColor() const{
    return shape.getFillColor();
}

void Polygon::setColor(sf::Color const& color){
    shape.setFillColor(color);
}

sf::Color const& Polygon::getBorderColor() const{
    return shape.getOutlineColor();
}

void Polygon::setBorderColor(sf::Color const& color){
    shape.setOutlineColor(color);
}

void Polygon::draw(RenderStorage const& storage){
    for(auto v : this->vertices){
        storage.vertices.push_back(v.x);
        storage.vertices.push_back(v.y);
        storage.vertices.push_back(color.r_f);
        storage.vertices.push_back(color.g_f);
        storage.vertices.push_back(color.b_f);
        storage.vertices.push_back(color.a_f);
    }
    size_t teselation_index = storage.last_index + this->vertices.size() - 1;
    for(size_t i = storage.last_index+1; i< teselation_index; ++i){
        storage.index_buff.push_back(storage.last_index);
        storage.index_buff.push_back(i);
        storage.index_buff.push_back(i+1);
    }

    storage.last_index += vertices.size(); 
}


// Updates the value of the sf::Shape based on the polygon
void Polygon::update(){
    shape.setPosition({position.x, position.y});
    shape.setPointCount(n_vertices);
    for(size_t i{} ; i < vertices.size() ; ++i){
        shape.setPoint(i, sf::Vector2f{vertices.at(i).x, vertices.at(i).y});
    }
}

// Assigns a sf::Shape to a polygon
void Polygon::assign(sf::ConvexShape const& s){
    shape = sf::ConvexShape{s};
}

// Fills the values of vertices with the atributte shape
bool Polygon::fill(){
    return fill(shape);
}

// Fills the values of vertices with the SFML Shape
bool Polygon::fill(sf::ConvexShape const& s){
    // Get the polygon's amount of vertices
    if(n_vertices = s.getPointCount(); n_vertices <= 0) return false;

    // Get the global position
    position.x = s.getPosition().x;
    position.y = s.getPosition().y;

    // Get the local vertex coordinates
    for(size_t i{}; i<n_vertices ; ++i){
        vertices.emplace_back(Vector2r{s.getPoint(i).x, s.getPoint(i).y});
    }
    return true;
}

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
