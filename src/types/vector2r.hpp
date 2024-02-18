#pragma once

#include "precision.h"
namespace CDP{
    
struct Vector2r{
    real x{},y{};

    Vector2r& operator=(Vector2r const& v);
    Vector2r& operator+=(Vector2r const& v);
    Vector2r& operator-=(Vector2r const& v);
    Vector2r& operator*=(real const& r);
    Vector2r operator-() const;
    Vector2r getNormal();
    real getSquaredMagnitud();
    real getMagnitud();
    real dot(Vector2r const&);
    Vector2r getNormalized();
    Vector2r getRotated(real);
};
Vector2r operator+(Vector2r const& v1, Vector2r const& v2);
Vector2r operator-(Vector2r const& v1, Vector2r const& v2);
real operator*(Vector2r const& v1, Vector2r const& v2);
Vector2r operator*(Vector2r const&, real const& r);
Vector2r operator*(real const& r, Vector2r const&);


} // namespace CDP