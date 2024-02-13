#pragma once


namespace CDP{
struct Polygon;
struct RenderSystem;

struct Algorithm{
    virtual bool colide(Polygon const&, Polygon const&) = 0;
    virtual void draw(RenderSystem&) = 0;
    virtual ~Algorithm() = default;

    signed char change_F{-1};
};
} // namespace CDP
