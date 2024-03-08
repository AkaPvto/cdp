#include "sat.hpp"
#include <iostream>
#include <cmath>

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

void SAT::draw(RenderSystem& render){

}

void SAT::destroy(TextManager& textMan, RenderPolygon& renderPol, RenderLine& renderLine, RenderSegment& renderSegment){

}

// Use of optional as a returning type
bool raycast(Vector2r const& point, real angle, SAT::Strip const& line, Vector2r& col_p){
    // Angle asumed in radians

    // Get the unitary vector in the angle's direction
    Vector2r unitary{cos(angle), sin(angle)};


    // First check if they intersect before anything else
    // Cheking if the dot product between the unitary and the vector obtained from the point to each end of the segment
    // u*(p.start - p0) * u*(p.end - p0) => if both dot products have the same sign, it'll always be positive
    // In case the sign of both dot products are the same, there's no intersection; otherwise, it is
    if(unitary*(line.start - point) * unitary*(line.end - point) > 0) return false;


    // Parametric rect ecuation
    // x = p.x + t*unitary.x
    // y = p.y + t*unitary.y

    // Point-in-segment ecuation; where 0 <= k <= 1
    // x = start.x + k*(end.x - start.x)
    // y = start.y + k*(end.y - start.y)


    // In order to optain the intersection point, we equate this functions
    // p.x + t.unitary.x = start.x + k*(end.x - start.x)
    // p.y + t.unitary.y = start.y + k*(end.y - start.y)

    // Resolving this ecuation system with "t" and "k" as variables
    // k = ( unitary.x*(start.y - p.y) - unitary.y*(start.x - p.x) ) /
    //      ( unitary.y*(end.x - start.x) - unitary.x*(end.y - start.y) )
    // t = ( start.x - p.x + k*(end.x - start.x) ) / unitary.x 
    // Obtain the value of t and u from the parametric system


    real k = ( unitary.x*(line.start.y - point.y) - unitary.y*(line.start.x - point.x) ) / 
                ( unitary.y*(line.end.x - line.start.x) - unitary.x*(line.end.y - line.start.y));
    
    // In orther to obtain the intersection, 
    // we only need one of the variables to substitute in one of the formulas (parametric or segment)
    // real t = (line.start.x - point.x + k*(line.end.x - line.start.x) ) / unitary.x;

    // Use the k value to obtain the intersection point
    col_p.x = line.start.x + k*(line.end.x - line.start.x);
    col_p.y = line.start.y + k*(line.end.y - line.start.y);

    return true;
}
} // namespace CDP
