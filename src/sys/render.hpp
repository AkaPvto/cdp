#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1920

#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8
#define SOFT_GREEN          33_u8 , 184_u8, 49_u8 , 255_u8
#define LIGHT_BLUE          72_u8 , 191_u8, 191_u8, 255_u8
#define CREAM_RED           205_u8, 70_u8 , 56_u8 , 255_u8

uint8_t operator ""_u8(unsigned long long i);

namespace CDP{
    
struct Color{
    uint8_t r{},g{},b{},a{};
    float   r_f{},g_f{},b_f{},a_f{};
    
    Color() = default;
    
    Color(uint8_t _r,uint8_t _g, uint8_t _b,uint8_t _a) :
    r{_r}, g{_g}, b{_b}, a{_a}, r_f{_r/255}, g_f{_g/255}, b_f{_b/255}, a_f{_a/255} {}

    Color(float _r,float _g, float _b,float _a) :
    r{_r*255}, g{_g*255}, b{_b*255}, a{_a*255}, r_f{_r}, g_f{_g}, b_f{_b}, a_f{_a} {}
};

struct RenderSystem{
    void init();
    void update();
    void end();

    bool isOpen();


    private:
        GLFWwindow* window{};
        GLuint* VBO;
        GLuint* VAO;
        GLuint* shaderProgram;

};


} // namespace CDP