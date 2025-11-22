#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "shader.h"

namespace graphics {
    class Texture {
        public:
            GLuint ID;
            GLenum type;
            Texture(std::string texture_path, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
            void textUnit(Shader& shader, const char* uniform, GLuint unit);
            void Bind();
            void Unbind();
            void Delete();
    };
}

#endif 
