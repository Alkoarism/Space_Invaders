#include "bullet.h"

Bullet::Bullet() : Entity(),
	m_TimeCtr(0.0f), offScreen(false), shooter(PLAYER), spriteName2("") {
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string& sprite, Shooter shooter)
	: Entity(pos, size, sprite, glm::vec3(1.0f), velocity),
	m_TimeCtr(), offScreen(false), shooter(shooter) {

	this->spriteName2 = this->spriteName;
	this->spriteName2[this->spriteName2.length() - 1] = 'b';
	if (this->shooter == PLAYER)
		this->velocity.y = -this->velocity.y;
}

glm::vec2 Bullet::Move(float dt, unsigned int window_height) {
	m_TimeCtr += dt;
	if (m_TimeCtr >= 0.25) {
		std::swap(this->spriteName, this->spriteName2);
		m_TimeCtr = 0;
	}
	this->position.y += this->velocity.y * dt;
	
	if (this->position.y <= -this->size.y || this->position.y >= window_height) {
		offScreen = true;
	}
	
	return this->position;
}