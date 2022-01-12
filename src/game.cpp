#include "game.h"

Game::Game(unsigned int width, unsigned int height) 
	:	state(GAME_MENU), 
		width(width), height(height), 
		m_PlayerShots(0), m_AlienShots(0) {
	
	// Shader Loading ---------------------------------------------------------
	std::string spriteShaderName = "sprite";
	Renderer::LoadShader(spriteShaderName, 
		"res\\shaders\\main2D.vert",
		"res\\shaders\\main2D.frag");

	glm::mat4 projection = glm::ortho
	(	0.0f, static_cast<float>(this->width),		//left, right
		static_cast<float>(this->height), 0.0f,		//bottom, top
		-1.0f, 1.0f									//zNear, zFar
	);
	Renderer::GetShader(spriteShaderName).SetUniform("projection", projection);
	Renderer::GetShader(spriteShaderName).SetUniform("image", 0);

	m_SpRenderer.reset(new SpriteRenderer(spriteShaderName));

	Shader& bitmapFontShader = Renderer::LoadShader(
		"BitmapFont_game",
		"res\\shaders\\main2D.vert",
		"res\\shaders\\bitmap2D.frag");
	bitmapFontShader.SetUniform("projection", projection);
	bitmapFontShader.SetUniform("model", glm::mat4(1.0f));
	bitmapFontShader.SetUniform("image", 0);

	// Texture loading --------------------------------------------------------
	Renderer::LoadTexture("background",	"res\\textures\\background_1.jpg",		false);
	Renderer::LoadTexture("al_tr_0",	"res\\textures\\alien_triangle_0.png",	true);
	Renderer::LoadTexture("al_tr_1",	"res\\textures\\alien_triangle_1.png", true);
	Renderer::LoadTexture("al_tr_2",	"res\\textures\\alien_triangle_2.png", true);
	Renderer::LoadTexture("al_sq_0",	"res\\textures\\alien_square_0.png",	true);
	Renderer::LoadTexture("al_sq_1",	"res\\textures\\alien_square_1.png", true);
	Renderer::LoadTexture("al_sq_2",	"res\\textures\\alien_square_2.png", true);
	Renderer::LoadTexture("al_cl_0",	"res\\textures\\alien_circle_0.png",	true);
	Renderer::LoadTexture("al_cl_1",	"res\\textures\\alien_circle_1.png", true);
	Renderer::LoadTexture("al_cl_2",	"res\\textures\\alien_circle_2.png", true);
	Renderer::LoadTexture("al_UFO_0",	"res\\textures\\alien_UFO_0.png",		true);
	Renderer::LoadTexture("al_UFO_1",	"res\\textures\\alien_UFO_1.png", true);
	Renderer::LoadTexture("al_UFO_2",	"res\\textures\\alien_UFO_2.png", true);
	Renderer::LoadTexture("player",		"res\\textures\\player.png",			true);
	Renderer::LoadTexture("bullet_1a",	"res\\textures\\bullet_1a.png",			true);
	Renderer::LoadTexture("bullet_2a",	"res\\textures\\bullet_2a.png",			true);

	// Font Loading -----------------------------------------------------------
	m_Font.reset(new BitmapFont(
		bitmapFontShader, Renderer::LoadTexture("BitmapFont_game")));
	m_Font->Load("res\\bitmap\\batang.bff");
	m_Font->SetNormalY(true);
	m_Font->invertYAxis = true;
	m_Font->scale = 50.0f;

	// Level Loading ----------------------------------------------------------
	BorderOffset borders;
	borders.top = TOP_HUD_SIZE;
	borders.down = BOTTOM_HUD_SIZE;
	
	GameLevel one;
	one.borderOffset = borders;
	one.Load("res\\levels\\classic.lvl", this->width, this->height);
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
	switch (this->state) {
		case (GAME_MENU) :{
			if (this->keys[GLFW_KEY_ENTER] && !this->keysProcessed[GLFW_KEY_ENTER]) {
				this->state = GAME_ACTIVE;
			}
		} break;
		case (GAME_ACTIVE): {
			float ds = PLAYER_VELOCITY * dt;
			if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT]) {
				if (m_Player->position.x >= 0.0f)
					m_Player->position.x -= ds;
				if (m_Player->position.x < 0.0f)
					m_Player->position.x = 0.0f;
			}
			if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT]) {
				if (m_Player->position.x <= (this->width - m_Player->size.x))
					m_Player->position.x += ds;
				if (m_Player->position.x > this->width - m_Player->size.x)
					m_Player->position.x = this->width - m_Player->size.x;
			}
			if (this->keys[GLFW_KEY_SPACE] && m_PlayerShots == 0) {
				float posX = m_Player->position.x + ((PLAYER_SIZE.x / 2) - (BULLET_SIZE.x / 2));
				float posY = m_Player->position.y - BULLET_SIZE.y;
				glm::vec2 bulletPos = glm::vec2(posX, posY);
				Bullet b(bulletPos, BULLET_SIZE, BULLET_VELOCITY, "bullet_1a", PLAYER);
				b.color = glm::vec3(0.0f, 1.0f, 0.0f);
				m_Bullets.push_back(b);
				++m_PlayerShots;
			}
		} break;
	}
}

