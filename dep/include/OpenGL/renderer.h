#ifndef RENDERER_H
#define RENDERER_H

#include "headers.h"
#include "OpenGL\vertex_array.h"
#include "OpenGL\index_buffer.h"
#include "OpenGL\shader.h"
#include "OpenGL\texture.h"

class Renderer {
public:
	static void Render
	(const VertexArray&, const IndexBuffer&, const Shader&);

	static void RenderConfig
	(const float& r = 0.0f, const float& g = 0.0f,
		const float& b = 0.0f, const float& a = 0.0f);
	static void FrameTimeTracker();

	static Shader LoadShader
	(std::string name, const char* vertexPath, const char* fragmentPath);
	static Texture& LoadTexture
	(const char* file,const bool alpha,const std::string name);

	static void Clear();

	static float GetLastFrame() { return lastFrame; }
	static float GetDeltaTime() { return deltaTime; }
	static Shader GetShader(const std::string name) { return shaders[name]; }
	static Texture& GetTexture(const std::string name) { return textures[name]; }

	static bool Render3D;
private:
	Renderer() { };

	static Shader LoadShaderFromFile
	(const char* vertexPath, const char* fragmentPath);

	static float lastFrame;
	static float deltaTime;
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;
};

#endif