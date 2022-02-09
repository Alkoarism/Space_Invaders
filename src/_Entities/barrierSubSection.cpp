#include "barrierSubSection.h"

BarrierSubSection::BarrierSubSection(std::string sprite,
	glm::vec2 pos, glm::vec2 size)
	: Entity(pos, size, glm::vec3(0.0f, 1.0f, 0.0f)), sprite(sprite)
{

}

void BarrierSubSection::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(sprite, 
		this->position, this->size, this->rotation, this->color);
}
