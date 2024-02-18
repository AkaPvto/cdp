#include "text.hpp"

namespace CDP{
    
void Text::destroy(){
    vbo.destroy();
    vao.destroy();
}
} // namespace CDP
