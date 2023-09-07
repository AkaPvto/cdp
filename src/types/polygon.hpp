#pragma once

#include <stdint.h>
#include <vector>

#include "vector2r.hpp"
#include "precision.h"

namespace sf{ struct Shape; }

namespace CDP{

struct Polygon{
    bool fill(sf::Shape const* s);
    
    uint16_t n_vertices{};
    std::vector<Vector2r> vertices;
    Vector2r position{};
};
} // namespace CDP
