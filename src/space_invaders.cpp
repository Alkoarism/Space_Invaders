#include "space_invaders.h"

using std::string;

SpaceInvaders::SpaceInvaders(const char* vertexPath, const char* fragmentPath)
	: m_Font(vertexPath, fragmentPath) {
	m_Model = glm::mat4(1.0f);
	m_GameState = MAIN_MENU;
	//open file with hi-score
	//if fail to open, create a file to hold hi-score
	//for now the scores will be initialized as 0000
	m_HiScore = 0;
	m_P1Score = m_P2Score = 0;

	//debug variables initialization
	m_Scale = 0.01f;
	m_X = m_Y = m_OffSet = 0.0f;
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
	auto ZeroFilling = [](string s) -> string {
		if (s.size() < 4) {
			string temp((4 - s.size()), '0');
			s = temp + s;
		}
		return s;
	};

	Print(0.011, WHITE, "Score<1>", -1.28, 1.55);
	Print(0.011, WHITE, "Hi-Score", -0.33, 1.55);
	Print(0.011, WHITE, "Score<2>", 0.62, 1.55);
	Print(0.011, WHITE, ZeroFilling(ToString(m_P1Score)) , -1.18, 1.35);
	Print(0.011, WHITE, ZeroFilling(ToString(m_HiScore)), -0.20, 1.35);
	Print(0.011, WHITE, ZeroFilling(ToString(m_P2Score)), 0.75, 1.35);
}

void SpaceInvaders::MainMenu() {
	TopScores();
}

void SpaceInvaders::ScoreTable() {

}

void SpaceInvaders::Game() {

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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Scale += 0.001 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		if (m_Scale > 0)
			m_Scale -= 0.001 * Renderer::GetDeltaTime();
		else
			m_Scale = 0;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		if (m_OffSet > 0)
			m_OffSet -= 1 * Renderer::GetDeltaTime();
		else
			m_OffSet = 0;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_OffSet += 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		m_Y += 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		m_Y -= 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		m_X -= 1 * Renderer::GetDeltaTime();
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
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

}


