#include "game_level.h"

GameLevel::GameLevel() {
}

bool GameLevel::Load(const char* file, unsigned int screenWidth, unsigned int screenHeight) {
	// alien initialization ------------------------------------------------------
	unsigned int alienCode;
	std::string line;
	std::ifstream fstream;
	std::vector<std::vector<unsigned int>> alienData;

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
			if (alienData.size() == MAX_ALIEN_ROWS - 3) break;
			alienData.push_back(row);
		}

		if (alienData.size() > 0) {
			// Ensure that every row have the same size
			unsigned int largerRow = 0;
			for (size_t i = 0; i != alienData.size(); ++i) {
				if (alienData[i].size() > largerRow)
					largerRow = alienData[i].size();
			}
			for (auto& row : alienData) {
				while (row.size() != largerRow) {
					row.push_back(0);
				}
			}
		}

		fstream.close();
	}
	catch (std::ifstream::failure e){
		std::cout << "ERROR::GAME_LEVEL_LOADING::FAILED_TO_LOAD_LEVEL_DATA" << std::endl;
		return false;
	}

	float playAreaHeight = screenHeight - (this->borderOffset.top + this->borderOffset.down);

	this->unitWidth = static_cast<float>(screenWidth) / MAX_ALIEN_COLS;
	this->unitHeight = playAreaHeight / MAX_ALIEN_ROWS;
	glm::vec2 unitGrid = glm::vec2(this->unitWidth, this->unitHeight);

	glm::vec2 relativePos = glm::vec2(
		MAX_ALIEN_COLS >= alienData[0].size() ?
			(MAX_ALIEN_COLS - alienData[0].size()) / 2 : 0,
		UFO_OFFSET);

	m_HordeInitPos = relativePos * unitGrid;
	m_HordeInitPos.y += this->borderOffset.top;

	this->horde.reset(new AlienHorde(
		m_HordeInitPos, unitGrid,
		glm::vec2(30.0f), glm::vec2(100.0f),
		alienData, 
		ALIEN_TILE_PROPORTION, true));

	// barrier initialization -------------------------------------------------
	//glm::vec2 barSize = glm::vec2(
	//	this->unitWidth * 2,
	//	this->unitHeight * 2);

	//float xOffSet = 
	//	(screenWidth - (barSize.x * MAX_BARRIER_COUNT)) / (MAX_BARRIER_COUNT + 1);
	//float yPos = screenHeight - this->borderOffset.down - barSize.y - 
	//	(this->unitHeight * BARRIER_OFFSET);

	//for (unsigned int i = 0; i != MAX_BARRIER_COUNT; ++i) {
	//	glm::vec2 barPos = glm::vec2(
	//		i * (barSize.x + xOffSet) + xOffSet,
	//		yPos);
	//	this->barriers.emplace_back(Barrier(barPos, barSize));
	//}

	// UFO initialization --------------------------------------------------------
	this->ufo.destroyed = true;
	return true;
}

bool GameLevel::IsCompleted() {

	if (this->horde->destroyed) {
		return true;
		this->ufo.destroyed = true;
	}
	return false;
}

void GameLevel::Update() {
	this->horde->Update();

	//for (Barrier& barrier : this->barriers)
	//	if (!barrier.destroyed)
	//		barrier.Update();
}

void GameLevel::Draw(SpriteRenderer& renderer) {
	if (!this->horde->destroyed)
		this->horde->Draw(renderer);

	//for (Entity& barrier : this->barriers)
	//	if (!barrier.destroyed)
	//		barrier.Draw(renderer);
	
	if (!this->ufo.destroyed)
		this->ufo.Draw(renderer);
}

void GameLevel::Restart(unsigned int screenWidth, unsigned int screenHeight) {
	this->horde->Reset(m_HordeInitPos, true);
	
	//for (Barrier& barrier : this->barriers)
	//	barrier.Reset();
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