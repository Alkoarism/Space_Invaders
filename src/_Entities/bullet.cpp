#include "bullet.h"

Bullet::Bullet() 
	: EntityDynamic(), type(LASER), hitScreenBorder(false), velocity(glm::vec2(1.0f)) {
}

Bullet::Bullet(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, std::string sprite, BulletType type)
	: EntityDynamic(pos, size, glm::vec3(1.0f)),
	type(type), hitScreenBorder(false), velocity(velocity), sprite(sprite) {

}

glm::vec2 Bullet::Move(float dt, const float height_limit) {
	this->position.y += this->velocity.y * dt;

	if (this->type == LASER && this->position.y <= height_limit)
		this->hitScreenBorder = true;
	
	if (this->type != LASER && this->position.y >= height_limit - this->size.y)
		this->hitScreenBorder = true;

	return this->position;
}

void Bullet::Draw(SpriteRenderer& renderer) {
	// Add sprite changing logic

	renderer.DrawSprite(this->sprite, 
		this->position, this->size, this->rotation, this->color);
}