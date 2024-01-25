#include "algorithm.hpp"
#include "types/polygon.hpp"


namespace CDP{
// AABB stands for Axis-Aligned Bounding Box
// AABB collision detection asumes regular polygons with 4 vertices and not rotary
struct AABB : Algorithm{
    bool colide(Polygon const&, Polygon const&);
    void draw(DrawList&, Polygon const&, Polygon const&, int, int);

    // Drawable flags
    bool proyection_F   {true};
    bool intersection_F {false};


};
} // namespace CDP