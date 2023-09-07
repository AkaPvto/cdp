#pragma once
#include "types/polygon.hpp"

namespace CDP{


struct Algorithm{
    virtual bool colide(Polygon const&, Polygon const&) = 0;
    virtual ~Algorithm() = default;
};
} // namespace CDP
