#include "gjk.hpp"
#include <iostream>

namespace CDP{
    
bool GJK::colide(Polygon const& p1, Polygon const& p2){
    return false;
}

Vector2r GJK::getFurtherVertex(Polygon const& p, Vector2r const& direction){
    real max_dist = -__FLT_MAX__;
    Vector2r max_v{};

    for(Vector2r const& v : p){
        if(real it_dist = v*direction; it_dist > max_dist ){
            max_dist = it_dist;
            max_v = v;
        }
    }

    return max_v;
}

Vector2r GJK::supportPoint(Polygon const& p1, Polygon const& p2, Vector2r const& direction){
    return getFurtherVertex(p1, direction) - getFurtherVertex(p2, -direction);    
}



// ##### Simplex definitions #####

GJK::Simplex& GJK::Simplex::operator=(std::initializer_list<Vector2r> init_list){
    vertices.fill(Vector2r{});
    size = 0;
    for(Vector2r v : init_list){
        vertices[size++] = v;
    }
}

Vector2r& GJK::Simplex::operator[](int i){
    return vertices[i];
}

Vector2r const& GJK::Simplex::at(int i) const{
    return vertices.at(i);
}

void GJK::Simplex::push_first(Vector2r const& v){
    size++;
    vertices = {v, vertices.at(0), vertices.at(1)};
}

uint8_t GJK::Simplex::getSize() const{
    return size;
}


std::array<Vector2r, 3>::const_iterator GJK::Simplex::begin() const{
    return vertices.begin();
}

std::array<Vector2r, 3>::const_iterator GJK::Simplex::end() const{
    return vertices.end() - (4-size);
}

} // namespace CDP
