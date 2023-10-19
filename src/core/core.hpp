#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "types/polygon.hpp"
#include "algorithm/algorithm.hpp"

#define WINDOW_PERCENTAGE 0.9


namespace CDP{
using PolygonArray = std::vector<Polygon>;


struct Core{
    typedef void(Core::*FuncType)();
    Core(   std::string name = "Collisions",
            double const h = sf::VideoMode::getDesktopMode().height  * WINDOW_PERCENTAGE, 
            double const w = sf::VideoMode::getDesktopMode().width   * WINDOW_PERCENTAGE);
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
        sf::RenderWindow window;
        PolygonArray polygons;
        double const height{};
        double const width{};
        // Static array. Contains pointer to functions for different scenarios initialization
        std::array<Core::FuncType, 3> initialize_types;
        Algorithm* algth{};

        

};

} // namespace CDP
