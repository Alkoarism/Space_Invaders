#ifndef BARRIER_H
#define BARRIER_H

#include "entity.h"
#include "barrierSection.h"

const unsigned int VERTICAL_SUB_SECTIONS(6);
const unsigned int HORIZONTAL_SUB_SECTIONS(6);

class Barrier : public Entity {
public:
	std::vector<std::vector<BarrierSection>> barrierContent;

	Barrier();
	Barrier(glm::vec2 pos, glm::vec2 size);

	void Update();
	void Reset();
	void Draw(SpriteRenderer& renderer) override;
private:
};

#endif