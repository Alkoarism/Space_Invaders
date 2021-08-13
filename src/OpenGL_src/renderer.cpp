#include "OpenGL/renderer.h"

void Renderer::Render
	(const VertexArray& va, const IndexBuffer& ib, const Shader& s) {
		va.Bind();
		ib.Bind();
		s.SetUniform("projection", projection);
		s.SetUniform("view", view);
		s.SetUniform("model", model);

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
	}

void Renderer::RenderConfig
	(const float& r, const float& g,
	 const float& b, const float& a) {

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4 Renderer::projection = glm::mat4(1.0f);
glm::mat4 Renderer::view = glm::mat4(1.0f);
glm::mat4 Renderer::model = glm::mat4(1.0f);
