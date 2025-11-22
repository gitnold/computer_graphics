#include "../include/shader.h"
#include <filesystem>
#include <fstream>
#include <ios>
#include <string>
#include <iostream>

namespace graphics {
    // read files given a path, in our case shaders/glsl files.
    std::string read_file(const char *filename) {
        //get file size.
        auto file_size = std::filesystem::file_size(filename);
        //declare buffer to store the data.
        std::string buffer(file_size, '\0');

        //open a file stream and read file contents into a string
        std::ifstream file(filename, std::ios::binary);
        file.read(buffer.data(), file_size);

        return buffer;
    }

    Shader::Shader(const char* vertexShaderFile, const char* fragShaderFile) {

        // Read vertexFile and fragmentFile and store the strings
    	std::string vertexCode = read_file(vertexShaderFile);
    	std::string fragmentCode = read_file(fragShaderFile);

    	// Convert the shader source strings into character arrays
    	const char* vertexSource = vertexCode.c_str();
    	const char* fragmentSource = fragmentCode.c_str();

    	// Create Vertex Shader Object and get its reference
    	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    	// Attach Vertex Shader source to the Vertex Shader Object
    	glShaderSource(vertexShader, 1, &vertexSource, NULL);
    	// Compile the Vertex Shader into machine code
    	glCompileShader(vertexShader);
    	// Checks if Shader compiled succesfully
    	this->compileErrors(vertexShader, "VERTEX");

    	// Create Fragment Shader Object and get its reference
    	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    	// Attach Fragment Shader source to the Fragment Shader Object
    	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    	// Compile the Vertex Shader into machine code
    	glCompileShader(fragmentShader);
    	// Checks if Shader compiled succesfully
    	this->compileErrors(fragmentShader, "FRAGMENT");

    	// Create Shader Program Object and get its reference
    	ID = glCreateProgram();
    	// Attach the Vertex and Fragment Shaders to the Shader Program
    	glAttachShader(ID, vertexShader);
    	glAttachShader(ID, fragmentShader);
    	// Wrap-up/Link all the shaders together into the Shader Program
    	glLinkProgram(ID);
    	// Checks if Shaders linked succesfully
    	this->compileErrors(ID, "PROGRAM");

    	// Delete the now useless Vertex and Fragment Shader objects
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);

    }

    void Shader::activate() {
        glUseProgram(this->ID);
    }

    void Shader::Delete() {
        glDeleteProgram(this->ID);
    }

    void Shader::compileErrors(unsigned int shader, std::string type) {
        // Stores status of compilation
    	GLint hasCompiled;
    	// Character array to store error message in
    	char infoLog[1024];
    	if (type != "PROGRAM")
    	{
    		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
    		if (hasCompiled == GL_FALSE)
    		{
    			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
    		}
    	}
    	else
    	{
    		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
    		if (hasCompiled == GL_FALSE)
    		{
    			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
    			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
    		}
    	}
    }
}
