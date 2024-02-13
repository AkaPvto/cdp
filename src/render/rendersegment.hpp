#pragma once

#include "renderline.hpp"

namespace CDP{
struct RenderSegment{
    RenderSegment(RenderLine&);
    void init_buffers(Segment&);
    void update_buffers(Segment&);
    void udpate_vertices(Segment&);
    void update_color(Segment&);
    void delete_buffers(Segment&);

private:
    RenderLine& renderLine;
};
} // namespace CDP
