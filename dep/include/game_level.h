#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "OpenGL\renderer.h"

#include "entity.h"
#include "alien.h"

// maximum number of aliens per row / column
const unsigned int MAX_ALIEN_ROWS = 20;
const unsigned int MAX_ALIEN_COLS = 22;

// alien size based on a single play area tile
const float ALIEN_TILE_PROPORTION = 0.9;

struct BorderOffset {
	float top = 0;
	float down = 0;
};

class GameLevel {
public:
	float unitWidth;
	float unitHeight;

	std::vector<Alien> aliens;
	BorderOffset borderOffset;

	GameLevel();
	bool Load(const char*, unsigned int, unsigned int);
	void Draw(SpriteRenderer&);
	bool IsCompleted();

private:
	void InitPosition(std::vector<std::vector<unsigned int>>, unsigned int, unsigned int);
};

#endif