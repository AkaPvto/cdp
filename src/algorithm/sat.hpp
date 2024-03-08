#include "algorithm.hpp"
#include "types/polygon.hpp"

#include "types/segment.hpp"

namespace CDP{
// SAT stands for Separating Axis Theorem
// This algorithm watches for an axis in witch the proyections of the two polygons doesn't intersect
struct SAT : Algorithm{
    struct Intersection{
        real min{0}, max{0};
    };
    struct Axis{
        Vector2r ref_point{0,0};
        real angle{0.0};
        size_t radius{1920};
    };
    struct Strip{
        Vector2r start{}, end{};
    };
    
    bool colide(Polygon const&, Polygon const&);
    bool axis_col(Vector2r const& axis, Polygon const& p1, Polygon const& p2);
    Intersection proyection(Vector2r const& axis, Polygon const& p);

    void draw(RenderSystem&);
    void destroy(TextManager& textMan, RenderPolygon& renderPol, RenderLine& renderLine, RenderSegment& renderSegment);

    // Drawable flags
    bool collision_axis_1{false};
    bool collision_axis_2{false};
    bool axis_1{false};
    bool axis_2{false};


private:
    // Data structures for the ui
    std::vector<std::pair<Axis, Line>> axes;
    std::vector<Segment> segments;

};
} // namespace CDP