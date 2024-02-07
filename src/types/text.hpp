#pragma once

#include <string>
#include "render/VAO.hpp"
#include "render/VBO.hpp"
#include "color.hpp"

struct TextManager; // Forward declaration to friend the TextManager class
struct RenderText;  // Forward declaration to friend the RenderText class

namespace CDP{
struct Text{
private:
    std::string content{};
    unsigned int scale{};
    float posX{}, posY{};
    Color color{};
    bool renderable{};

    VAO vao;
    VBO vbo;

friend RenderText;
friend TextManager;
};
} // namespace CDP