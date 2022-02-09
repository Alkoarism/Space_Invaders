#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
	int score;
	int lives;
	std::string sprite;

	Player(const glm::vec2 pos, const glm::vec2 size, const int lives);
	void Draw(SpriteRenderer& renderer) override;

private:
};

#endif