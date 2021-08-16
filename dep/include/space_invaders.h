#ifndef SPACE_INVADERS_H
#define SPACE_INVADERS_H

#include "OpenGL\renderer.h"
#include "bitmap_font.h"

enum State {
	MAIN_MENU,
	SCORE_TABLE,
	GAME
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
	SpaceInvaders(const char*, const char*);
	~SpaceInvaders();

	void LoadFont(const char*);
	void Run(GLFWwindow*);

private:
	int m_HiScore, m_P1Score, m_P2Score;
	int m_PlayerLifes;
	int m_Credits;
	bool m_P2Join;
	glm::mat4 m_Model;

	State m_GameState;
	BitmapFont m_Font;

	void TopScores();
	void MainMenu();
	void ScoreTable();
	void Game();
	template<typename T> std::string ToString(const T&, const std::size_t size = 0);
	void Print(const float&, const Color&, const std::string&, const float&, const float&);
	void ProcessInput(GLFWwindow*);


	//debug stuff
	float m_Scale, m_X, m_Y, m_OffSet;

	void NotYetImplemented();
	void Debug();
};

template<typename T>
std::string SpaceInvaders::ToString(const T& value, std::size_t size) {
	std::ostringstream temp;
	temp << value;
	std::string s(temp.str());
	if ((s.size() > size) && (size != 0))
		s.erase(5, s.back());
	return s;
}

#endif