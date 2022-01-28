#include "entity.h"

Entity::Entity() 
	:	position(0.0f, 0.0f), size(1.0f, 1.0f), rotation(0.0f),
		color(1.0f), destroyed(false) { }

Entity::Entity(glm::vec2 Pos, glm::vec2 Size, glm::vec3 Color)
	:	position(Pos), size(Size), rotation(0.0f), color(Color),
		destroyed(false) { }

void Entity::Draw(SpriteRenderer& Renderer) {
	Renderer.DrawSprite(this->position, this->size, this->rotation, this->color);
}
