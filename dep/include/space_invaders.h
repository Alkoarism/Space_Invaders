#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include "OpenGL\renderer.h"
#include "bitmap_font.h"

enum State {
	MAIN_MENU,
	SCORE_TABLE,
	GAME
};

class SpaceInvaders {
public:
	SpaceInvaders(const char*, const char*);

	void LoadFont(const char*);
	void Run(GLFWwindow*);
private:
	int m_HiScore, m_P1Score, m_P2Score;
	int m_PlayerLifes;
	int m_Credits;
	glm::mat4 m_Model;

	State m_GameState;
	BitmapFont m_Font;

	void MainMenu();
	void ScoreTable();
	void Game();
	void NotYetImplemented();
	void ProcessInput(GLFWwindow*);
};

#endif