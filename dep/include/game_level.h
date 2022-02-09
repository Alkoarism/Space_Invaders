#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "OpenGL\renderer.h"

#include "alienHorde.h"
#include "ufo.h"
//#include "barrier.h"

const unsigned int MAX_ALIEN_ROWS(20);
const unsigned int MAX_ALIEN_COLS(22);
const unsigned int MAX_BARRIER_COUNT(4);

const float ALIEN_TILE_PROPORTION(0.8f);
const float BARRIER_TILE_PROPORTION(2.0f);

// from top borderOffset
const float UFO_OFFSET(2.0f);

// from bottom borderOffset
const float BARRIER_OFFSET(2.0f);

struct BorderOffset {
	float top = 0;
	float down = 0;
};

class GameLevel {
public:
	float screenWidth;
	float screenHeight;

	float unitWidth;
	float unitHeight;

	UFO ufo;
	std::unique_ptr<AlienHorde> horde;
	//std::vector<Barrier> barriers;
	
	BorderOffset borderOffset;

	GameLevel(float screenWidth, float screenHeight);
	bool Load(const char*);
	int IsCompleted();
	void Update();
	void Draw(SpriteRenderer&);
	void Restart();

	void SetUFO();

private:
	glm::vec2 m_HordeInitPos;
};

#endif