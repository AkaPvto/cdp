#include "algorithm.hpp"
#include "types/polygon.hpp"
#include "types/segment.hpp"

#include <vector>

namespace CDP{

struct RenderSystem;
struct RenderPolygon;
struct RenderLine;
struct RenderSegment;

// AABB stands for Axis-Aligned Bounding Box
// AABB collision detection asumes regular polygons with 4 vertices and not rotary
struct AABB : Algorithm{
    bool colide(Polygon const&, Polygon const&);
    void init_draw(RenderSystem&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void update(RenderSystem&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void draw(RenderSystem&);

    // Drawable flags
    bool intersection_F {false};
    bool projection_F   {false};
    bool labels_F       {false};


private:
    // Projections
    std::vector<Polygon> projections;
    std::vector<Line>    projection_lines;
    std::vector<Segment> segments;


};
} // namespace CDP