#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "render/VBO.hpp"
#include "render/EBO.hpp"
#include "render/VAO.hpp"
#include "render/shaderprogram.hpp"

#include "types/color.hpp"

#define DEFAULT_WINDOW_WIDTH    1920
#define DEFAULT_WINDOW_HEIGHT   1080

namespace CDP{

struct Vector2r; // Temporal, migrar al input system

struct RenderSystem{
    void init(int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, const char* name = "Window");
    void end();
    bool isOpen();

    template <typename DrawType>
    void update(DrawType*, int);

    // Temporal, migrar al input system
    void getMousePos(Vector2r& v);
    bool isKeyPressed(int key);

    void setBackgroundColor(Color const& c);

    private:
        GLFWwindow* window{};
        ShaderProgram shader_p;
        Color background_color{};

};

} // namespace CDP