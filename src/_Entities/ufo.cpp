#include "ufo.h"

UFO::UFO() : UFO(glm::vec2(0.0f), glm::vec2(1.0f), glm::vec2(0.0f)) {
}

UFO::UFO(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity) 
	: EntityDynamic(pos, size, "al_UFO_0", glm::vec3(1.0f, 0.0f, 0.0f)), 
	velocity(velocity), m_SubSpriteNbr(0), m_AddSpriteNbr(true), m_TimeTracker(0) {

	m_SubSprites = { '0', '1', '2' };
}

glm::vec2 UFO::Move(float dt, float window_width) {
	m_TimeTracker += dt;
	this->position.x -= this->velocity.x * dt;

	return this->position;
}

void UFO::Draw(SpriteRenderer& renderer) {
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
