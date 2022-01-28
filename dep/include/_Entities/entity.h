#ifndef ENTITY_H
#define ENTITY_H

#include "OpenGL\renderer.h"

#include "sprite_renderer.h"

class Entity {
public:
	glm::vec2 position, size;
	glm::vec3 color;
	float rotation;
	bool destroyed;

	Entity();
	Entity(
		glm::vec2 pos, glm::vec2 size, glm::vec3 color = glm::vec3(1.0f));
	virtual ~Entity() = default;

	virtual void Draw(SpriteRenderer&);
};

#endif