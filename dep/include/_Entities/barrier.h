#ifndef BARRIER_H
#define BARRIER_H

#include "entity.h"
#include "barrierSubSection.h"

const unsigned int VERTICAL_SUB_SECTIONS(6);
const unsigned int HORIZONTAL_SUB_SECTIONS(12);

class Barrier : public Entity {
public:
	std::vector<std::vector<BarrierSubSection>> barrierContent;

	Barrier();
	Barrier(glm::vec2 pos, glm::vec2 size);

	void Reset();
	void Draw(SpriteRenderer& renderer) override;
private:
	std::vector<std::vector<bool>> m_SectionState;

	void UpdateTextures(size_t row, size_t col);
};

#endif