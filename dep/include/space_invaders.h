#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include "OpenGL\renderer.h"
#include "bitmap_font.h"

//Read about state pattern to remove all these enum from the code and
//reduce the coupling relating the SpaceInvaders, State and Color classes.
enum State {
	MAIN_MENU,
	SCORE_TABLE,
	GAME,
	ENDGAME
};

enum Color {
	WHITE,
	RED,
	BLUE,
	GREEN,
	YELLOW,
};

class SpaceInvaders {
public:
	SpaceInvaders();
	~SpaceInvaders();

	void LoadFont(const char*);
	void Run(GLFWwindow*);

private:
	int m_Credits;
	int m_AliensAlive;
	int m_AliensDirection;
	int m_ScreenXLimit;
	int m_HiScore, m_P1Score, m_P2Score;
	int m_PlayerLifes;
	int m_P1Move, m_P2Move;
	bool m_P1Shoot, m_P2Shoot;
	bool m_P2Join;
	bool m_Victory;
	glm::mat4 m_Model;

	State m_GameState;
	BitmapFont m_Font;

	//std::vector<Entity> m_Entitys;

	void TopScores();
	void MainMenu();
	void ScoreTable();
	void Game();
	void EndGame();

	void Print(const float&, const Color&, const std::string&, const float&, const float&);
	void ProcessInput(GLFWwindow*);


	//debug stuff
	float m_Scale, m_X, m_Y, m_OffSet;

	void NotYetImplemented();
	void Debug();
};

#endif