#pragma once

#include <cstdint>



namespace CDP{
uint8_t operator ""_u8(unsigned long long i);
    
struct Color{
    uint8_t r{},g{},b{},a{};
    float   r_f{},g_f{},b_f{},a_f{};
    
    Color() = default;
    Color(Color const&) = default;
    Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a);
    Color(float _r,float _g, float _b,float _a);

    void setRed(float);
    void setRed(uint8_t);
    void setGreen(float);
    void setGreen(uint8_t);
    void setBlue(float);
    void setBlue(uint8_t);
    void setAlpha(float);
    void setAlpha(uint8_t);
};
} // namespace CDPº