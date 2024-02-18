#include "rendersegment.hpp"

#include "types/segment.hpp"

namespace CDP{

RenderSegment::RenderSegment(RenderLine& r_) : renderLine{r_}{

}

void RenderSegment::init_buffers(Segment& segment){
    auto lines = segment.getGlobalLines();

    renderLine.init_buffers(lines[0]);
    renderLine.init_buffers(lines[1]);
    renderLine.init_buffers(lines[2]);
}

void RenderSegment::update_buffers(Segment& segment){
    auto lines = segment.getGlobalLines();

    renderLine.update_buffers(lines[0]);
    renderLine.update_buffers(lines[1]);
    renderLine.update_buffers(lines[2]);
}

void RenderSegment::udpate_vertices(Segment& segment){
    auto lines = segment.getGlobalLines();

    renderLine.udpate_vertices(lines[0]);
    renderLine.udpate_vertices(lines[1]);
    renderLine.udpate_vertices(lines[2]);
}

void RenderSegment::update_color(Segment& segment){
    auto lines = segment.getGlobalLines();

    renderLine.update_color(lines[0]);
    renderLine.update_color(lines[1]);
    renderLine.update_color(lines[2]);
}

void RenderSegment::delete_buffers(Segment& segment){
    auto& lines = segment.getLines();
    
    renderLine.delete_buffers(lines[0]);
    renderLine.delete_buffers(lines[1]);
    renderLine.delete_buffers(lines[2]);
}

} // namespace CDP
