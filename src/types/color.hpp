#pragma once

#include <cstdint>

uint8_t operator ""_u8(unsigned long long i){
    return uint8_t(i);
}

struct Color{
    uint8_t r{},g{},b{},a{};
    float   r_f{},g_f{},b_f{},a_f{};
    
    Color() = default;
    Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a);
    Color(float _r,float _g, float _b,float _a);
};