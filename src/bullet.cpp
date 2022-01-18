#include "bullet.h"

Bullet::Bullet() : Entity(), type(LASER), hitScreenBorder(false) {
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string sprite, BulletType type)
	: Entity(pos, size, sprite, glm::vec3(1.0f), velocity),
	type(type), hitScreenBorder(false) {

}

glm::vec2 Bullet::Move(float dt, const float height_limit) {
	this->position.y += this->velocity.y * dt;

	if (this->type == LASER && this->position.y <= height_limit)
		this->hitScreenBorder = true;
	
	if (this->type != LASER && this->position.y >= height_limit + this->size.y)
		this->hitScreenBorder = true;

	return this->position;
}

void Bullet::Draw(SpriteRenderer& renderer) {
	// Add sprite changing logic

	Entity::Draw(renderer);
}