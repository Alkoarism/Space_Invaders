#include "renderer.h"

void Renderer::Render(const VertexArray& va, const IndexBuffer& ib, const Shader& s) {
	va.Bind();
	ib.Bind();
	s.Use();

}