#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/VBO.hpp"
#include "render/EBO.hpp"
#include "render/VAO.hpp"
#include "render/shaderprogram.hpp"

#include "types/color.hpp"

#define DEFAULT_WINDOW_WIDTH    1920
#define DEFAULT_WINDOW_HEIGHT   1080

struct ImFont;
namespace CDP{
struct Vector2r; // Temporal, migrar al input system

struct RenderSystem{
    void init(int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, const char* name = "Window");
    void end();
    void resolve();
    bool isOpen();
    void update_init();

    template <typename DrawType>
    void draw(DrawType*, int);

    // Get window dimensions
    int getWidth() const;
    int getHeight() const;
  
    // Acces to the loaded fonts
    ImFont* getLightFont() const;
    ImFont* getHeavyFont() const;

    // Temporal, migrar al input system
    void getMousePos(Vector2r& v);
    bool isKeyPressed(int key);
    bool isMousePressed(int key);

    void setBackgroundColor(Color const& c);

    private:
        GLFWwindow* window{};
        ShaderProgram shader_p;
        Color background_color{};
        void(*user_interface)();
        ImFont* font_l{nullptr};
        ImFont* font_h{nullptr};
};


} // namespace CDP