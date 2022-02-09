#ifndef GAME_H
#define GAME_H

#include "OpenGL\renderer.h"
#include "sprite_renderer.h"
#include "game_level.h"
#include "bullet.h"
#include "player.h"
#include "bitmap_font.h"

enum GameState {
	GAME_MENU,
	GAME_SCORE_TABLE,
	GAME_ACTIVE,
	GAME_END
};

const float TOP_HUD_SIZE(100.0f);
const float BOTTOM_HUD_SIZE(50.0f);

const glm::vec2 BULLET_SIZE(5.0f, 15.0f);
const float BULLET_VELOCITY(500.0f);
const float PLAYER_VELOCITY(400.0f);

const float ALIEN_VELOCITY_MAX(100.0f);
const float ALIEN_VELOCITY_MIN(20.0f);

class Game {
public:
	static std::default_random_engine engine;
	static std::uniform_int_distribution<int> randomDist;

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
	unsigned int m_PlayerShots, m_AlienShots, m_ShotsUntilUFO;
	int m_GameResult;
	glm::vec2 m_PlayerStartPos;
	std::unique_ptr<BitmapFont> m_Font;
	std::unique_ptr<SpriteRenderer> m_SpRenderer;
	std::unique_ptr<Player> m_Player;
	std::forward_list<Bullet> m_Bullets;

	void DoCollisions();
	bool CheckCollision(Entity& one, Entity& two);
	void GenerateBullet(Entity& shooter, BulletType type);
};

#endif