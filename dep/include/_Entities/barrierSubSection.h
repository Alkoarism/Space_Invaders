#ifndef BARRIERSUBSECTION_H
#define BARRIERSUBSECTION_H

#include "entity.h"

class BarrierSubSection : public Entity {
public:
	std::string sprite;

	BarrierSubSection(std::string sprite, glm::vec2 pos, glm::vec2 size);

	void Draw(SpriteRenderer& renderer) override;
private:

};

#endif