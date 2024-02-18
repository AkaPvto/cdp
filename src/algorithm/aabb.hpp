#include "algorithm.hpp"
#include "types/polygon.hpp"
#include "types/segment.hpp"

#include <vector>
#include <string>

namespace CDP{

struct RenderSystem;
struct RenderPolygon;
struct RenderLine;
struct RenderSegment;
struct TextManager;

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

    struct LabelData{
        Vector2r startPos{};
        Vector2r endPos{};
        std::string start_c{};
        std::string end_c{};  
    };

    // Methods
    bool colide(Polygon const&, Polygon const&);
    void init_draw(RenderSystem&, TextManager&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void draw(RenderSystem&);
    void update(RenderSystem&, TextManager&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void update_all(RenderSystem&, TextManager&, RenderPolygon&, RenderSegment&, RenderLine&, Polygon&, Polygon&);
    void toggle_labels(TextManager&) const;
    void destroy(TextManager&, RenderPolygon&, RenderLine&, RenderSegment&);

    // Drawable flags
    bool intersection_F {false};
    bool projection_F   {false};
    bool labels_F       {false};

    // Collision flags
    bool axis_x_col{false};
    bool axis_y_col{false};


private:
    // Private methods to module inner operations
    void init_label(TextManager&);
    void init_projection(RenderPolygon&, RenderLine&, ProjectionData const&, Color const&);
    void update_segment_color(RenderSegment&, size_t, bool);
    void update_segment_pos(RenderSegment&, size_t, Polygon&);
    void update_projection_color(RenderPolygon&, size_t, bool);
    void update_projection_pos(RenderPolygon&, RenderLine&, size_t, ProjectionData const&);
    ProjectionData getX_projection(Polygon&, float) const;
    ProjectionData getY_projection(Polygon&, float) const;
    void update_label_color(TextManager&, size_t, bool);
    void update_label(TextManager& textMan, LabelData const& data, size_t index);
    LabelData getX_label(TextManager&, Segment&) const;
    LabelData getY_label(TextManager&, Segment&) const;
    void update_color(TextManager&, RenderPolygon&, RenderSegment&);

    
    
    // Data structures
    std::vector<Polygon> projections;
    std::vector<Line>    projection_lines;
    std::vector<Segment> segments;
    std::vector<size_t>  labels; // { xMin_1, xMax_1, xMin_2, xMax_2, yMin_1, yMax_1, yMin_2, yMax_2 }

    // Polygon colors
    Color color1{}, color2{};




};
} // namespace CDP