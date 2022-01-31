#ifndef BULLET_H
#define BULLET_H

#include "entityDynamic.h"

enum BulletType {
	LASER,
	SLOW,
	FAST,
	WIGGLY
};

class Bullet : public EntityDynamic {
public:
	bool hitScreenBorder;
	std::string sprite;
	glm::vec2 velocity;
	BulletType type;

	Bullet();
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, 
		std::string sprite, BulletType type);

	bool Pierce();
	glm::vec2 Move(float dt, float heigh_limit) override;
	void Draw(SpriteRenderer& renderer) override;
	//void Reset(glm::vec2 position, glm::vec2 velocity); //Not really needed in this game

private:
	static std::default_random_engine m_Engine;
	static std::uniform_int_distribution<int> m_RandomDist;

};

#endif