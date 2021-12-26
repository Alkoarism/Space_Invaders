#include "bullet.h"

Bullet::Bullet() : Entity(), m_TimeCtr(0.0f), offScreen(false), m_Shooter(PLAYER) {
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string& sprite, Shooter shooter)
	: Entity(pos, size, sprite, glm::vec3(1.0f), velocity),
	m_TimeCtr(), offScreen(false), m_Shooter(shooter) {

	if (m_Shooter == PLAYER)
		this->velocity.y = -this->velocity.y;
}

glm::vec2 Bullet::Move(float dt, unsigned int window_height) {
	m_TimeCtr += dt;
	this->position.y += this->velocity.y * dt;
	
	if (this->position.y <= -this->size.y || this->position.y >= window_height) {
		offScreen = true;
	}
	
	return this->position;
}