#include <stdint.h>
#include <array>

using real = float;

namespace sf{ struct Shape; }

namespace CDP{
using Vertex = std::array<real, 2>;

template <uint16_t I>
struct Polygon{
    Polygon();
    bool fill(sf::Shape const* s);
    
    private:    
        uint16_t n_vertices{};
        std::array<Vertex, I> vertices;
        std::array<real, 2> position;
};
} // namespace CDP
