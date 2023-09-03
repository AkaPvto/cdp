#include "algorith.hpp"
#include "types/polygon.hpp"

namespace CDP{
// AABB stands for Axis-Aligned Bounding Box
// AABB collision detection asumes regular polygons with 4 vertices and not rotary
struct AABB : Algorithm{
    bool colide(Polygon const&, Polygon const&);
};
} // namespace CDP