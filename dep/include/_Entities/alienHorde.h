#ifndef ALIEN_HORDE_H
#define ALIEN_HORDE_H

#include "entityDynamic.h"
#include "alien.h"

class AlienHorde : public EntityDynamic {
public:
	unsigned int activeAliens;
	unsigned int initialAlienCnt;
	std::forward_list<Alien> aliens;

	glm::vec2 unitGridSize;
	glm::vec2 minVelocity;
	glm::vec2 curVelocity;
	glm::vec2 maxVelocity;

	AlienHorde(	
		glm::vec2 pos, glm::vec2 unitGridSize,
		glm::vec2 minVel, glm::vec2 maxVel,
		std::vector<std::vector<unsigned int>>& alienData, 
		float alienToGridProp, bool moveRight);

	void Update();
	void Reset(glm::vec2 pos, bool moveRight);
	void Draw(SpriteRenderer& renderer) override;
	glm::vec2 Move(float dt, float window_width) override;

private:
	bool m_HorizontalMove;
	bool m_MoveRight;

	unsigned int m_LastCount;

	float m_GridToAlProp;
	float m_Descent;
	float m_MoveTracker;

	glm::vec2 m_ResizeOffset;

	std::vector<std::vector<unsigned int>> m_AlienData;

	void Load();
};

#endif