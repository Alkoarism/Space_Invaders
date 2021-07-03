#include <glad/glad.h>

#include "vertex_array.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
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

void VertexArray::Bind() const {
	glBindVertexArray(m_vertexArrayID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