void Game::Update(float) {
	float sinFunction = 0.5 * (sin(glfwGetTime() * 3.14) + 1);
	float dt = Renderer::GetDeltaTime();

	if (!m_Bullets.empty()) {
		std::vector<Bullet>::iterator i = m_Bullets.begin();
		while (i != m_Bullets.end()) {
			if (!(i->offScreen || i->destroyed)) {
				if (i->shooter == PLAYER)
					i->color = glm::vec3(0.0f, sinFunction, 0.0f);
				else
					i->color = glm::vec3(sinFunction, 0.0f, 0.0f);
				i->Move(dt, this->height);
				++i;
			}
			else {
				if (i->shooter == PLAYER)
					--m_PlayerShots;
				else if (i->shooter == ALIEN)
					--m_AlienShots;

				i = m_Bullets.erase(i);
			}
		}
	}

	for (auto& alien : this->levels[this->level].aliens) {
		if (alien.destroyed != true) {
			alien.Move(dt, this->width);
		}
	}

	DoCollisions();
}

void Game::Render() {
	switch (this->state) {
		case (GAME_MENU): {
			m_SpRenderer->DrawSprite("background",
				glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);

			m_Font->SetColor(glm::vec4(0.0f, std::abs(sin(glfwGetTime())), 0.0f, 1.0f));
			glm::vec2 textSize = m_Font->GetSize("<Press Enter to Start>");
			m_Font->Print("<Press Enter to Start>",
				(this->width / 2) - (textSize.x / 2), 
				(this->height  / 2) - (textSize.y / 2));
		} break;
		case (GAME_ACTIVE): {
			// Draw Backgroundd
			m_SpRenderer->DrawSprite("background",
				glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);

			// Draw Level
			this->levels[this->level].Draw(*m_SpRenderer);

			// Draw the Player
			m_Player->Draw(*m_SpRenderer);

			// Draw Every Bullet
			if (!m_Bullets.empty()) {
				for (auto& b : m_Bullets)
					b.Draw(*m_SpRenderer);
			}
		} break;
	}
}

void Game::DoCollisions() {
	for (Entity& alien : this->levels[this->level].aliens) {
		if (!alien.destroyed) {
			if (!m_Bullets.empty()) {
				for (Bullet& bullet : m_Bullets) {
					if (!bullet.destroyed) {
						if (bullet.shooter == PLAYER && CheckCollision(alien, bullet)) {
							alien.destroyed = bullet.destroyed = true;
						}
					}
				}
			}
		}
	}
}

// square AABB collision
bool Game::CheckCollision(Entity& one, Entity& two) {
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
		two.position.x + two.size.x >= one.position.x;

	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;

	return collisionX && collisionY;
}