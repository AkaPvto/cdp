#include <vector>
#include <array>
#include <string>

#include "types/polygon.hpp"
#include "types/segment.hpp"
#include "algorithm/algorithm.hpp"
#include "render/renderpolygon.hpp"
#include "render/rendersegment.hpp"
#include "sys/render.hpp"
#include "sys/textmanager.hpp"

#define WINDOW_PERCENTAGE 0.9


namespace CDP{
using PolygonList = std::vector<Polygon>;
using SegmentList    = std::vector<Segment>;


struct Core{
    typedef void(Core::*FuncType)();
    Core(   std::string name = "Collisions",
            double const w = DEFAULT_WINDOW_WIDTH * WINDOW_PERCENTAGE,
            double const h = DEFAULT_WINDOW_HEIGHT  * WINDOW_PERCENTAGE); 
    void run();
    void mouse_movement();
    void check_collision();
    void draw_collision();
    void draw();
    void delete_shapes();
    void initialize(uint32_t const);
    void AABB_init();
    void SAT_init();
    void GJK_init();

    // Input
    bool drag_n_drop(Polygon const& p, Vector2r const& mouse);
    int dragg_index = -1;
    bool dragging = false;
    Vector2r drag_starting_pos{-1,-1};


    // UI management
    void update_ui();
    void AABB_ui();
    void SAT_ui();
    void GJK_ui();



    private:
        RenderSystem render;
        RenderPolygon renderPol;
        RenderLine    renderLine;
        RenderSegment renderSegment{renderLine};
        TextManager textMan;
        PolygonList polygons;
        SegmentList    segments;
        double const width{};
        double const height{};
        // Static array. Contains pointer to functions for different scenarios initialization
        std::array<Core::FuncType, 3> initialize_types;
        Algorithm* algth{};

        // UI management attributes
        size_t mode_index{};
        std::array<Core::FuncType, 3> mode_ui;
        bool draw_algth{false};
        

};

} // namespace CDP
