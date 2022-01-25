#ifndef ALIEN_H
#define ALIEN_H

#include "entityDynamic.h"

enum AlienShape {
	TRIANGLE,
	CIRCLE,
	SQUARE,
};

class Alien final : public EntityDynamic {
public:
	static glm::vec2 velocity;
	static glm::vec2 unitGridSize;

	const AlienShape shape;
	glm::vec2 gridPos;

	Alien(AlienShape shape);
	Alien(glm::vec2 pos, glm::vec2 size, AlienShape shape);

	glm::vec2 Move(float dt, float window_width) override;
	void Draw(SpriteRenderer&) override;

	static void SetHorDir(bool moveRight);
private:
	static bool m_MoveRight;
	static bool m_HorizontalMove;

	bool m_ProcessedMoveChange;
	bool m_AddSpriteNbr;
	float m_PositionTracker;
	float m_Descent;
	glm::vec2 m_Movement;
	glm::vec2 m_LastPos;

	size_t m_SubSpriteNbr;
	std::vector<char> m_SubSprites;
};

#endif