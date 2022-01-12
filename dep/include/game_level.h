#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "OpenGL\renderer.h"

#include "entity.h"
#include "alien.h"

struct BorderOffset {
	float top = 0;
	float down = 0;
	float left = 0;
	float right = 0;
};

class GameLevel {
public:
	//level state
	std::vector<Alien> aliens;
	BorderOffset borderOffset;

	GameLevel();
	bool Load(const char*, unsigned int, unsigned int);
	void Draw(SpriteRenderer&);
	bool IsCompleted();

private:
	void init(std::vector<std::vector<unsigned int>>, unsigned int, unsigned int);
};

#endif