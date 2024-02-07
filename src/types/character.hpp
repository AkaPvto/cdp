#pragma once

#include "vector2r.hpp"

namespace CDP{
struct Character{
    unsigned int textureID; // ID handle of the glyph texture
    unsigned int advance;    // offset to advance to next glyph
    Vector2r size;          // size of the glyph
    Vector2r bearing;       // offset from baseline to left/top of glyph
};

} // namespace CDP