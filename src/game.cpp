#include "game.h"

Game::Game(unsigned int width, unsigned int height) 
	: state(GAME_ACTIVE), width(width), height(height), m_TimeTracker(1) {
	
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
	Renderer::LoadTexture("background",	"res\\textures\\background_1.jpg",		false);
	Renderer::LoadTexture("al_tr_0",	"res\\textures\\alien_triangle_0.png",	true);
	Renderer::LoadTexture("al_sq_0",	"res\\textures\\alien_square_0.png",	true);
	Renderer::LoadTexture("al_cl_0",	"res\\textures\\alien_circle_0.png",	true);
	Renderer::LoadTexture("al_UFO_0",	"res\\textures\\alien_UFO_0.png",		true);
	Renderer::LoadTexture("player",		"res\\textures\\player.png",			true);
	Renderer::LoadTexture("bullet_1a",	"res\\textures\\bullet_1a.png",			true);
	Renderer::LoadTexture("bullet_2a",	"res\\textures\\bullet_2a.png",			true);

	// Level Loading ----------------------------------------------------------
	GameLevel one;
	one.borderOffset = glm::vec2(50.0f, 0.0f);
	one.Load("res\\levels\\test.lvl", this->width, this->height / 2);
	this->levels.push_back(one);
	this->level = 0;

	// Player Initialization --------------------------------------------------
	glm::vec2 playerPos = glm::vec2(
		(this->width / 2.0f) - (PLAYER_SIZE.x / 2.0f),
		(this->height - PLAYER_SIZE.y));

	m_Player.reset(new Entity(playerPos, PLAYER_SIZE, "player", glm::vec3(0.0f, 1.0f, 0.0f)));
}

Game::~Game() {

}

void Game::ProcessInput(float dt) {
	if (this->state == GAME_ACTIVE) {
		float ds = PLAYER_VELOCITY * dt;
		if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT]) {
			if (m_Player->position.x >= 0.0f)
				m_Player->position.x -= ds;
		}
		if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT]) {
			if (m_Player->position.x <= (this->width - m_Player->size.x))
				m_Player->position.x += ds;
		}
		if (this->keys[GLFW_KEY_SPACE] && m_TimeTracker >= 1) {
			if (this->sprite)
				m_Sprite = "bullet_1a";
			else
				m_Sprite = "bullet_2a";

			float posX = m_Player->position.x + ((PLAYER_SIZE.x / 2) - (BULLET_SIZE.x / 2));
			float posY = m_Player->position.y - BULLET_SIZE.y;
			glm::vec2 bulletPos = glm::vec2(posX, posY);
			Bullet b(bulletPos, BULLET_SIZE, BULLET_VELOCITY, m_Sprite, PLAYER);
			b.color = glm::vec3(0.0f, 1.0f, 0.0f);
			m_Bullets.push_back(b);
			m_TimeTracker = 0;
		}
		if (this->keys[GLFW_KEY_Q])
			sprite = true;
		if (this->keys[GLFW_KEY_E])
			sprite = false;
	}
}

void Game::Update(float) {
	m_TimeTracker += Renderer::GetDeltaTime();

	if (!m_Bullets.empty()) {
		std::vector<Bullet>::iterator i = m_Bullets.begin();
		while (i != m_Bullets.end()) {
			if (!i->offScreen) {
				i->Move(Renderer::GetDeltaTime(), this->height);
				++i;
			}	else
				i = m_Bullets.erase(i);
		}
	}

	DoCollisions();
}

void Game::Render() {
	if (this->state == GAME_ACTIVE) {
		// Draw Backgroundd
		m_Sprite = "background";
		m_SpRenderer->DrawSprite(m_Sprite,
			glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		
		// Draw Level
		this->levels[this->level].Draw(*m_SpRenderer);

		// Draw the Player
		m_Player->Draw(*m_SpRenderer);

		// Draw Every Bullet
		if (!m_Bullets.empty()) {
			for (auto b : m_Bullets)
				b.Draw(*m_SpRenderer);
		}
	}
}

void Game::DoCollisions() {
	for (Entity& alien : this->levels[this->level].aliens) {
		if (!alien.destroyed) {
			if (!m_Bullets.empty()) {
				for (Bullet& bullet : m_Bullets) {
					if (bullet.shooter == PLAYER && CheckCollision(alien, bullet)) {
						alien.destroyed = true;
					}
				}
			}
		}
	}
}

bool Game::CheckCollision(Entity& one, Entity& two) {
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
		two.position.x + two.size.x >= one.position.x;

	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;

	return collisionX && collisionY;
}
