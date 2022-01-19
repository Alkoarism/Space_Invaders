#include "game_level.h"

GameLevel::GameLevel() {
}

bool GameLevel::Load(const char* file, unsigned int screenWidth, unsigned int screenHeight) {
	this->aliens.clear();
	unsigned int alienCode;
	std::string line;
	std::ifstream fstream;

	fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fstream.open(file, std::ios::in);

		while (!fstream.eof() && std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> alienCode)
				row.push_back(alienCode);
			this->alienData.push_back(row);
		}

		if (this->alienData.size() > 0) {
			// Ensure that every row have the same size
			unsigned int largerRow = 0;
			for (size_t i = 0; i != this->alienData.size(); ++i) {
				if (this->alienData[i].size() > 0)
					largerRow = this->alienData[i].size();
			}
			for (auto& row : this->alienData) {
				while (row.size() != largerRow) {
					row.push_back(0);
				}
			}

			InitPosition(screenWidth, screenHeight);
		}

		fstream.close();
	}
	catch (std::ifstream::failure e){
		std::cout << "ERROR::GAME_LEVEL_LOADING::FAILED_TO_LOAD_LEVEL_DATA" << std::endl;
		return false;
	}

	return true;
}

bool GameLevel::IsCompleted() {
	for (Entity& alien : this->aliens)
		if (!alien.destroyed)
			return false;
	return true;
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (Entity& alien : this->aliens)
		if (!alien.destroyed)
			alien.Draw(renderer);
}

void GameLevel::Restart(unsigned int screenWidth, unsigned int screenHeight) {
	this->aliens.clear();
	InitPosition(screenWidth, screenHeight);
}

void GameLevel::InitPosition(unsigned int screenWidth, unsigned int screenHeight) {

	float playAreaHeight = screenHeight - (this->borderOffset.top + this->borderOffset.down);

	this->unitWidth = static_cast<float>(screenWidth) / MAX_ALIEN_COLS;
	this->unitHeight = playAreaHeight / MAX_ALIEN_ROWS;

	float alienTileOffset = 1.0f - ALIEN_TILE_PROPORTION;

	// initialize level aliens based on alienData
	for (unsigned int y = 0; y != this->alienData.size(); ++y) {
		if (y == MAX_ALIEN_ROWS) break;

		for (unsigned int x = 0; x != this->alienData[y].size(); ++x) {
			if (x == MAX_ALIEN_COLS) break;

			glm::vec2 alienRelativeOffset(
				MAX_ALIEN_COLS >= this->alienData[y].size() ? 
					(MAX_ALIEN_COLS - this->alienData[y].size()) / 2 : 0,
				2.5 // UFO Offset
				);

			//check alien type from level data (2D level array)
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
				this->aliens.push_back(Alien(pos, size, glm::vec2(30.0f), type));
				this->aliens[this->aliens.size() - 1].gridPos = glm::vec2(x, y);
			}
		}
	}
}
