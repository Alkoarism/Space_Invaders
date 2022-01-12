#include "alien.h"

Alien::Alien(AlienShape shape) : 
	Alien(glm::vec2(0.0f), glm::vec2(1.0f),	glm::vec2(0.0f), shape) {
}

Alien::Alien(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, AlienShape shape)
	:	Entity(pos, size, "", glm::vec3(1.0f), velocity), 
		shape(shape), m_SubSpriteNbr(0), m_TimeTracker(0), m_AddSpriteNbr(true)
{
	m_SubSprites = { '0', '1', '2' };

	switch (this->shape) {
		case SQUARE: {
			this->spriteName = "al_sq_0";
			this->color = glm::vec3(0.2, 1.0, 0.2);
			break;
		}
		case CIRCLE: {
			this->spriteName = "al_cl_0";
			this->color = glm::vec3(0.2, 0.2, 1.0);
			break;
		}
		case TRIANGLE: {
			this->spriteName = "al_tr_0";
			this->color = glm::vec3(1.0, 0.2, 1.0);
			break;
		}
	}
}

glm::vec2 Alien::Move(float dt, unsigned int window_width) {
	this->position.x += this->velocity.x * dt;

	if (this->position.x <= 0 || this->position.x >= window_width - this->size.x) {
		this->velocity.x = -(this->velocity.x);

		this->position.y += this->velocity.y * dt;
	}

	return this->position;
}

void Alien::Draw(SpriteRenderer& renderer) {
	m_TimeTracker += Renderer::GetDeltaTime();
	if (m_TimeTracker >= 1) {
		if (m_SubSpriteNbr + 1 == m_SubSprites.size())
			m_AddSpriteNbr = false;
		else if (m_SubSpriteNbr == 0)
			m_AddSpriteNbr = true;

		if (m_AddSpriteNbr)
			++m_SubSpriteNbr;
		else
			--m_SubSpriteNbr;

		m_TimeTracker = 0;
		this->spriteName.pop_back();
		this->spriteName += m_SubSprites[m_SubSpriteNbr];
	}

	Entity::Draw(renderer);
}