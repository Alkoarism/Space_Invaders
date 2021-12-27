#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "OpenGL\renderer.h"

#include "entity.h"

class GameLevel {
public:
	//level state
	std::vector<Entity> aliens;
	glm::vec2 borderOffset;

	GameLevel();
	bool Load(const char*, unsigned int, unsigned int);
	void Draw(SpriteRenderer&);
	bool IsCompleted();

private:
	void init(std::vector<std::vector<unsigned int>>, unsigned int, unsigned int);
};

#endif