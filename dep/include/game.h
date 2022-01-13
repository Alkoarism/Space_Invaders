#ifndef GAME_H
#define GAME_H

#include "OpenGL\renderer.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "bullet.h"
#include "bitmap_font.h"

enum GameState {
	GAME_MENU,
	GAME_SCORE_TABLE,
	GAME_ACTIVE,
	GAME_END
};

const float TOP_HUD_SIZE = 100.0f;
const float BOTTOM_HUD_SIZE = 50.0f;

const glm::vec2 BULLET_SIZE(5.0f, 5.0f);
const glm::vec2 BULLET_VELOCITY(100.0f, 100.0f);
const float PLAYER_VELOCITY(400.0f);

class Game {
public:
	GameState state;
	bool keys[1024];
	bool keysProcessed[1024];
	bool sprite;
	unsigned int width, height;
	unsigned int level;
	std::vector<GameLevel> levels;

	Game(unsigned int, unsigned int);
	~Game();

	void ProcessInput(float);
	void Update(float);
	void Render();

private:
	unsigned int m_PlayerShots, m_AlienShots;
	std::unique_ptr<BitmapFont> m_Font;
	std::unique_ptr<SpriteRenderer> m_SpRenderer;
	std::unique_ptr<Entity> m_Player;
	std::vector<Bullet> m_Bullets;

	void DoCollisions();
	bool CheckCollision(Entity& one, Entity& two);
};

#endif