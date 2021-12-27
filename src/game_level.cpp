#include "game_level.h"

GameLevel::GameLevel() : borderOffset(glm::vec2(0.0f)) {
}

bool GameLevel::Load(const char* file, unsigned int lvlWidth, unsigned int lvlHeight) {
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
			init(alienData, lvlWidth, lvlHeight);

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
	unsigned int lvlWidth, unsigned int lvlHeight) {

	//calculate dimensions
	unsigned int height = alienData.size();
	unsigned int width	= alienData[0].size();
	float unit_width	= (lvlWidth - (2 * this->borderOffset.x)) / static_cast<float>(width);
	float unit_height	= (lvlHeight - (2 * this->borderOffset.y)) / static_cast<float>(height);

	// initialize level aliens based on alienData
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			//check alien type from level data (2D level array)
			if (alienData[y][x] > 0) {
				glm::vec3 color = glm::vec3(1.0f);
				std::string type = "";

				switch (alienData[y][x]) {
					case 1: {
						color = glm::vec3(0.0f, 0.0f, 1.0f);
						type = "al_cl_0";
						break;
					} case 2: {
						color = glm::vec3(0.0f, 1.0f, 0.0f);
						type = "al_sq_0";
						break;
					} case 3: {
						color = glm::vec3(1.0f, 0.1f, 1.0f);
						type = "al_tr_0";
						break;
					} default: {
						color = glm::vec3(1.0f, 0.0f, 0.0f);
						type = "al_UFO_0";
						break;
					}
				}

				glm::vec2 pos(
					(unit_width * x) + this->borderOffset.x, 
					(unit_height * y) + this->borderOffset.y);
				glm::vec2 size(unit_width, unit_height);
				this->aliens.push_back(Entity(pos, size, type, color));
			}
		}
	}
}
