#include "..\dep\include\game_level.h"

bool GameLevel::Load(const char* file, unsigned int lvlWidth, unsigned int lvlHeight) {
	this->aliens.clear();
	unsigned int alienCode;
	std::string line;
	std::vector<std::vector<unsigned int>> alienData;
	std::ifstream fstream;

	fstream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		fstream.open(file);

		while (std::getline(fstream, line)) {
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
		std::cout << "ERROR::GAME_LEVEL_LOADING::LEVEL_DATA_NOT_FOUND" << std::endl;
		return false;
	}

	return true;
}

void GameLevel::Draw(SpriteRenderer& renderer) {

}

bool GameLevel::IsCompleted()
{
	return false;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> alienData, 
	unsigned int lvlWidth, unsigned int lvlHeight) {

	//calculate dimensions
	unsigned int height = alienData.size();
	unsigned int width	= alienData[0].size();
	float unit_width	= lvlWidth / static_cast<float>(width);
	float unit_height	= lvlHeight / static_cast<float>(height);

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
						type = "al_cr_0";
					} case 2: {
						color = glm::vec3(0.0f, 1.0f, 0.0f);
						type = "al_sq_0";
					} case 3: {
						color = glm::vec3(1.0f, 0.0f, 0.0f);
						type = "al_tr_0";
					} default: {
						color = glm::vec3(1.0f, 0.0f, 0.0f);
						type = "al_UFO_0";
					}
				}

				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				this->aliens.push_back(Entity(pos, size, type, color));
			}
		}
	}
}
