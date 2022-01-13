#include "game_level.h"

GameLevel::GameLevel() {
}

bool GameLevel::Load(const char* file, unsigned int screenWidth, unsigned int screenHeight) {
	this->aliens.clear();
	unsigned int alienCode;
	std::string line;
	std::vector<std::vector<unsigned int>> alienData;
	std::ifstream fstream;

	fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fstream.open(file, std::ios::in);

		while (!fstream.eof() && std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> alienCode)
				row.push_back(alienCode);
			alienData.push_back(row);
		}
		if (alienData.size() > 0)
			init(alienData, screenWidth, screenHeight);

		fstream.close();
	}
	catch (std::ifstream::failure e){
		std::cout << "ERROR::GAME_LEVEL_LOADING::FAILED_TO_LOAD_LEVEL_DATA" << std::endl;
		return false;
	}

	return true;
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (Entity& alien : this->aliens)
		if (!alien.destroyed)
			alien.Draw(renderer);
}

bool GameLevel::IsCompleted() {
	for (Entity& alien : this->aliens)
		if (!alien.destroyed)
			return false;
	return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> alienData, 
	unsigned int screenWidth, unsigned int screenHeight) {

	float playAreaHeight = screenHeight - (this->borderOffset.top + this->borderOffset.down);

	this->unitWidth = static_cast<float>(screenWidth) / MAX_ALIEN_COLS;
	this->unitHeight = playAreaHeight / MAX_ALIEN_ROWS;

	float alienTileOffset = 1.0f - ALIEN_TILE_PROPORTION;

	// initialize level aliens based on alienData
	for (unsigned int y = 0; y != alienData.size(); ++y) {
		if (y == MAX_ALIEN_ROWS) break;

		for (unsigned int x = 0; x != alienData[y].size(); ++x) {
			if (x == MAX_ALIEN_COLS) break;

			glm::vec2 alienRelativeOffset(
				MAX_ALIEN_COLS >= alienData[y].size() ? 
					(MAX_ALIEN_COLS - alienData[y].size()) / 2 : 0,
				2.5 // UFO Offset
				);

			//check alien type from level data (2D level array)
			if (alienData[y][x] > 0) {
				glm::vec3 color = glm::vec3(1.0f);
				AlienShape type;

				switch (alienData[y][x]) {
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
			}
		}
	}
}
