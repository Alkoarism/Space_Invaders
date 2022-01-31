#ifndef BARRIERSECTION_H
#define BARRIERSECTION_H

#include "entity.h"

enum SectionType {
	BORDER,
	CORNER,
	EDGE,
	INNER
};

class BarrierSection : public Entity {
public:
	std::string sprite;
	SectionType location;
	std::pair<Entity, Entity> subSections;

	BarrierSection(std::string sprite, glm::vec2 pos, glm::vec2 size, SectionType location);

	void Update();
	void Reset();
	void Draw(SpriteRenderer& renderer) override;
private:
	glm::vec2 m_SpritePosition;
	glm::vec2 m_SpriteSize;

};

#endif