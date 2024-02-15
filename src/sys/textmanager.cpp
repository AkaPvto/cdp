#include "textmanager.hpp"


#include <glad/glad.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H

#include "types/glerror.hpp"
#include <iostream>

#define CHAR_VERTICES   6   // Number of vertices per character
#define VERTEX_SIZE     4   // Number of floats per vertex

#define SHADER_PATH "src/render/shaders/"  // Shaders path

namespace CDP{
TextManager::TextManager(uint32_t w_, uint32_t h_) : width{w_}, height {h_}{

}

void TextManager::init(){
    FT_Library ft;
    FT_Face face;
    // Freetype functions return 0 if an error occurs, any other integer otherwise
    if(FT_Init_FreeType(&ft)){
        // Throw error message
        std::cout << "ERROR: Freetype initialization failed\n";
        return;
    }


    if(FT_New_Face(ft, "fonts/truetypes/Nexa-Heavy.ttf", 0, &face)){
        // Throw error message
        std::cout << "ERROR: Freetype face creation failed\n";
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for(unsigned char c = 0; c<128; c++){
        // load the character glyph
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
            // Throw error message
            std::cout << "ERROR: Freetype character loader failed\n";
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
                             Character::Vector2u{face->glyph->bitmap.width, face->glyph->bitmap.rows}, 
                             Character::Vector2i{face->glyph->bitmap_left, face->glyph->bitmap_top} };

        char_set[c] = character;

    } // endloop



    // // Check if it's the right place to do this
    FT_Done_Face(face);
    FT_Done_FreeType(ft);


    shader_p.init();
    shader_p.addShader(SHADER_PATH"shader_txt.vert", GL_VERTEX_SHADER);
    shader_p.addShader(SHADER_PATH"shader_txt.frag", GL_FRAGMENT_SHADER);
    shader_p.link();
    shader_p.use();
}


unsigned int TextManager::addText(const char* txt, Vector2r pos, Color color, unsigned int scale, bool render_){
    text_storage.emplace_back(std::string(txt), pos.x, pos.y, color, scale, render_);

    // Prepare the VBO and the VAO
    // Set up of the VBO empty for future insertion of the data
    Text& added_txt = text_storage.back();
    added_txt.vao.bind();
    added_txt.vbo.bind();
    added_txt.vbo.dynamic_insert(NULL, sizeof(GLfloat)*VERTEX_SIZE*CHAR_VERTICES);
    added_txt.vao.addAttrib(0, 4, GL_FLOAT, 4*sizeof(GLfloat), (void*)0);
    added_txt.vbo.unbind();
    added_txt.vao.unbind();

    return text_storage.size()-1;
}

void TextManager::render(){
    if(char_set.size() <= 0) {
        std::cout << "ERROR: The characters map has not been initializated\n";
        return;
    }

    shader_p.use();
    for(auto& text : text_storage){
        if(text.renderable) draw(text);
    }

}

void TextManager::draw(Text& text){
    // Obtain the normalized value of the polygon's position
    uint32_t norm_width = width/2;
    uint32_t norm_height = height/2;

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
        float x = (totalX + ch.bearing.x) * text.scale;
        float y = text.posY - (ch.size.y - ch.bearing.y) * text.scale;

        float w = ch.size.x * text.scale;
        float h = ch.size.y * text.scale;

        // std::cout << "Char: " << *char_ << " with values: " << x << " | " << y << " | " << w << " | " << h << std::endl;

        // update the VBO for each character
        float vertices[CHAR_VERTICES*VERTEX_SIZE] = {
            /*{*/ (x - norm_width)/norm_width,    (y+h-norm_height)/norm_height,    0.0f,   0.0f /*}*/,
            /*{*/ (x - norm_width)/norm_width,    (y-norm_height)/norm_height,      0.0f,   1.0f /*}*/,
            /*{*/ (x+w - norm_width)/norm_width,  (y-norm_height)/norm_height,      1.0f,   1.0f /*}*/,

            /*{*/ (x - norm_width)/norm_width,    (y+h-norm_height)/norm_height,    0.0f,   0.0f /*}*/,
            /*{*/ (x+w - norm_width)/norm_width,  (y-norm_height)/norm_height,      1.0f,   1.0f /*}*/,
            /*{*/ (x+w - norm_width)/norm_width,  (y+h-norm_height)/norm_height,    1.0f,   0.0f /*}*/,
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        //update the VBO
        text.vbo.bind();
        text.vbo.modify(vertices, sizeof(vertices), 0);
        text.vbo.unbind();

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);



        // now advance the global X for the next glyph of the text (note that advance is number of 1/64 pixels)
        totalX += (ch.advance >> 6) * text.scale; // bitshift by 6 to get the value in pixels (2^6 = 64)

    }

    text.vao.unbind();
    glBindTexture(GL_TEXTURE_2D, 0);

    checkGLError("textmanager.cpp", 199);
}

} // namespace CDP
