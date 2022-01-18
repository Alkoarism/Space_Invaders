#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

enum BulletType {
	LASER,
	SLOW,
	FAST,
	WIGGLY
};

class Bullet : public Entity {
public:
	bool hitScreenBorder;
	BulletType type;

	Bullet();
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, 
		std::string sprite, BulletType type);

	glm::vec2 Move(float dt, const float heigh_limit);
	void Draw(SpriteRenderer& renderer) override;
	//void Reset(glm::vec2 position, glm::vec2 velocity); //Not really needed in this game

private:
};

#endif