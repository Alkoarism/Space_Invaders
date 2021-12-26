#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

enum Shooter {
	PLAYER,
	ALIEN
};

class Bullet : public Entity {
public:

	bool offScreen;

	Bullet();
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, 
		std::string& sprite, Shooter shooter);

	glm::vec2 Move(float dt, unsigned int window_height);
	//void Reset(glm::vec2 position, glm::vec2 velocity); //Not really needed in this game

private:
	float m_TimeCtr;
	Shooter m_Shooter;
};

#endif