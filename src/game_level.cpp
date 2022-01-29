#include "game_level.h"

GameLevel::GameLevel() {
}

bool GameLevel::Load(const char* file, unsigned int screenWidth, unsigned int screenHeight) {
	// alien initialization ------------------------------------------------------
	unsigned int alienCode;
	std::string line;
	std::ifstream fstream;

	fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fstream.open(file, std::ios::in);

		while (!fstream.eof() && std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> alienCode) {
				if (row.size() == MAX_ALIEN_COLS) break;
				row.push_back(alienCode);
			}
			if (this->alienData.size() == MAX_ALIEN_ROWS - 3) break;
			this->alienData.push_back(row);
		}

		if (this->alienData.size() > 0) {
			// Ensure that every row have the same size
			unsigned int largerRow = 0;
			for (size_t i = 0; i != this->alienData.size(); ++i) {
				if (this->alienData[i].size() > largerRow)
					largerRow = this->alienData[i].size();
			}
			for (auto& row : this->alienData) {
				while (row.size() != largerRow) {
					row.push_back(0);
				}
			}

			this->Restart(screenWidth, screenHeight);
		}

		fstream.close();
	}
	catch (std::ifstream::failure e){
		std::cout << "ERROR::GAME_LEVEL_LOADING::FAILED_TO_LOAD_LEVEL_DATA" << std::endl;
		return false;
	}

	// barrier initialization -------------------------------------------------
	glm::vec2 barSize = glm::vec2(
		this->unitWidth * 2,
		this->unitHeight * 2);

	float xOffSet = 
		(screenWidth - (barSize.x * MAX_BARRIER_COUNT)) / (MAX_BARRIER_COUNT + 1);
	float yPos = screenHeight - this->borderOffset.down - barSize.y - 
		(this->unitHeight * BARRIER_OFFSET);

	for (unsigned int i = 0; i != MAX_BARRIER_COUNT; ++i) {
		glm::vec2 barPos = glm::vec2(
			i * (barSize.x + xOffSet) + xOffSet,
			yPos);
		this->barriers.emplace_back(Barrier(barPos, barSize));
	}

	// UFO initialization --------------------------------------------------------
	this->ufo.destroyed = true;
	return true;
}

bool GameLevel::IsCompleted() {
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

	if (this->aliens.begin() != this->aliens.end())
			return false;
	this->ufo.destroyed = true;
	return true;
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (Entity& alien : this->aliens)
		if (!alien.destroyed)
			alien.Draw(renderer);

	for (Entity& barrier : this->barriers)
		if (!barrier.destroyed)
			barrier.Draw(renderer);
	
	if (!this->ufo.destroyed)
		this->ufo.Draw(renderer);
}

void GameLevel::Restart(unsigned int screenWidth, unsigned int screenHeight) {
	this->aliens.clear();
	InitPosition(screenWidth, screenHeight);
	
	for (Barrier& barrier : this->barriers)
		barrier.Reset();
}

void GameLevel::SetUFO(unsigned int screenWidth) {
	glm::vec2 size = ALIEN_TILE_PROPORTION * glm::vec2(
		2 * this->unitWidth,
		this->unitHeight);

	glm::vec2 pos = glm::vec2(screenWidth ,
		 this->borderOffset.top +
		(this->unitHeight * (UFO_OFFSET / 2)) - 
		(size.x / 2));

	this->ufo = UFO(pos, size, glm::vec2(100.0f));
}

void GameLevel::InitPosition(unsigned int screenWidth, unsigned int screenHeight) {
	float playAreaHeight = screenHeight - (this->borderOffset.top + this->borderOffset.down);

	this->initialAlienCnt = 0;
	this->unitWidth = static_cast<float>(screenWidth) / MAX_ALIEN_COLS;
	this->unitHeight = playAreaHeight / MAX_ALIEN_ROWS;

	Alien::SetHorDir(true);
	Alien::unitGridSize = glm::vec2(this->unitWidth, this->unitHeight);

	float alienTileOffset = 1.0f - ALIEN_TILE_PROPORTION;

	for (unsigned int y = 0; y != this->alienData.size(); ++y) {
		for (unsigned int x = 0; x != this->alienData[y].size(); ++x){
			glm::vec2 alienRelativeOffset(
				MAX_ALIEN_COLS >= this->alienData[y].size() ?
				(MAX_ALIEN_COLS - this->alienData[y].size()) / 2 : 0,
				UFO_OFFSET
			);

			if (this->alienData[y][x] > 0) {
				glm::vec3 color = glm::vec3(1.0f);
				AlienShape type;

				switch (this->alienData[y][x]) {
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
					(this->unitWidth * (alienRelativeOffset.x + x + alienTileOffset)),
					(this->unitHeight * (alienRelativeOffset.y + y + alienTileOffset)) + this->borderOffset.top);
				glm::vec2 size(
					this->unitWidth * ALIEN_TILE_PROPORTION,
					this->unitHeight * ALIEN_TILE_PROPORTION);
				Alien a(pos, size, type);
				a.gridPos = glm::vec2(x, y);
				this->aliens.push_front(a);
				++this->initialAlienCnt;
			}
		}
	}

	this->activeAliens = this->initialAlienCnt;
}
