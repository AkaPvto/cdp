#pragma once
#include "types/polygon.hpp"

namespace sf{ struct Drawable; }
namespace CDP{
using DrawList = std::vector<sf::Drawable*>;
struct Algorithm{
    virtual bool colide(Polygon const&, Polygon const&) = 0;
    virtual void draw(DrawList&, Polygon const&, Polygon const&, int, int) = 0;
    virtual ~Algorithm() = default;
};
} // namespace CDP
