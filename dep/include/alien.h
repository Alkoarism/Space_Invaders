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
	static glm::vec2 unitGridSize;

	const AlienShape shape;
	glm::vec2 gridPos;

	Alien(AlienShape shape);
	Alien(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, AlienShape shape);

	glm::vec2 Move(float dt, unsigned int window_width);
	void Draw(SpriteRenderer&) override;

private:
	static bool m_TurnAround;
	static bool m_GoDown;
	static float m_BorderOffset;

	bool m_BorderOffsetProcessed;
	bool m_AddSpriteNbr;
	float m_TimeTracker;
	float m_Descent;
	float m_LastBorderTrespassValue;

	//implement this later...
	size_t m_SubSpriteNbr;
	std::vector<char> m_SubSprites;
};

#endif