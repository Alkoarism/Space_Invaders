#ifndef UFO_H
#define UFO_H

#include "entityDynamic.h"
class UFO : public EntityDynamic {
public:
	glm::vec2 velocity;
	std::vector<std::string> sprites;

	UFO();
	UFO(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);

	glm::vec2 Move(float, float) override;
	void Draw(SpriteRenderer& renderer) override;

private:
	float m_TimeTracker;

	bool m_AddSpriteNbr;
	size_t m_SubSpriteNbr;
};

#endif