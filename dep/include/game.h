#ifndef GAME_H
#define GAME_H

#include "OpenGL\renderer.h"
#include "sprite_renderer.h"
#include "game_level.h"

enum GameState {
	GAME_MENU,
	GAME_SCORE_TABLE,
	GAME_ACTIVE
};

const glm::vec2 PLAYER_SIZE(130.0f, 80.0f);
const float PLAYER_VELOCITY(500.0f);

class Game {
public:
	GameState state;
	bool keys[1024];
	unsigned int width, height;
	std::vector<GameLevel> levels;
	unsigned int level;

	Game(unsigned int, unsigned int);
	~Game();

	void ProcessInput(float);
	void Update(float);
	void Render();

private:
	std::vector<std::string> m_TextureNames;
	std::unique_ptr<SpriteRenderer> m_SpRenderer;
	std::unique_ptr<Entity> m_Player;
};

#endif