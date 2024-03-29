#include <vector>
#include <array>
#include <string>

#include "types/polygon.hpp"
#include "algorithm/algorithm.hpp"
#include "types/renderpolygon.hpp"
#include "sys/render.hpp"

#define WINDOW_PERCENTAGE 0.9


namespace CDP{
using PolygonArray = std::vector<Polygon>;


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
    private:
        RenderSystem render;
        RenderPolygon renderPol;
        PolygonArray polygons;
        double const width{};
        double const height{};
        // Static array. Contains pointer to functions for different scenarios initialization
        std::array<Core::FuncType, 3> initialize_types;
        Algorithm* algth{};

        

};

} // namespace CDP
