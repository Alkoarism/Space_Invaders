#include "game.h"

Game::Game(unsigned int width, unsigned int height) 
	: state(GAME_ACTIVE), width(width), height(height) {

	// Shader Loading ---------------------------------------------------------
	std::string spriteShaderName = "sprite";
	Renderer::LoadShader(spriteShaderName, 
		"res\\shaders\\main2D.vert", "res\\shaders\\main2D.frag");

	glm::mat4 projection = glm::ortho
	(	0.0f, static_cast<float>(this->width),		//left, right
		static_cast<float>(this->height), 0.0f,		//bottom, top
		-1.0f, 1.0f									//zNear, zFar
	);
	Renderer::GetShader(spriteShaderName).SetUniform("projection", projection);
	Renderer::GetShader(spriteShaderName).SetUniform("image", 0);

	m_SpRenderer.reset(new SpriteRenderer(spriteShaderName));
	// Texture loading --------------------------------------------------------
	m_TextureNames = { "background", "al_tr_0", "al_sq_0", "al_cl_0", "al_UFO_0" };

	Renderer::LoadTexture("background", "res\\textures\\background.jpg");
	Renderer::LoadTexture("al_tr_0", "res\\textures\\alien_triangle_0.png", true);
	Renderer::LoadTexture("al_sq_0", "res\\textures\\alien_square_0.png", true);
	Renderer::LoadTexture("al_cl_0", "res\\textures\\alien_circle_0.png", true);
	Renderer::LoadTexture("al_UFO_0", "res\\textures\\alien_UFO_0.png", true);
	Renderer::LoadTexture("player", "res\\textures\\player.png", true);

	//for (size_t i = 1; i != m_TextureNames.size(); i++) {
	//	Renderer::GetTexture(m_TextureNames[i]).SetPar(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//	Renderer::GetTexture(m_TextureNames[i]).SetPar(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	Renderer::GetTexture(m_TextureNames[i]).SetPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	Renderer::GetTexture(m_TextureNames[i]).SetPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//}

	// Level Loading ----------------------------------------------------------
	GameLevel one; one.Load("res\\levels\\test.lvl", this->width, this->height / 2);
	this->levels.push_back(one);
	this->level = 0;

	// Player Initialization --------------------------------------------------
	glm::vec2 playerPos = glm::vec2(
		(this->width / 2.0f) - (PLAYER_SIZE.x / 2.0f),
		(this->height - PLAYER_SIZE.y));

	m_Player.reset(new Entity(playerPos, PLAYER_SIZE, "player"));
}

Game::~Game() {

}

void Game::ProcessInput(float dt) {
	if (this->state == GAME_ACTIVE) {
		float ds = PLAYER_VELOCITY * dt;
		if (this->keys[GLFW_KEY_A]) {
			if (m_Player->position.x >= 0.0f)
				m_Player->position.x -= ds;
		}
		if (this->keys[GLFW_KEY_D]) {
			if (m_Player->position.x <= (this->width - m_Player->size.x))
				m_Player->position.x += ds;
		}
	}
}

void Game::Update(float) {

}

void Game::Render() {
	if (this->state == GAME_ACTIVE) {
		// Draw Background
		m_SpRenderer->DrawSprite(m_TextureNames[0],
			glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		
		// Draw Level
		this->levels[this->level].Draw(*m_SpRenderer);

		// Draw the Player
		m_Player->Draw(*m_SpRenderer);
	}
}
