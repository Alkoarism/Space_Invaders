#ifndef RENDERER_H
#define RENDERER_H

#include "headers.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Renderer {
public:
	static void Render
		(const VertexArray & va, const IndexBuffer & ib, const Shader & s) {
		va.Bind();
		ib.Bind();
		s.Use();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	}

	static void RenderConfig
		(const float& r = 0.0f, const float& g = 0.0f, 
		 const float& b = 0.0f, const float& a = 0.0f) {

		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	static std::pair<std::string, glm::mat4> view;
	static std::pair<std::string, glm::mat4> projection;
	static std::pair<std::string, glm::mat4> model;

private:

};

#endif