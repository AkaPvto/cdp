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
    struct ProjectionData{
        struct Line{
            Vector2r start{};
            Vector2r end{};
        };
        std::vector<Vector2r> pol_vertices;
        Line line1{};
        Line line2{};
    };

    // Methods
    bool colide(Polygon const&, Polygon const&);
    void init_draw(RenderSystem&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void draw(RenderSystem&);
    void update(RenderSystem&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void update_all(RenderSystem&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);

    // Drawable flags
    bool intersection_F {false};
    bool projection_F   {false};
    bool labels_F       {false};

    // Collision flags
    bool axis_x_col{false};
    bool axis_y_col{false};


private:
    // Private methods to module inner operations
    void init_projection(RenderPolygon&, RenderLine&, ProjectionData const&, Color const&);
    void update_segment_color(RenderSegment&, size_t, bool);
    void update_segment_pos(RenderSegment&, size_t, Polygon&);
    void update_projection_color(RenderPolygon&, size_t, bool);
    void update_projection_pos(RenderPolygon&, RenderLine&, size_t, ProjectionData const&);
    ProjectionData getX_projection(Polygon&, float) const;
    ProjectionData getY_projection(Polygon&, float) const;
    void update_color(RenderPolygon&, RenderSegment&);
    
    
    // Data structures
    std::vector<Polygon> projections;
    std::vector<Line>    projection_lines;
    std::vector<Segment> segments;

    // Polygon colors
    Color color1{}, color2{};




};
} // namespace CDP