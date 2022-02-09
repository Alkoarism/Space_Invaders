#include "alienHorde.h"

AlienHorde::AlienHorde(glm::vec2 pos, glm::vec2 unitGridSize,
	glm::vec2 minVel, glm::vec2 maxVel,
	std::vector<std::vector<unsigned int>>& alienData, 
	float gridToAlienProportion, bool moveRight)
	
	: EntityDynamic(pos, glm::vec2(1.0f)),
	minVelocity(minVel), maxVelocity(maxVel), curVelocity(minVel), unitGridSize(unitGridSize),
	m_GridToAlProp(gridToAlienProportion), m_AlienData(alienData), 
	m_MoveRight(moveRight), m_Descent(0), m_LastCount(0), m_HorizontalMove(true) {

	Load();
}

void AlienHorde::Update() {
	unsigned int removed = 0;
	auto condition = [&removed](const Alien& value) -> bool
	{
		if (value.destroyed) {
			++removed;
			return true;
		}
		else
			return false;
	};
	this->aliens.remove_if(condition);
	this->activeAliens -= removed;

	if (this->activeAliens != m_LastCount) {
		float activeAlienRatio =
			static_cast<float>(this->activeAliens) /
			static_cast<float>(this->initialAlienCnt);
		this->curVelocity = glm::vec2(
			((1 - activeAlienRatio) * (1 - activeAlienRatio) *
				(this->maxVelocity - this->minVelocity)) +
			this->minVelocity);
		
		bool firstAlien = true;
		glm::vec2 outerBorder(0.0f), position(0.0f);
		for (auto& alien : this->aliens) {
			if (firstAlien) {
				position = alien.position;
				m_ResizeOffset = alien.hordePos;
				firstAlien = false;
			}

			if (alien.hordePos.x < m_ResizeOffset.x) {
				m_ResizeOffset.x = alien.hordePos.x;
			}
			if (alien.hordePos.y < m_ResizeOffset.y) {
				m_ResizeOffset.y = alien.hordePos.y;
			}
			if (alien.position.x < position.x) {
				position.x = alien.position.x;
			}
			if (alien.position.y < position.y) {
				position.y = alien.position.y;
			}
			if (alien.position.x + alien.size.x > outerBorder.x) {
				outerBorder.x = alien.position.x + alien.size.x;
			}
			if (alien.position.y + alien.size.y > outerBorder.y) {
				outerBorder.y = alien.position.y + alien.size.y;
			}
		}

		float alienTileOffset = 1.0f - m_GridToAlProp;
		this->position = position - (this->unitGridSize * alienTileOffset);
		this->size = outerBorder - this->position;

		if (this->activeAliens == 0)
			this->destroyed = true;

		m_LastCount = this->activeAliens;
	}
}

void AlienHorde::Reset(glm::vec2 pos, bool horDir) {
	this->aliens.clear();
	this->activeAliens = 0;
	this->position = pos;
	this->curVelocity = this->minVelocity;
	this->destroyed = false;
	m_HorizontalMove = true;
	m_MoveRight = horDir;

	Load();
}

void AlienHorde::Draw(SpriteRenderer& renderer) {
	for (auto& alien : this->aliens) {
		if (!alien.destroyed)
			alien.Draw(renderer);
	}
}

glm::vec2 AlienHorde::Move(float dt, float window_width) {
	glm::vec2 movement = this->curVelocity * dt;
	
	if (m_HorizontalMove) {
		
		float leftBorderOffset = this->unitGridSize.x * (1 - m_GridToAlProp);
		float nextHorPos = this->position.x + movement.x * (m_MoveRight ? 1 : -1);
		float rightBorderOffset= window_width - this->size.x;
		if (nextHorPos < -leftBorderOffset || nextHorPos > rightBorderOffset) {
			m_HorizontalMove = false;
			m_MoveRight = !m_MoveRight;
		}
		else {
			this->position.x = nextHorPos;
			m_MoveTracker += movement.x;
		}
	}
	else {
		float nextVertPos = this->position.y + movement.y;
		m_Descent += movement.y;
		if (m_Descent < this->unitGridSize.y){
			this->position.y = nextVertPos;
			m_MoveTracker += movement.y;
		}
		else {
			m_HorizontalMove = true;
			m_Descent = 0;
		}
	}

	float alienTileOffset = 1.0f - m_GridToAlProp;
	for (auto& alien : this->aliens) {
		glm::vec2 alienRelativeOffset(
			alien.hordePos.x + alienTileOffset - m_ResizeOffset.x,
			alien.hordePos.y + alienTileOffset - m_ResizeOffset.y);

		alien.position = glm::vec2(
			this->position.x + this->unitGridSize.x * alienRelativeOffset.x,
			this->position.y + this->unitGridSize.y * alienRelativeOffset.y);
	}

	return this->position;
}

void AlienHorde::Load() {
	float unitWidth = this->unitGridSize.x;
	float unitHeight = this->unitGridSize.y;
	float alienTileOffset = 1.0f - m_GridToAlProp;

	for (unsigned int y = 0; y != m_AlienData.size(); ++y) {
		for (unsigned int x = 0; x != m_AlienData[y].size(); ++x) {
			glm::vec2 alienRelativeOffset(
				x + alienTileOffset,
				y + alienTileOffset);

			if (m_AlienData[y][x] > 0) {
				glm::vec3 color = glm::vec3(1.0f);
				AlienShape type;

				switch (m_AlienData[y][x]) {
					case 1: {
						type = CIRCLE;
						break;
					} case 2: {
						type = SQUARE;
						break;
					} case 3: {
						type = TRIANGLE;
						break;
					}
				}

				glm::vec2 pos(
					this->position.x + unitWidth * alienRelativeOffset.x,
					this->position.y + unitHeight * alienRelativeOffset.y);
				glm::vec2 size(
					unitWidth * m_GridToAlProp,
					unitHeight * m_GridToAlProp);
				Alien a(pos, size, type);
				a.hordePos = glm::vec2(x, y);

				this->aliens.push_front(a);
				++this->activeAliens;

				glm::vec2 outerBorder((pos + size) - this->position);
				if (outerBorder.x > this->size.x) {
					this->size.x = outerBorder.x;
				}
				if (outerBorder.y > this->size.y) {
					this->size.y = outerBorder.y;
				}
			}
		}
	}

	this->initialAlienCnt = this->activeAliens;
	m_LastCount = this->activeAliens;
	m_ResizeOffset = glm::vec2(0.0f);
}