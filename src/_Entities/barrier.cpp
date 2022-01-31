#include "barrier.h"

Barrier::Barrier() : Barrier(glm::vec2(0.0f), glm::vec2(1.0f)) {
}

Barrier::Barrier(glm::vec2 pos, glm::vec2 size) : Entity(pos, size) {
	glm::vec2 subSectionSize = glm::vec2(
		this->size.x / HORIZONTAL_SUB_SECTIONS,
		this->size.y / VERTICAL_SUB_SECTIONS);

	for (size_t y = 0; y != VERTICAL_SUB_SECTIONS; ++y) {
		std::vector<BarrierSection> temp;
		for (size_t x = 0; x != HORIZONTAL_SUB_SECTIONS; ++x) {
			glm::vec2 subPos = glm::vec2(
				this->position.x + (x * subSectionSize.x),
				this->position.y + (y * subSectionSize.y));
			BarrierSection bss("barrier", subPos, subSectionSize, INNER);
			temp.push_back(bss);
		}

		this->barrierContent.push_back(temp);
	}
}

void Barrier::Update() {
	for (auto& row : this->barrierContent) {
		for (auto& section : row) {
			if (!section.destroyed)
				section.Update();
		}
	}
}

void Barrier::Reset() {
	for (auto& row : this->barrierContent) {
		for (auto& section : row) {
			section.Reset();
		}
	}
	this->destroyed = false;
}

void Barrier::Draw(SpriteRenderer& renderer) {
	for (auto& row : this->barrierContent) {
		for (auto& section : row) {
			if (!section.destroyed)
				section.Draw(renderer);
		}
	}
}
