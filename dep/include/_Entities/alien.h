#ifndef ALIEN_H
#define ALIEN_H

#include "entityDynamic.h"

enum AlienShape {
	TRIANGLE,
	CIRCLE,
	SQUARE,
};

class Alien final : public Entity {
public:
	static size_t subSpriteNbr;

	const AlienShape shape;
	glm::vec2 hordePos;

	std::vector<std::string> sprites;

	Alien(AlienShape shape);
	Alien(glm::vec2 pos, glm::vec2 size, AlienShape shape);

	void Draw(SpriteRenderer&) override;
private:
};

#endif