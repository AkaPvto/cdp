#pragma once

#include <string>
#include "render/VAO.hpp"
#include "render/VBO.hpp"
#include "color.hpp"


namespace CDP{

struct TextManager; // Forward declaration to friend the TextManager class
struct RenderText;  // Forward declaration to friend the RenderText class

struct Text{
public:
    Text(std::string s, float x, float y, Color c, unsigned int scl, bool rend) : content{s}, posX{x}, posY{y}, color{c}, scale{scl}, renderable{rend} {}
private:
    std::string content{};
    float posX{}, posY{};
    Color color{};
    unsigned int scale{};
    bool renderable{};

    VAO vao{};
    VBO vbo{};

friend RenderText;
friend TextManager;
};
} // namespace CDP