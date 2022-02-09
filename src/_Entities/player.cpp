#include "player.h"

Player::Player() : Player(glm::vec2(0.0f), glm::vec2(1.0f), 3) {

}

Player::Player(glm::vec2 pos, glm::vec2 size, int lives) 
	: Entity(pos, size, glm::vec3(0.0f, 1.0f, 0.0f)), 
	lives(lives), score(0) 
{
	sprite = "player";
}

void Player::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(this->sprite,
		this->position, this->size, this->rotation, this->color);
}
