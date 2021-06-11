#ifndef SCREEN_H
#define SCREEN_H

enum Scene {
	MAIN_MENU,
	SCORE_TABLE,
	GAME
};

class Screen {
public:
	Screen();
	~Screen();

	void Render();

private:
	int hi_score;
	int player_score;
	Scene screen_state;
};

#endif