#pragma once

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
    unsigned int addText(Text const&);
    int getTextLength(size_t index);
    int getTextLength(Text const& text);
    void setTextContent(size_t index, const char*);
    void setTextPos(size_t index, Vector2r pos);
    void setTextColor(size_t index, Color color);
    void setTextScale(size_t index, unsigned int scale);
    void setTextRenderable(size_t index, bool renderable);
    void deleteText(size_t index);
    void render();
    void draw(Text&);
    void end();    
private:
    size_t current_ID{0};
    ShaderProgram shader_p{};
    uint32_t width{}, height{};
    std::map<char, Character> char_set;
    std::map<size_t, Text> text_storage;
};
} // namespace CDP