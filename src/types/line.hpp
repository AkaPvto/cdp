#pragma once

#include "vector2r.hpp"
#include "color.hpp"

#include "render/VBO.hpp"
#include "render/VAO.hpp"

namespace CDP{

struct RenderLine;

struct Line{
public:
    Line() = default;
    Line(Vector2r const&, Vector2r const&, Color c = Color(1.0f,1.0f,1.0f,1.0f), float width = 1);

    void setColor(Color const&);
    void setWidth(float);
    void setSmooth(bool);
    void setStipple(bool, uint8_t, uint16_t);

    void draw();
private:
    Vector2r start{}, end{};
    Color color{1.0f,1.0f,1.0f,1.0f};
    float width{1};

    bool smooth{true};
    bool stipple{false};
    uint8_t stipple_factor{1};
    uint16_t stipple_pattern{0x00FF};

    // openGL attributes
    VAO vao;
    VBO vbo;

friend RenderLine;

};

} // namespace CDP