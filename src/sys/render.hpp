#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/shaderprogram.hpp"
#include "render/VBO.hpp"
#include "render/VAO.hpp"
#include "render/EBO.hpp"

#include "types/color.hpp"


#define BACKGROUND_COLOR    57_u8 , 57_u8 , 57_u8 , 255_u8


namespace CDP{

enum RenderMode{
    STATIC = 0,
    DYNAMIC = 1
};

struct RenderStorage{
    RenderStorage(std::vector<GLfloat>& _v, std::vector<GLuint>& _ib, uint32_t& _li);
    RenderStorage() = delete;
    std::vector<GLfloat>& vertices;
    std::vector<GLuint>& index_buff;
    uint32_t& last_index;
};

struct RenderSystem{
    RenderSystem() = default;
    RenderSystem(const char* name_w, uint32_t width_w, uint32_t height_w, RenderMode rm);
    void init();
    void update();
    void end();

    void drawUI();
    bool isOpen();

    template <typename T>
    void draw(T drawable);


    private:
        // GLFW attributes
        GLFWwindow* window{};
        uint32_t window_width{1280}, window_height{720};
        const char* window_name{"Default window"};
        Color background_color{BACKGROUND_COLOR};
        RenderMode render_mode{RenderMode::STATIC};
    
        // OpenGL attributes
        ShaderProgram shader_P{};
        VAO vao{};
        VBO vbo{};
        EBO ebo{};
        std::vector<GLfloat> vertices;
        std::vector<GLuint> index_buff;
        uint32_t last_index{};

};


} // namespace CDP