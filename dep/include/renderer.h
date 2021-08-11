#ifndef RENDERER_H
#define RENDERER_H

#include "headers.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

class Shader;
class VertexArray;
class IndexBuffer;

class Renderer {
public:
	static void Render(const VertexArray&, const IndexBuffer&, const Shader&);

	static std::pair<std::string, glm::mat4> view;
	static std::pair<std::string, glm::mat4> projection;
	static std::pair<std::string, glm::mat4> model;

private:

};

#endif