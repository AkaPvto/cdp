#include "algorithm.hpp"

namespace CDP{

struct GJK : Algorithm{
    bool colide(Polygon const&, Polygon const&);
};
} // namespace CDP
