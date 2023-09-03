#include "aabb.hpp"

namespace CDP{

// Check collisions between 2 boxes using AABB
bool AABB::colide(Polygon const& b1, Polygon const& b2){
    // Exclude more-or-less vertices polygons
    if(b1.n_vertices != 4 || b2.n_vertices != 4) return false;

    // We'll check each axis separately
    // The box's vertices are asumed to be setted clockwise, starting in the top-left:
    //          0--------1
    //          |        |
    //          3--------2

    real xMax_1{b1.vertices.at(1).x}, xMin_1{b1.vertices.at(0).x}, 
         xMax_2{b2.vertices.at(1).x}, xMin_2{b2.vertices.at(0).x};
    real yMax_1{b1.vertices.at(3).y}, yMin_1{b1.vertices.at(0).y}, 
         yMax_2{b2.vertices.at(3).y}, yMin_2{b2.vertices.at(0).y};

    // Check 1-dimensionaly if the boxes are colliding
    if(xMax_1 < xMin_2 || xMin_1 > xMax_2) return false;
    // Same with Y axis
    if(yMax_1 < yMin_2 || yMin_1 > yMax_2) return false;

    return true;
}


} // namespace CDP