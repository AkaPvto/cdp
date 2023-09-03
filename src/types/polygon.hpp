#pragma once

#include <stdint.h>
#include <vector>

using real = float;

namespace sf{ struct Shape; }

namespace CDP{
struct Vertex{
    real x{},y{};
};

struct Polygon{
    bool fill(sf::Shape const* s);
    
    uint16_t n_vertices{};
    std::vector<Vertex> vertices;
    Vertex position{};
};
} // namespace CDP
