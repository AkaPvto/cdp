#pragma once

#include "types/line.hpp"

namespace CDP{
struct RenderLine{
    RenderLine(uint32_t, uint32_t);
    void init_buffers(Line&);
    void update_buffers(Line&);
    void udpate_vertices(Line&);
    void update_color(Line&);
    void process_data(Line&, GLfloat*, GLuint*);
    void delete_buffers(Line&);

private:
    uint32_t width{}, height{};
};
} // namespace CDP