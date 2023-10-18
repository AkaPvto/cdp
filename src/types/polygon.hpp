#pragma once

#include <stdint.h>
#include <vector>
#include <SFML/Graphics.hpp>

#include "vector2r.hpp"
#include "precision.h"


namespace CDP{

struct Polygon{
    Polygon() = default;
    Polygon(sf::ConvexShape const&);
    Polygon(std::vector<Vector2r> const&, Vector2r const&);

    sf::ConvexShape const& getShape() const;
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
    sf::Color const&    getColor() const;
    void                setColor(sf::Color const&);
    sf::Color const&    getBorderColor() const;
    void                setBorderColor(sf::Color const&);

    bool fill(sf::ConvexShape const& s);
    bool fill();
    void assign(sf::ConvexShape const& s);
    void update();

    std::vector<Vector2r>::iterator         begin();
    std::vector<Vector2r>::iterator         end();
    std::vector<Vector2r>::const_iterator   begin() const;
    std::vector<Vector2r>::const_iterator   end() const;


    private:
        uint16_t n_vertices{};
        std::vector<Vector2r> vertices;
        Vector2r position{};
        sf::ConvexShape shape{};
};
} // namespace CDP
