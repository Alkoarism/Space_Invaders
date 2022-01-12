#include "bullet.h"

Bullet::Bullet() : Entity(),
	offScreen(false), shooter(PLAYER) {
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string sprite, Shooter shooter)
	: Entity(pos, size, sprite, glm::vec3(1.0f), velocity),
	offScreen(false), shooter(shooter) {

	if (this->shooter == PLAYER)
		this->velocity.y = -this->velocity.y;
}

glm::vec2 Bullet::Move(float dt, unsigned int window_height) {
	this->position.y += this->velocity.y * dt;
	
	if (this->position.y <= -this->size.y || this->position.y >= window_height) {
		offScreen = true;
	}
	
	return this->position;
}