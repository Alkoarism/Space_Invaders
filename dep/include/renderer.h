#ifndef RENDERER_H
#define RENDERER_H

#include "headers.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer {
public:
	static void Render
	(const VertexArray&, const IndexBuffer&, const Shader&);
	static void RenderConfig
	(const float& r = 0.0f, const float& g = 0.0f,
		const float& b = 0.0f, const float& a = 0.0f);
	
	static void SetProjection(const glm::mat4& p) { projection = p; }
	static void SetView(const glm::mat4& v) { view = v; }
	static void SetModel(const glm::mat4& m) { model = m; }

private:
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::mat4 model;
};

#endif