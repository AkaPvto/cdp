#pragma once

#include <array>
#include "line.hpp"
namespace CDP{

struct Segment{
    Segment() = delete;
    Segment(Segment const&) = default;
    Segment(Segment&&) = default;
    Segment(Vector2r const&, float, float, float, float, Color const&);


    Vector2r getPos() const;
    void setPos(Vector2r const&);
    Color const& getColor() const;
    void setColor(Color const&);
    float getLength() const;
    void setLength(float l);
    float getHeight() const;
    void setHeight(float h);
    float getWidth() const;
    void setWidth(float w);

    void update();
    std::array<Line, 3> getGlobalLines() const;
    void draw();

    private:
        Vector2r pos{};
        // Space between the ends of the segment
        float length{};
        // Length of the vertical lines at both ends of the segment
        float height{};
        // Width of the segments lines
        float width{1};
        // Rotation of the segment
        float rotation{0};
        // Color of the segment (white by default)
        Color color{1.0f,1.0f,1.0f,1.0f};

        // In a segment with this structure:     |-------------------|
        // This are the index for the lines:     0         2         1
        std::array<Line, 3> segment_lines;
        
        
        std::array<Line, 3>& getLines();


    friend struct RenderSegment;
};

} // namespace CDP