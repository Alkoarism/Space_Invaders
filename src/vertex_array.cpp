#include <glad/glad.h>

#include "vertex_array.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
}

VertexArray::~VertexArray() {
	Release();
}

VertexArray::VertexArray(VertexArray&& other) noexcept
	: m_vertexArrayID(other.m_vertexArrayID) {
	other.m_vertexArrayID = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
	if (this != &other) {
		Release();
		std::swap(m_vertexArrayID, other.m_vertexArrayID);
	}
	return *this;
}

void VertexArray::AddBuffer(const VertexBuffer& vb) {
	Bind();
	vb.Bind();

	//in this project, all the objects will have this configuration of pointers
	//AttribPointer(attribute, components, type, ???, total size of components, offset)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void VertexArray::Bind() const {
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

