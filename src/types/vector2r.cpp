#include <cmath>

#include "vector2r.hpp"

namespace CDP{
Vector2r& Vector2r::operator=(Vector2r const& v){
    x = v.x;
    y = v.y;
    return *this;
}

Vector2r Vector2r::operator+=(Vector2r const& v){
    return Vector2r{ .x = this->x + v.x, .y = this->y + v.y};
}

Vector2r Vector2r::operator-=(Vector2r const& v){
    return Vector2r{ .x = this->x - v.x, .y = this->y - v.y};
}

Vector2r Vector2r::operator-() const{
    return Vector2r{-x, -y};
}

real Vector2r::operator*=(Vector2r const& v){
    return (*this)*v;
}

Vector2r Vector2r::getNormal(){
    return Vector2r{ .x = -y, .y = x};
}

real Vector2r::getSquaredMagnitud(){
    return x*x + y*y;
}

real Vector2r::getMagnitud(){
    return sqrt(getSquaredMagnitud());
}

Vector2r Vector2r::getNormalized(){
    real magn = getMagnitud();
    return Vector2r{ .x = x/magn, .y = y/magn };
}

real Vector2r::dot(Vector2r const& v){
    return (*this)*v;
}

Vector2r operator+(Vector2r const& v1, Vector2r const& v2){
    return Vector2r{ .x = v1.x + v2.x, .y = v1.y + v2.y};
}

Vector2r operator-(Vector2r const& v1, Vector2r const& v2){
    return Vector2r{ .x = v1.x - v2.x, .y = v1.y - v2.y};
}

real operator*(Vector2r const& v1, Vector2r const& v2){
    return v1.x*v2.x + v1.y*v2.y;
}

} // namespace CDP
