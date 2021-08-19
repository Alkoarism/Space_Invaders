#ifndef ENTITY_H
#define ENTITY_H

#include "OpenGL/renderer.h"
#include "OpenGL/texture.h"

class Entity {
public:
	Entity(const char* v_Path, const char* f_Path)
		: m_Shader(v_Path, f_Path) { }
	virtual ~Entity() = default;

	virtual void LoadTexture(const char*) = 0;
	virtual void Render(const float&, const float&) = 0;
	virtual float GetLength() const = 0;
	virtual float GetHeight() const = 0;

protected:
	VertexArray m_VAO;

private:
	Shader m_Shader;
	

};

#endif