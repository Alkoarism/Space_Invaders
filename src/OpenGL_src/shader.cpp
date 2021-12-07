#include "OpenGL/shader.h"

// activate the shader
// ------------------------------------------------------------------------
void Shader::Use() const{
    glUseProgram(this->ID);
}

// compile shaders already retrieved using the renderer class
// ------------------------------------------------------------------------
void Shader::Compile(const char* vShaderCode, const char* fShaderCode) {
    // compile shaders
    unsigned int vertex, fragment;

    // vertex shader and it´s error handling
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    // fragment Shader and it´s error handling
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    CheckCompileErrors(this->ID, "PROGRAM");

    // delete the shaders as they're linked
    //into the program and are no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::SetGLUniform(const std::string& name, const bool& value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::SetGLUniform(const std::string& name, const int& value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetGLUniform(const std::string& name, const float& value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::SetGLUniform(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv
        (glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::GetGLUniform(const std::string& name, int& value) const {
    glGetUniformiv(ID, glGetUniformLocation(this->ID, name.c_str()), &value);
}

void Shader::GetGLUniform(const std::string& name, float& value) const {
    glGetUniformfv(ID, glGetUniformLocation(this->ID, name.c_str()), &value);
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::CheckCompileErrors(unsigned int shader, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " 
                << type << "\n" << infoLog 
                << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " 
                << type << "\n" << infoLog 
                << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}