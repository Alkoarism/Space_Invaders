#include "barrier.h"

Barrier::Barrier() : Barrier(glm::vec2(0.0f), glm::vec2(1.0f)) {
}

Barrier::Barrier(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {
	glm::vec2 subSectionSize = glm::vec2(
		this->size.x / HORIZONTAL_SUB_SECTIONS,
		this->size.y / VERTICAL_SUB_SECTIONS);

	for (size_t y = 0; y != VERTICAL_SUB_SECTIONS; ++y) {
		std::vector<BarrierSubSection> temp;
		std::vector<bool> state;
		for (size_t x = 0; x != HORIZONTAL_SUB_SECTIONS; ++x) {
			glm::vec2 subPos = glm::vec2(
				this->position.x + (x * subSectionSize.x),
				this->position.y + (y * subSectionSize.y));
			BarrierSubSection bss("barrier", subPos, subSectionSize);
			temp.push_back(bss);
			state.emplace_back(bss.destroyed);
		}

		this->barrierContent.push_back(temp);
		m_SectionState.push_back(state);
	}
}

void Barrier::Reset() {
	for (auto& row : this->barrierContent) {
		for (auto& section : row) {
			section.destroyed = false;
		}
	}
}

void Barrier::Draw(SpriteRenderer& renderer) {
	for (size_t j = 0; j != this->barrierContent.size(); ++j) {
		for (size_t k = 0; k != this->barrierContent.size(); ++k) {
			if (this->barrierContent[j][k].destroyed != m_SectionState[j][k])
				UpdateTextures(j, k);
		}
	}

	for (auto& row : this->barrierContent) {
		for (auto& section : row) {
			if (!section.destroyed)
				section.Draw(renderer);
		}
	}
}

void Barrier::UpdateTextures(size_t row, size_t col) {
	m_SectionState[row][col] = this->barrierContent[row][col].destroyed;
}