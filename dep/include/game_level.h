#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "OpenGL\renderer.h"

#include "alien.h"
#include "ufo.h"

// maximum number of aliens per row / column
const unsigned int MAX_ALIEN_ROWS(20);
const unsigned int MAX_ALIEN_COLS(22);

// alien size based on a single play area tile
const float ALIEN_TILE_PROPORTION(0.8f);

const float UFO_OFFSET(2.0f);

struct BorderOffset {
	float top = 0;
	float down = 0;
};

class GameLevel {
public:
	unsigned int initialAlienCnt;
	unsigned int activeAliens;
	float unitWidth;
	float unitHeight;

	UFO ufo;
	std::forward_list<Alien> aliens;
	std::vector<std::vector<unsigned int>> alienData;
	BorderOffset borderOffset;

	GameLevel();
	bool Load(const char*, unsigned int, unsigned int);
	bool IsCompleted();
	void Draw(SpriteRenderer&);
	void Restart(unsigned int, unsigned int);

	void SetUFO(unsigned int);

private:
	void InitPosition(unsigned int, unsigned int);
};

#endif