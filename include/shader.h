#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include "glad/glad.h"
#include <string>


namespace graphics {
    std::string read_file(const char* filename);

    class Shader{
        public:
            GLuint ID;
            Shader(const char* vertexShaderPath, const char* fragShaderFile);
            void activate();
            void Delete();
        private:
            void compileErrors(unsigned int shader, std::string type);
    };
}

#endif // !SHADER_H
