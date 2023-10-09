#include "algorithm.hpp"

namespace CDP{

struct GJK : Algorithm{
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
    Vector2r supportPoint(Polygon const&, Polygon const&, Vector2r const&);
};
} // namespace CDP
