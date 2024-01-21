#include "color.hpp"
    
namespace CDP{

uint8_t operator ""_u8(unsigned long long i){
    return uint8_t(i);
}

Color::Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a) :
    r{_r}, g{_g}, b{_b}, a{_a}, r_f{_r/255.0f}, g_f{_g/255.0f}, b_f{_b/255.0f}, a_f{_a/255.0f} {}

Color::Color(float _r,float _g, float _b,float _a) :
    r{uint8_t(_r*255)}, g{uint8_t(_g*255)}, b{uint8_t(_b*255)}, a{uint8_t(_a*255)}, r_f{_r}, g_f{_g}, b_f{_b}, a_f{_a} {}

} // namespace CDP