#pragma once

#include "vector2r.hpp"

namespace CDP{

struct Character{
    struct Vector2u{
        unsigned int x{}, y{};
    };
    struct Vector2i{
        int x{}, y{};
    };

    unsigned int textureID; // ID handle of the glyph texture
    long advance;    // offset to advance to next glyph
    Vector2u size;          // size of the glyph
    Vector2i bearing;       // offset from baseline to left/top of glyph
};

} // namespace CDP