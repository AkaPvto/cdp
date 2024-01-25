#pragma once

#include <stdint.h>
#include <vector>

#include "vector2r.hpp"
#include "precision.h"
#include "color.hpp"
#include "render/VBO.hpp"
#include "render/EBO.hpp"
#include "render/VAO.hpp"

namespace CDP{
struct RenderPolygon;

struct Polygon{
    Polygon() = default;
    Polygon(std::vector<Vector2r> const&, Vector2r const&);

    int                 getVertexCount() const;
    Vector2r            getCenter() const;
    Vector2r            getVertex(int) const;
    Vector2r            getLocalVertex(int) const;
    void                setVertex(Vector2r const& v, int index);
    void                setVertices(std::vector<Vector2r> const&);
    Vector2r            getPosition() const;
    void                setPosition(Vector2r const&);
    real                getBorder() const;
    void                setBorder(real const& b);
    Color const&        getColor() const;
    void                setColor(Color const&);
    Color const&        getBorderColor() const;
    void                setBorderColor(Color const&);

    int getEBOsize();
    void normalize_vertices(uint32_t width, uint32_t height);
    void draw();


    std::vector<Vector2r>::iterator         begin();
    std::vector<Vector2r>::iterator         end();
    std::vector<Vector2r>::const_iterator   begin() const;
    std::vector<Vector2r>::const_iterator   end() const;


    private:
        uint16_t n_vertices{};
        std::vector<Vector2r> vertices;
        Vector2r position{};
        Color color{};
        Color border_color{};
        real border_size{};
        VAO vao;
        VBO vbo;
        EBO ebo;

    friend RenderPolygon;
};
} // namespace CDP
