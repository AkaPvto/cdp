#include <SFML/Graphics.hpp>
#include "algorithm/algorithm.hpp"
#include <vector>
#include <string>


#define WINDOW_PERCENTAGE 0.8


namespace CDP{
using ShapesArray = std::vector<sf::Shape*>;


struct Core{
    typedef void(Core::*FuncType)();
    Core(   std::string name = "Collisions",
            double const h = sf::VideoMode::getDesktopMode().height  * WINDOW_PERCENTAGE, 
            double const w = sf::VideoMode::getDesktopMode().width   * WINDOW_PERCENTAGE);
    void run();
    void mouse_movement();
    void check_collision();
    void draw();
    void delete_shapes();
    void initialize(uint32_t const);
    void AABB_init();
    void SAT_init();
    void GJK_init();
    private:
        sf::RenderWindow window;
        ShapesArray shapes;
        double const height{};
        double const width{};
        // Static array. Contains pointer to functions for different scenarios initialization
        std::array<Core::FuncType, 3> initialize_types;
        Algorithm* algth{};

        

};

} // namespace CDP
