#include "sat.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


namespace CDP{
    
bool SAT::colide(Polygon const& p1, Polygon const& p2){
    // Get the normal's axis for each polygon's edge

    // Lambda, for each edge of the given polygon, proyect both polygons
    // Compare the two resultant intervals: return true if intersect, false otherwise
    auto polygon_col = [&](Polygon const& p){
        // Iterate through the vertices of the polygon to get each edge and calculate it's normalized normal
        for(uint8_t i = 0 ; i < p.getVertexCount()-1 ; ++i){
            Vector2r normal = (p.getVertex(i+1) - p.getVertex(i)).getNormal().getNormalized();
            // Call the function to proyect both polygons into the axis of the normal
            if(axis_col(normal, p1, p2)) return false;
        }
        // Since the last edge is calculated "vertex[0] - vertex[n]" 
        // is easier to reduce the iterations of the loop to (n-1) and deal with this case individualy 
        Vector2r normal = (p.getVertex(0) - p.getVertex(p.getVertexCount()-1)).getNormal().getNormalized();
        if(axis_col(normal, p1, p2)) return false;

        return true;
    };

    // Call the lambda to proyect the polygons in each edge's normals
    if(!polygon_col(p1)) return false;
    if(!polygon_col(p2)) return false;
    
    return true;
}

bool SAT::axis_col(Vector2r const& axis, Polygon const& p1, Polygon const& p2){
    // Call the function to proyect a polygon into an axis and recieve the interval of the proyection
    Intersection intr1 = proyection(axis, p1);
    Intersection intr2 = proyection(axis, p2);

    // Check if the intervals intersect
    // return's false if so, true otherwise
    return (intr1.min > intr2.max || intr1.max < intr2.min);
}

SAT::Intersection SAT::proyection(Vector2r const& axis, Polygon const& p){
    Intersection intr{};
    intr.max = intr.min = axis * p.getVertex(0);
    
    // For each vertex of the polygon, we get it's proyection in the given axis using the dot product
    // Filter to get the minimun and maximun in order to obtain the polygon's proyections
    for(uint8_t i{1} ; i < p.getVertexCount() ; ++i){
        real aux = axis*p.getVertex(i);
        if(aux > intr.max) intr.max = aux;
        if(aux < intr.min) intr.min = aux;
    }

    return intr;
}

void SAT::draw(DrawList& draw_l, Polygon const& p1, Polygon const& p2, int window_w, int window_h){



}
} // namespace CDP
