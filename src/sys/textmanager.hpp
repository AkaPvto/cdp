#pragma once

#include <vector>
#include <map>

#include "types/text.hpp"
#include "types/character.hpp"
#include "render/shaderprogram.hpp"

namespace CDP{
struct TextManager{
    TextManager() = default;
    TextManager(TextManager&&) = default;
    TextManager(TextManager const&) = delete;


    void init();
    void render();
    void draw(Text&);    
private:
    ShaderProgram shader_p{};
    std::map<char, Character> char_set;
    std::vector<Text> text_storage;
};
} // namespace CDP