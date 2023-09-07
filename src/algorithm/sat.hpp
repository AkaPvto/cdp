#include "algorithm.hpp"
#include "types/polygon.hpp"

namespace CDP{
// SAT stands for Separating Axis Theorem
// This algorithm watches for an axis in witch the proyections of the two polygons doesn't intersect
struct SAT : Algorithm{
    struct Intersection{
        real min{0}, max{0};
    };
    bool colide(Polygon const&, Polygon const&);
    bool axis_col(Vector2r const& axis, Polygon const& p1, Polygon const& p2);
    Intersection proyection(Vector2r const& axis, Polygon const& p);
};
} // namespace CDP