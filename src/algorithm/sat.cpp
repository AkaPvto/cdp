#include "sat.hpp"
#include <iostream>

namespace CDP{
    
bool SAT::colide(Polygon const& p1, Polygon const& p2){
    // Get the normal's axis for each polygon's edge
    auto polygon_col = [&](Polygon const& p){
        for(uint8_t i = 0 ; i < p.n_vertices-1 ; ++i){
            Vector2r normal = (p.vertices[i+1] - p.vertices[i]).getNormal().getNormalized();
            if(axis_col(normal, p1, p2)) return false;
        }
        Vector2r normal = (p.vertices[0] - p.vertices[p.n_vertices-1]).getNormal().getNormalized();
        if(axis_col(normal, p1, p2)) return false;

        return true;
    };

    if(!polygon_col(p1)) return false;
    if(!polygon_col(p2)) return false;
    
    return true;
}

bool SAT::axis_col(Vector2r const& axis, Polygon const& p1, Polygon const& p2){
    Intersection intr1 = proyection(axis, p1);
    Intersection intr2 = proyection(axis, p2);

    return (intr1.min > intr2.max || intr1.max < intr2.min);
}

SAT::Intersection SAT::proyection(Vector2r const& axis, Polygon const& p){
    Intersection intr{};
    intr.min = axis * p.vertices[0];
    
    for(uint8_t i{1} ; i < p.n_vertices ; ++i){
        real aux = axis*p.vertices[i];
        if(aux > intr.max) intr.max = aux;
        if(aux < intr.min) intr.min = aux;
    }

    return intr;
}
} // namespace CDP
