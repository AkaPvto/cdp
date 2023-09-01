#include <SFML/Graphics.hpp>
#include "polygon.hpp"

namespace CDP{

// Default constructor initialices the value of all the vertex to 0
template <uint16_t I>
Polygon<I>::Polygon(){
    n_vertices = I;
    for(Vertex v : vertices) v = {0,0,0};
}

// Fills the values of vertices with the SFML Shape
template <uint16_t I>
bool Polygon<I>::fill(sf::Shape const* s){
    if(s == nullptr || n_vertices != s->getPointCount()) return false;

    // Get the global position
    position = s->getPosition();

    // Get the local vertex coordinates
    for(size_t i{}; i<n_vertices ; ++i){
        vertices[i] = s->getPoint(i);
    }
}
} // namespace CDP
