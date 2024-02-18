#include "gjk.hpp"

#include <iostream>


namespace CDP{
    
bool GJK::colide(Polygon const& p1, Polygon const& p2){
    // Get initial support point
    Vector2r supp = getSupportPoint(p1, p2, Vector2r{1,0});

    // Initialize the simplex first vertex with the support point
    Simplex splx{};
    splx.push_first(supp);

    // The new search direction will be towards the (0, 0)
    Vector2r searchDirection = -supp;

    // Get the second support point to form a Line
    // Line is the lower Simplex possible, from here we can iterate
    supp = getSupportPoint(p1, p2, searchDirection);
    
    // Insert the second support point into the Simplex to make a Line
    splx.push_first(supp);

    // If the new support point is in the opposite direction of the search direction
    // Means that we tried to look up for points in the direction of the (0, 0) but the further point doesn't reach it
    // Thus the polygons don't collide
    while(similarDirection(supp, searchDirection)){
        
        // If the full simplex processing logic returns true, we found a Simplex containing (0 ,0)
        if(updateSimplex(splx, searchDirection)) return true;

        // Otherwise, search for new point and go next iteration
        supp = getSupportPoint(p1, p2, searchDirection);
    
        // Insert the support point into the Simplex
        splx.push_first(supp);
    }
    return false;
}

Vector2r GJK::getFurtherVertex(Polygon const& p, Vector2r const& direction){
    real max_dist = -__FLT_MAX__;
    Vector2r max_v{};

    for(Vector2r v : p){
        v += p.getPosition();
        if(real it_dist = v*direction; it_dist > max_dist ){
            max_dist = it_dist;
            max_v = v;
        }
    }

    return max_v;
}

Vector2r GJK::getSupportPoint(Polygon const& p1, Polygon const& p2, Vector2r const& direction){
    return getFurtherVertex(p1, direction) - getFurtherVertex(p2, -direction);    
}


bool GJK::updateSimplex(Simplex& s, Vector2r& direction){
    switch(s.getSize()){
        case 2:
            return onedimensional(s, direction);
            break;
        case 3:
            return bidimensional(s, direction);
            break;
        // case 4:
        //     return tridimensional(s, direction);
        //     break;
        default:
            return false;
            break;
    }
    return false;
}

bool GJK::onedimensional(Simplex& s, Vector2r& direction){
    Vector2r a = s[0];
    Vector2r b = s[1];

    Vector2r ab = b-a;
    Vector2r ao =  -a;
    
    // AB and AO are in the same direction
    if(similarDirection(ab, ao)){
        direction = ab.getNormal();
        real abn_dot_ao = direction*ao;
        int sign = abs(abn_dot_ao)/(abn_dot_ao);
        direction *= sign;
    }
    else{
        s = {a};
        direction = ao;
    }

    return false;
}

bool GJK::bidimensional(Simplex& s, Vector2r& direction){
    Vector2r a = s[0];
    Vector2r b = s[1];
    Vector2r c = s[2];

    Vector2r ab = b-a;
    Vector2r ac = c-a;
    Vector2r ao =  -a;

    // Get both AC and AB edge's normals
    Vector2r ac_normal = ac.getNormal();
    Vector2r ab_normal = ab.getNormal();
    // Get the product between any of those normals and the other original edge to find the angular orientation of the edges
    real acn_dot_ab = ac_normal*ab;
    // Get the sign of the orientation to correct the normal direction
    int points_orientation = abs(acn_dot_ab)/acn_dot_ab;
    // We correct the normal direction
    ac_normal *= (-1)*points_orientation;
    ab_normal *= points_orientation;
    

    // Logic for the case where the origin is in the pure A region
    auto region_A = [&](){
        s = {a};
        direction = ao;
        return false;
    };

    // Logic for the case where the origin is in one of the edge's regions
    auto region_edge = [&](Vector2r p1, Vector2r p2, Vector2r edge_n){
        s = {p1, p2};
        direction = edge_n;
        return onedimensional(s, direction);
    };

    // origin in the AC plane
    if(similarDirection(ac_normal, ao)){
        // origin in the AC edge region
        if(similarDirection(ac, ao)) region_edge(a, c, ac_normal);
        // origin in the pure A region
        else region_A();
    }
    // origin in the AB plane
    else if(similarDirection(ab_normal, ao)){
        // origin in the AB edge region
        if(similarDirection(ab, ao)) region_edge(a, b, ab_normal);
        // origin in the pure A region
        else region_A();
    }
    else return true;
    
    return false;
}

// bool tridimensional(Simplex& s, Vector2r& direction){}

// Checks if the angular distance between two Vector2r
// returns true if it's less than 90 degrees, false otherwise
bool GJK::similarDirection(Vector2r const& v1, Vector2r const& v2){
    return v1*v2 > 0;
}


void GJK::draw(RenderSystem& render){

}

void GJK::destroy(TextManager& textMan, RenderPolygon& renderPol, RenderLine& renderLine, RenderSegment& renderSegment){

}

GJK::Vector3r GJK::toVector3r(Vector2r const& v) const{
    return Vector3r{v.x, v.y, 0};
}

Vector2r GJK::toVector2r(Vector3r const& v) const{
    return Vector2r{v.x, v.y};
}


// ##### Simplex definitions #####

GJK::Simplex& GJK::Simplex::operator=(std::initializer_list<Vector2r> init_list){
    vertices.fill(Vector2r{});
    size = 0;
    for(Vector2r v : init_list){
        vertices[size++] = v;
    }

    return *this;
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

// #####   Simplex end     #####

// Cross product definition
GJK::Vector3r operator%(GJK::Vector3r const& v1, GJK::Vector3r const& v2){
    return GJK::Vector3r{v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x};
}

} // namespace CDP
