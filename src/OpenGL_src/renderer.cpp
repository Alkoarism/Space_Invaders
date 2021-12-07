#include "OpenGL/renderer.h"

void Renderer::Render
	(const VertexArray& va, const IndexBuffer& ib, const std::string sName) {
		va.Bind();
		ib.Bind();
        shaders[sName].Use();
		shaders[sName].SetUniform("projection", projection);
		shaders[sName].SetUniform("view", view);
		shaders[sName].SetUniform("model", model);

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	}

void Renderer::RenderConfig
	(const float& r, const float& g,
	 const float& b, const float& a) {

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FrameTimeTracker() {
	const float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

Shader Renderer::LoadShader(std::string name, const char* vertexPath, const char* fragmentPath) {
    shaders[name] = LoadShaderFromFile(vertexPath, fragmentPath);
    return shaders[name];
}

Shader Renderer::GetShader(const std::string name) {
    return shaders[name];
}

void Renderer::Clear() {
    // (properly) delete all shaders
    for (auto s : shaders)
        glDeleteProgram(s.second.ID);
}

Shader Renderer::LoadShaderFromFile(const char* vertexPath, const char* fragmentPath) {
	    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);
    return shader;
}

float Renderer::lastFrame = 0.0f;
float Renderer::deltaTime = 0.0f;
glm::mat4 Renderer::projection = glm::mat4(1.0f);
glm::mat4 Renderer::view = glm::mat4(1.0f);
glm::mat4 Renderer::model = glm::mat4(1.0f);
std::map<std::string, Shader> Renderer::shaders;
