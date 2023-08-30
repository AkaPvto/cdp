#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define WINDOW_PERCENTAGE 0.8


namespace CDP{
using ShapesArray = std::vector<sf::Shape*>;
struct Core{
    
    Core(   std::string name = "Collisions",
            double const h = sf::VideoMode::getDesktopMode().height  * WINDOW_PERCENTAGE, 
            double const w = sf::VideoMode::getDesktopMode().width   * WINDOW_PERCENTAGE);
    void run();
    void draw();

    private:
        sf::RenderWindow window;
        ShapesArray shapes;
        double const height{};
        double const width{};

};

} // namespace CDP
