#include "algorithm.hpp"

#include <array>

namespace CDP{

struct GJK : Algorithm{
    struct Vector3r{ 
        real x{}, y{}, z{}; 
        // Cross product
    };
    
    struct Simplex{
        std::array<Vector2r, 3> vertices{};
        uint8_t size{};

        Simplex& operator=(std::initializer_list<Vector2r>);
        Vector2r& operator[](int i);
        Vector2r const& at(int i) const;
        void push_first(Vector2r const&);
        uint8_t getSize() const;
        std::array<Vector2r, 3>::const_iterator begin() const;
        std::array<Vector2r, 3>::const_iterator end() const;
    };

    bool colide(Polygon const&, Polygon const&);
    Vector2r getFurtherVertex(Polygon const& , Vector2r const&);
    Vector2r getSupportPoint(Polygon const&, Polygon const&, Vector2r const&);

    Vector3r toVector3r(Vector2r const&) const;
    Vector2r toVector2r(Vector3r const&) const;

    bool updateSimplex(Simplex& s, Vector2r& direction);
    bool onedimensional(Simplex&, Vector2r&);
    bool bidimensional(Simplex&, Vector2r&);
    // bool tridimensional(Simplex&, Vector2r&);
    bool similarDirection(Vector2r const&, Vector2r const&);
    
    // typedef bool(GJK::*gjk_func)(Simplex&, Vector2r&);
    // std::array<gjk_func, 2> updateSimplex{onedimensional, bidimensional};

    void draw(DrawList&, Polygon const&, Polygon const&, int, int);

};

// Cross product operator for Vector3r class
GJK::Vector3r operator%(GJK::Vector3r const& v1, GJK::Vector3r const& v2);

} // namespace CDP
