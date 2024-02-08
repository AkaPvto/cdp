#pragma once

#include <vector>
#include <map>

#include "types/text.hpp"
#include "types/character.hpp"
#include "render/shaderprogram.hpp"

namespace CDP{
struct TextManager{
    TextManager() = delete;
    TextManager(uint32_t, uint32_t);
    TextManager(TextManager&&) = default;
    TextManager(TextManager const&) = delete;


    void init();
    unsigned int addText(const char* txt, Vector2r pos, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), unsigned int scale = 1, bool render_ = false );
    void render();
    void draw(Text&);    
private:
    ShaderProgram shader_p{};
    uint32_t width{}, height{};
    std::map<char, Character> char_set;
    std::vector<Text> text_storage;
};
} // namespace CDP