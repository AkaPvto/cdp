#include <SFML/Graphics.hpp>
#include "polygon.hpp"

namespace CDP{

// // Default constructor initialices the value of all the vertex to 0
// Polygon::Polygon(){
//     for(Vector2r v : vertices) v = Vector2r{};
// }

// Fills the values of vertices with the SFML Shape
bool Polygon::fill(sf::Shape const* s){
    if(s == nullptr) return false;

    // Get the polygon's amount of vertices
    if(n_vertices = s->getPointCount(); n_vertices <= 0) return false;

    // Get the global position
    position.x = s->getPosition().x;
    position.y = s->getPosition().y;

    // Get the local vertex coordinates
    for(size_t i{}; i<n_vertices ; ++i){
        vertices.emplace_back(Vector2r{s->getPoint(i).x + position.x, s->getPoint(i).y + position.y});
    }
    return true;
}
} // namespace CDP
