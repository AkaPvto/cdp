#include <SFML/Graphics.hpp>
#include "polygon.hpp"

namespace CDP{

// Contructing a polygon based on a sf::Shape
Polygon::Polygon(sf::ConvexShape const& s) : shape{s}{
    fill();
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


} // namespace CDP
