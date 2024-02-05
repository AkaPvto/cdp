#pragma once

#include <memory>
#include "polygon.hpp"

namespace CDP{

struct RenderPolygon{
    using GLfloat_ptr = std::shared_ptr<GLfloat>;
    using GLuint_ptr = std::shared_ptr<GLuint>;

    RenderPolygon(uint32_t, uint32_t);
    void update_color(Polygon&);
    void update_position(Polygon&);
    void update_buffers(Polygon&);
    void init_buffers(Polygon&);
    void process_data(Polygon&, GLfloat*, GLuint*, GLsizeiptr, GLsizeiptr);
    void delete_buffers(Polygon&);

private:
    uint32_t width{}, height{};
};

} // namespace CDP