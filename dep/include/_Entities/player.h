#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
public:
	int score;
	int lives;
	std::string sprite;

	Player();
	Player(glm::vec2 pos, glm::vec2 size, int lives);
	void Draw(SpriteRenderer& renderer) override;

private:
};

#endif