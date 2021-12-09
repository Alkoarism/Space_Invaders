#ifndef RENDERER_H
#define RENDERER_H

#include "headers.h"
#include "OpenGL\vertex_array.h"
#include "OpenGL\index_buffer.h"
#include "OpenGL\shader.h"

class Renderer {
public:
	static void Render
	(const VertexArray&, const IndexBuffer&, const std::string);

	static void RenderConfig
	(const float& r = 0.0f, const float& g = 0.0f,
		const float& b = 0.0f, const float& a = 0.0f);
	static void FrameTimeTracker();

	static Shader LoadShader
	(std::string name, const char* vertexPath, const char* fragmentPath);

	static void Clear();

	static void SetProjection(const glm::mat4& p) { projection = p; }
	static void SetView(const glm::mat4& v) { view = v; }
	static void SetModel(const glm::mat4& m) { model = m; }

	static float GetLastFrame() { return lastFrame; }
	static float GetDeltaTime() { return deltaTime; }
	static Shader GetShader(const std::string name) { return shaders[name]; }

	static bool depthBuffer;
private:
	Renderer() { };

	static Shader LoadShaderFromFile
	(const char* vertexPath, const char* fragmentPath);

	static float lastFrame;
	static float deltaTime;
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::mat4 model;
	static std::map<std::string, Shader> shaders;
};

#endif