#include "glad/glad.h"

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// constructor generates the shader on the fly
// ------------------------------------------------------------------------
Shader::Shader(const char* shaderPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;

    fileRead(shaderPath, vertexCode, "#VERTEX", "#VERTEX_END");
    fileRead(shaderPath, fragmentCode, "#FRAGMENT", "#FRAGMENT_END");

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // 2. compile shaders
    unsigned int vertex, fragment;

    // vertex shader and it´s error handling
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment Shader and it´s error handling
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked
    // into the program and are no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// activate the shader
// ------------------------------------------------------------------------
void Shader::use() {
    glUseProgram(ID);
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::getInt(const std::string& name, int& value) const {
    glGetUniformiv(ID, glGetUniformLocation(ID, name.c_str()), &value);
}

void Shader::getFloat(const std::string& name, float& value) const {
    glGetUniformfv(ID, glGetUniformLocation(ID, name.c_str()), &value);
}

// utility function for reading shaders from the same file
void Shader::fileRead(const std::string fileName, std::string shaderCode,
    const std::string start, const std::string end) {

    std::string temp;
    bool shaderFound = false;

    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(fileName);

        while (getline(shaderFile, temp)) {
            if (temp == end) {
                shaderFile.close();
                shaderFound = false;
            }

            if (shaderFound)
                shaderCode += temp;

            if (temp == start)
                shaderFound = true;
        }
    } 
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::" << start
            << "::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}