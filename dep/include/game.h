#ifndef GAME_H
#define GAME_H

#include "OpenGL\renderer.h"
#include "bitmap_font.h"
#include "sprite_renderer.h"

enum GameState {
	GAME_MENU,
	GAME_SCORE_TABLE,
	GAME_ACTIVE
};

class Game {
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;

	Game(unsigned int, unsigned int);
	~Game();

	void ProcessInput(float);
	void Update(float);
	void Render();

private:
	std::string m_SpriteTextName;
	std::unique_ptr<SpriteRenderer> m_Sprite;

};

#endif