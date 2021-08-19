#include "space_invaders.h"

using std::string;

SpaceInvaders::SpaceInvaders(const char* vertexPath, const char* fragmentPath)
	: m_Font(vertexPath, fragmentPath) {
	m_Model = glm::mat4(1.0f);
	m_GameState = MAIN_MENU;
	m_P1Score = m_P2Score = 0;
	m_P2Join = false;
	m_ScreenXLimit = 1.2f;

	std::ifstream ReadFile;
	ReadFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		ReadFile.open("res\\score.dat");
		ReadFile >> m_HiScore;
		ReadFile.close();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SAVE_FILE_NOT_FOUND" << std::endl;
		ReadFile.clear();
		m_HiScore = 0;
	}

	//debug variables initialization
	m_Scale = 0.01f;
	m_X = m_Y = m_OffSet = 0.0f;
}

SpaceInvaders::~SpaceInvaders() {
	std::ofstream WriteToFile;
	WriteToFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		WriteToFile.open("res\\score.dat");
		WriteToFile << m_HiScore;
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::RESOURCES_FOLDER_NOT_FOUND" << std::endl;
	}
}

void SpaceInvaders::Run(GLFWwindow* window) {
	ProcessInput(window);

	switch (m_GameState) {
	case MAIN_MENU:
		MainMenu();
		break;
	case SCORE_TABLE:
		ScoreTable();
		break;
	case GAME:
		Game();
		break;
	default:
		NotYetImplemented();
	}

	Debug();
}

void SpaceInvaders::LoadFont(const char* bffPath) {
	m_Font.Load(bffPath);
}

void SpaceInvaders::TopScores() {
	auto ZeroFilling = [](string& s, int& zeros) -> string {
		if (s.size() < zeros) {
			string temp((zeros - s.size()), '0');
			s = temp + s;
		}
		return s;
	};
	int zero_Number = 4;

	Print(0.011, WHITE, "Score<1>", -1.28, 1.55);
	Print(0.011, WHITE, "Hi-Score", -0.33, 1.55);
	Print(0.011, WHITE, "Score<2>", 0.62, 1.55);
	Print(0.011, WHITE, ZeroFilling(std::to_string(m_P1Score), zero_Number) , -1.18, 1.35);
	Print(0.011, WHITE, ZeroFilling(std::to_string(m_HiScore), zero_Number), -0.20, 1.35);
	Print(0.011, WHITE, ZeroFilling(std::to_string(m_P2Score), zero_Number), 0.75, 1.35);
}

void SpaceInvaders::MainMenu() {
	TopScores();
	
	Print(0.011, WHITE, "<1 or 2 players?>", -0.62, 0.3);
	Print(0.011, m_P2Join ? WHITE : GREEN , "1 player", -0.30, -0.2);
	Print(0.011, m_P2Join ? GREEN : WHITE , "2 players", -0.35, -0.7);
}

void SpaceInvaders::ScoreTable() {

}

void SpaceInvaders::Game() {
	//size_t playersDefeated = 0;
	//int deadAliens = 0;
	//int players = 0;

	//for (auto& e : m_Entitys) {
	//	if (e.IsDestroyed() == 0) {
	//		if (e.GetType() == PLAYER) {
	//			playersDefeated++;
	//		}
	//		else if (e.GetTYpe() == ALIEN) {
	//			deadAliens++;
	//		}
	//		continue;
	//	}

	//	switch (e.GetType()) {
	//		case PLAYER:
	//		{
	//			if (players == 0) {
	//				e.Move(m_P1Move);
	//				if (m_P1Shoot)
	//					e.Shoot();
	//				m_P1Score = e.GetScore();
	//			}
	//			else {
	//				e.Move(m_P2Move);
	//				if (m_P2Shoot)
	//					e.Shoot();
	//				m_P2Score = e.GetScore();
	//			}
	//			players++;
	//		}
	//		case ALIEN:
	//		{
	//			if (e.GetX().first() == -m_ScreenXLimit)
	//				m_AliensDirection = 1;
	//			if (e.GetX().second() == m_ScreenXLimit)
	//				m_AliensDirection = -1;

	//			e.Move(m_AliensDirection);
	//			e.Shoot();
	//		}
	//		case UFO:
	//		{
	//			e.Move();
	//		}
	//	}

	//	e.Render();
	//	e.DetectColision();
	//}

	//if (players == playersDefeated) {
	//	m_GameState = ENDGAME;
	//	m_Victory = false;
	//} else if (m_AliensAlive == 0) {
	//	m_GameState = ENDGAME;
	//	m_Victory = true;
	//}
}

void SpaceInvaders::EndGame() {

}

void SpaceInvaders::Print (const float& scale, const Color& color,
	const string& txt, const float& x, const float& y) {

	m_Model = glm::mat4(1.0f);
	m_Model = glm::scale(m_Model, glm::vec3(scale, scale, 0.0));
	Renderer::SetModel(m_Model);

	switch (color) {
	case WHITE:
		m_Font.SetColor(1.0f, 1.0f, 1.0f);
		break;
	case RED:
		m_Font.SetColor(1.0f, 0.0f, 0.0f);
		break;
	case BLUE:
		m_Font.SetColor(0.0f, 0.0f, 1.0f);
		break;
	case GREEN:
		m_Font.SetColor(0.0f, 1.0f, 0.0f);
		break;
	case YELLOW:
		m_Font.SetColor(1.0f, 1.0f, 0.0f);
		break;
	}

	m_Font.Print(txt.c_str(), 100 * x, 100 * y);
}

void SpaceInvaders::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	switch (m_GameState) {
		case MAIN_MENU:
		{
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				m_P2Join = true;
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				m_P2Join = false;
			break;
		}
		case SCORE_TABLE:

			break;
		case GAME:

			break;
		default:
			NotYetImplemented();
	}

	//Debug keys - Can be deleted later
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Scale += 0.001 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		if (m_Scale > 0)
			m_Scale -= 0.001 * Renderer::GetDeltaTime();
		else
			m_Scale = 0;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_OffSet -= 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_OffSet += 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		m_Y += 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		m_Y -= 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		m_X -= 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		m_X += 1 * Renderer::GetDeltaTime();


}

//delete this later
string SimpleDebug(const float&);
void SpaceInvaders::Debug() {
	
	Print(0.01, YELLOW, "Scale:" + SimpleDebug(m_Scale), -1.4, -2.0f);
	Print(0.01, YELLOW, "X:" + SimpleDebug(m_X), -0.2, -2.0f);
	Print(0.01, YELLOW, "Y:" + SimpleDebug(m_Y), -0.2, -1.8f);
	Print(0.01, YELLOW, "OffSet:" + SimpleDebug(m_OffSet), 0.6, -2.0f);
}

string SimpleDebug(const float& value) {
	std::ostringstream temp;
	temp << value;
	string s(temp.str());
	if (s.size() > 5)
		s.erase(5, s.back());
	return s;
}

void SpaceInvaders::NotYetImplemented() {
	assert(false);
}


