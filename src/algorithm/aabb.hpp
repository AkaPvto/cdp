#include "algorithm.hpp"
#include "types/polygon.hpp"

using Drawable_rect = std::array<sf::RectangleShape, 4>;
using Drawable_line = std::vector<sf::VertexArray>;
namespace CDP{
// AABB stands for Axis-Aligned Bounding Box
// AABB collision detection asumes regular polygons with 4 vertices and not rotary
struct AABB : Algorithm{
    bool colide(Polygon const&, Polygon const&);
    void draw(DrawList&, Polygon const&, Polygon const&, int, int);

    // Drawable flags
    bool proyection_F   {true};
    bool intersection_F {false};

    // Drawable objects
    struct Drawable{
        Drawable_line lines{};
        Drawable_rect rectangles{};
    };
    Drawable drawables{};


};
} // namespace CDP