#include "space_invaders.h"

SpaceInvaders::SpaceInvaders(const char* vertexPath, const char* fragmentPath)
	: m_Font(vertexPath, fragmentPath) {
	m_Model = glm::mat4(1.0f);
	m_GameState = MAIN_MENU;
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
}

void SpaceInvaders::LoadFont(const char* bffPath) {
	m_Font.Load(bffPath);
}

void SpaceInvaders::MainMenu() {

	m_Model = glm::mat4(1.0f);
	m_Model = glm::scale(m_Model, glm::vec3(0.009, 0.009, 0.0));
	Renderer::SetModel(m_Model);

	m_Font.SetColor(1.0f, 1.0f, 1.0f);

	m_Font.Print("Text Prototype", -100, 0);
	m_Font.Print("Finally some progress!", -160, -40);
}

void SpaceInvaders::ScoreTable() {

}

void SpaceInvaders::Game() {

}

void SpaceInvaders::NotYetImplemented() {

}

void SpaceInvaders::ProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}
