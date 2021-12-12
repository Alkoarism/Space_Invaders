#include "OpenGL/renderer.h"

void Renderer::Render
	(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
		va.Bind();
		ib.Bind();
        shader.Use();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	}

void Renderer::RenderConfig
	(const float& r, const float& g,
	 const float& b, const float& a) {

	glClearColor(r, g, b, a);
    if (Render3D)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else 
        glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::FrameTimeTracker() {
	const float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

Shader Renderer::LoadShader
    (std::string name, const char* vertexPath, const char* fragmentPath) {
    
    shaders[name] = LoadShaderFromFile(vertexPath, fragmentPath);
    return shaders[name];
}

Texture& Renderer::LoadTexture
    (const char* file, const bool alpha, const std::string name) {

    textures[name] = Texture();
    TextureLayout tl;
    if (alpha)
        tl.SetFormat(GL_RGBA);
    else
        tl.SetFormat(GL_RGB);

    tl.SetType(GL_TEXTURE_2D);
    tl.AddPar(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    tl.AddPar(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    tl.AddPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    tl.AddPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    textures[name].SetLayout(tl);
    textures[name].Load(file);
    return textures[name];
}


void Renderer::Clear() {
    // (properly) delete all shaders
    for (auto s : shaders)
        glDeleteProgram(s.second.ID);
}

Shader Renderer::LoadShaderFromFile
    (const char* vertexPath, const char* fragmentPath) {

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

    Shader shader;
    shader.Compile(vertexCode.c_str(), fragmentCode.c_str());
    return shader;
}

bool Renderer::Render3D = false;
float Renderer::lastFrame = 0.0f;
float Renderer::deltaTime = 0.0f;
std::map<std::string, Shader> Renderer::shaders;
std::map<std::string, Texture> Renderer::textures;
