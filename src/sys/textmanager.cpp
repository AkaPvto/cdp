#include "textmanager.hpp"

#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H


#define CHAR_VERTICES   6   // Number of vertices per character
#define VERTEX_SIZE     4   // Number of floats per vertex

namespace CDP{

void TextManager::init(){
    FT_Library ft;
    // Freetype functions return 0 if an error occurs, any other integer otherwise
    if(FT_Init_FreeType(&ft)){
        // Throw error message
        return;
    }

    FT_Face face;
    if(FT_New_Face(ft, "truetype/Nexa-Heavy.tff", 0, &face)){
        // Throw error message
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for(unsigned char c = 0; c<128; c++){
        // load the character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            // Throw error message
            continue;
        }

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* data);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // store the character into the map
        Character character{ texture, 
                             face->glyph->advance.x, 
                             Vector2r{face->glyph->bitmap.width, face->glyph->bitmap.rows}, 
                             Vector2r{face->glyph->bitmap_left, face->glyph->bitmap_top} };
        
    } // endloop



    // // Check if it's the right place to do this
    // FT_Done_Face(face);
    // FT_Done_FreeType(ft);


    shader_p.init();
    shader_p.addShader("render/shaders/shader_txt.vert", GL_VERTEX_SHADER);
    shader_p.addShader("render/shaders/shader_txt.frag", GL_FRAGMENT_SHADER);
    shader_p.link();


    // glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    // shader_p.getUniform("");
    // glUniformMatrix4fv()
    // glUniformMatrix4fv(shader_p.getUniform("projection"), )
    // glUniform3(shader_p.getUniform("projection"), text.color.r_f, text.color.g_f, text.color.b_f);
}

void TextManager::render(){
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader_p.use();

    for(auto& text : text_storage){
        if(text.renderable) draw(text);

    }

    glDisable(GL_BLEND);
}

void TextManager::draw(Text& text){
    // set the text color into the shader uniform and set render state
    glUniform3f(shader_p.getUniform("textColor"), text.color.r_f, text.color.g_f, text.color.b_f);
    glActiveTexture(GL_TEXTURE0);
    text.vao.bind();


    // overall x position of the string
    float totalX = text.posX;

    std::string::const_iterator char_;
    // Iterate through all the characters from the string one by one
    for(char_ = text.content.begin(); char_ != text.content.end(); char_++){
        // Obtain the character from the char_set map
        Character ch = char_set.at(*char_);

        // Obtain the position of the char with margins and bearing
        float x = totalX + ch.bearing.x * text.scale;
        float y = text.posY - (ch.size.y - ch.bearing.y) * text.scale;

        float w = ch.size.x * text.scale;
        float h = ch.size.y * text.scale;

        // update the VBO for each character
        float vertices[CHAR_VERTICES][VERTEX_SIZE] = {
            { x,    y+h,    0.0f,   0.0f },
            { x,    y,      0.0f,   1.0f },
            { x+w,  y,      1.0f,   1.0f },

            { x,    y+h,    0.0f,   0.0f },
            { x+w,  y,      1.0f,   1.0f },
            { x+w,  y+h,    1.0f,   0.0f },
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        //update the VBO
        text.vbo.bind();
        text.vbo.modify(&vertices[0][0], sizeof(vertices), 0);
        text.vbo.unbind();

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // now advance the global X for the next glyph of the text (note that advance is number of 1/64 pixels)
        totalX += (ch.advance >> 6) * text.scale; // bitshift by 6 to get the value in pixels (2^6 = 64)

    }

    text.vao.unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

}

} // namespace CDP
