#include "alien.h"

size_t Alien::subSpriteNbr = 0;

Alien::Alien(AlienShape shape) : 
	Alien(glm::vec2(0.0f), glm::vec2(1.0f),	shape) {
}

Alien::Alien(glm::vec2 pos, glm::vec2 size, AlienShape shape)
	:	Entity(pos, size, glm::vec3(1.0f)), 
		shape(shape)
{
	switch (this->shape) {
		case SQUARE: {
			this->sprites = { "al_sq_0", "al_sq_1", "al_sq_2" };
			this->color = glm::vec3(0.2, 1.0, 0.2);
			break;
		}
		case CIRCLE: {
			this->sprites = { "al_cl_0", "al_cl_1", "al_cl_2" };
			this->color = glm::vec3(0.2, 0.2, 1.0);
			break;
		}
		case TRIANGLE: {
			this->sprites = { "al_tr_0", "al_tr_1", "al_tr_2" };
			this->color = glm::vec3(1.0, 0.2, 1.0);
			break;
		}
	}
}

void Alien::Draw(SpriteRenderer& renderer) {
	renderer.DrawSprite(this->sprites[subSpriteNbr],
		this->position, this->size, this->rotation, this->color);
}