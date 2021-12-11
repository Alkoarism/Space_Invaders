#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include "OpenGL\renderer.h"
#include "bitmap_font.h"
#include "sprite_renderer.h"

//Read about state pattern to remove all these enum from the code and
//reduce the coupling relating the SpaceInvaders, State and Color classes.
enum GameState {
	GAME_MENU,
	GAME_SCORE_TABLE,
	GAME_ACTIVE,
};

class SpaceInvaders {
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;

	//initialize game state (load all shaders/textures/levels)
	SpaceInvaders(unsigned int, unsigned int);
	~SpaceInvaders();

	//game loop
	void ProcessInput(float);
	void Update(float);
	void Render();

private:
	std::unique_ptr<SpriteRenderer> sprite;

	void NotYetImplemented();
	void Debug();
};

#endif