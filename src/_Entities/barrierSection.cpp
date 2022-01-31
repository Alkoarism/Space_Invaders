#include "..\..\dep\include\_Entities\barrierSection.h"

BarrierSection::BarrierSection(std::string sprite, 
	glm::vec2 pos, glm::vec2 size, SectionType location) 
	:	Entity(pos, size, glm::vec3(0.0f, 1.0f, 0.0f)), 
		location(location), sprite(sprite),
		m_SpriteSize(size), m_SpritePosition(pos)
{
	glm::vec2 subPosition, subSize;

	switch (location) {
		default: {
			subPosition = glm::vec2(
				this->position.x,
				this->position.y);

			subSize = glm::vec2(
				this->size.x / 2,
				this->size.y);

			this->subSections.first = Entity(subPosition, subSize);
			this->subSections.second = Entity(glm::vec2(
				subPosition.x + subSize.x, subPosition.y), subSize);
		}
	}
}

void BarrierSection::Update() {
	if (this->subSections.first.destroyed && this->subSections.second.destroyed)
		this->destroyed = true;
	if (this->subSections.first.destroyed || this->subSections.second.destroyed) {
		m_SpriteSize.x /= 2;

		if (this->subSections.first.destroyed)
			m_SpritePosition = this->subSections.second.position;
		else
			m_SpritePosition = this->subSections.first.position;
	}
}

void BarrierSection::Reset() {
	m_SpritePosition = this->position;
	m_SpriteSize = this->size;
	this->subSections.first.destroyed = false;
	this->subSections.second.destroyed = false;
	this->destroyed = false;
}

void BarrierSection::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(this->sprite,
		m_SpriteSize, m_SpritePosition, this->rotation, this->color);
}
