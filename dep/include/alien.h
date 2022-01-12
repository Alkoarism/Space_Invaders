#ifndef ALIEN_H
#define ALIEN_H

#include "entity.h"

enum AlienShape {
	TRIANGLE,
	CIRCLE,
	SQUARE,
};

class Alien final: public Entity {
public:
	const AlienShape shape;

	Alien(AlienShape shape);
	Alien(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, AlienShape shape);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Draw(SpriteRenderer&) override;

private:
	bool m_AddSpriteNbr;
	float m_TimeTracker;

	//implement this later...
	size_t m_SubSpriteNbr;
	std::vector<char> m_SubSprites;
};

#endif