#include "game.h"

std::default_random_engine Game::engine(std::chrono::system_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> Game::randomDist(0, 10);

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

	// Texture loading e config --------------------------------------------------
	Renderer::LoadTexture("background",		"res\\textures\\background.jpg",		false);
	Renderer::LoadTexture("background_1",	"res\\textures\\background_1.jpg", false);
	Renderer::LoadTexture("al_tr_0",		"res\\textures\\alien_triangle_0.png",	true);
	Renderer::LoadTexture("al_tr_1",		"res\\textures\\alien_triangle_1.png", true);
	Renderer::LoadTexture("al_tr_2",		"res\\textures\\alien_triangle_2.png", true);
	Renderer::LoadTexture("al_sq_0",		"res\\textures\\alien_square_0.png",	true);
	Renderer::LoadTexture("al_sq_1",		"res\\textures\\alien_square_1.png", true);
	Renderer::LoadTexture("al_sq_2",		"res\\textures\\alien_square_2.png", true);
	Renderer::LoadTexture("al_cl_0",		"res\\textures\\alien_circle_0.png",	true);
	Renderer::LoadTexture("al_cl_1",		"res\\textures\\alien_circle_1.png", true);
	Renderer::LoadTexture("al_cl_2",		"res\\textures\\alien_circle_2.png", true);
	Renderer::LoadTexture("al_UFO_0",		"res\\textures\\alien_UFO_0.png",		true);
	Renderer::LoadTexture("al_UFO_1",		"res\\textures\\alien_UFO_1.png", true);
	Renderer::LoadTexture("al_UFO_2",		"res\\textures\\alien_UFO_2.png", true);
	Renderer::LoadTexture("player",			"res\\textures\\player.png",			true);
	Renderer::LoadTexture("bullet_1a",		"res\\textures\\bullet_1a.png",			true);
	Renderer::LoadTexture("bullet_2a",		"res\\textures\\bullet_2a.png",			true);

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
	glm::vec2 playerSize = glm::vec2(
		this->levels[level].unitWidth,
		this->levels[level].unitHeight);

	m_playerStartPos = glm::vec2(
		(this->width - playerSize.x) / 2.0f,
		this->height - (this->levels[level].borderOffset.down + this->levels[level].unitHeight));

	m_Player.reset(new Entity(m_playerStartPos, playerSize, "player", glm::vec3(0.0f, 1.0f, 0.0f)));
}

Game::~Game() {

}

void Game::ProcessInput(float dt) {
	switch (this->state) {
		case (GAME_MENU) :{
			if (this->keys[GLFW_KEY_ENTER] && !this->keysProcessed[GLFW_KEY_ENTER]) {
				this->state = GAME_ACTIVE;
				this->keysProcessed[GLFW_KEY_ENTER] = true;

				if (this->levels[this->level].IsCompleted()) {
					this->levels[this->level].Restart(this->width, this->height);
					m_Bullets.clear();
					m_AlienShots = 0;
					m_PlayerShots = 0;
				}
			}
		} break;
		case (GAME_ACTIVE): {
			if (!m_Player->destroyed) {
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
					GenerateBullet(*m_Player, LASER);
					++m_PlayerShots;
				}
			}
			else {
				if (this->keys[GLFW_KEY_ENTER] && !this->keysProcessed[GLFW_KEY_ENTER]) {
					this->keysProcessed[GLFW_KEY_ENTER] = true;
					m_Player->destroyed = false;
					m_Player->position = m_playerStartPos;
					m_Bullets.clear();
					m_PlayerShots = m_AlienShots = 0;
				}
			}
		} break;
		case (GAME_END): {
			if (this->keys[GLFW_KEY_ENTER] && !this->keysProcessed[GLFW_KEY_ENTER]) {
				this->state = GAME_MENU;
				this->keysProcessed[GLFW_KEY_ENTER] = true;
			}
		} break;
	}
}

void Game::Update(float dt) {
	if (this->state == GAME_ACTIVE && !m_Player->destroyed) {

		if (!m_Bullets.empty()) {
			std::vector<Bullet>::iterator bullet = m_Bullets.begin();
			while (bullet != m_Bullets.end()) {
				if (!(bullet->hitScreenBorder || bullet->destroyed)) {
					if (bullet->type == LASER)
						bullet->Move(dt, TOP_HUD_SIZE);
					else
						bullet->Move(dt, this->height - BOTTOM_HUD_SIZE);

					++bullet;
				}
				else {
					if (bullet->type == LASER)
						--m_PlayerShots;
					else 
						--m_AlienShots;

					bullet = m_Bullets.erase(bullet);
				}
			}
		}

		size_t totalAliens = this->levels[level].aliens.size();
		for (size_t cnt = 0; cnt != totalAliens; ++cnt) {
			Alien& alien = this->levels[this->level].aliens[cnt];
			if (!alien.destroyed) {
				alien.Move(dt, this->width);

				if (this->m_AlienShots < 3) {

					int randomNbr = this->randomDist(this->engine);
					if (randomNbr > 5) {
						
						// No need to check previous aliens
						bool willShoot = true;
						for (size_t i = cnt; i != totalAliens; ++i) {
							Alien& target = this->levels[level].aliens[i];
							if (target.gridPos.x == alien.gridPos.x
								&& target.gridPos.y > alien.gridPos.y
								&& !target.destroyed)
								
								willShoot = false;
						}

						if (willShoot) {
							if (alien.shape == TRIANGLE)
								GenerateBullet(alien, WIGGLY);
							else
								GenerateBullet(alien, randomNbr < 9 ? SLOW : FAST);

							++m_AlienShots;
						}
					}
				}
			}
		}

		DoCollisions();

		if (this->levels[level].IsCompleted()) {
			this->state = GAME_END;
		}
	}
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
			// Draw Background
			m_SpRenderer->DrawSprite("background_1",
				glm::vec2(0.0f, 0.0f),
				glm::vec2(this->width, TOP_HUD_SIZE),
				0.0f);
			m_SpRenderer->DrawSprite("background_1",
				glm::vec2(0.0f, this->height - BOTTOM_HUD_SIZE),
				glm::vec2(this->width, BOTTOM_HUD_SIZE),
				0.0f);
			m_SpRenderer->DrawSprite("background",
				glm::vec2(0.0f, TOP_HUD_SIZE), 
				glm::vec2(this->width, this->height - (TOP_HUD_SIZE + BOTTOM_HUD_SIZE)),
				0.0f);

			// Draw Level
			this->levels[this->level].Draw(*m_SpRenderer);

			// Draw the Player
			if (!m_Player->destroyed)
				m_Player->Draw(*m_SpRenderer);
			else {
				m_Font->SetColor(glm::vec4(1.0f, std::abs(sin(glfwGetTime())), 1.0f, 1.0f));
				glm::vec2 textSize = m_Font->GetSize("You Died");
				m_Font->Print("You Died",
					(this->width / 2) - (textSize.x / 2),
					(this->height / 2) - (textSize.y / 2));
			}

			// Draw Every Bullet
			if (!m_Bullets.empty()) {
				for (auto& b : m_Bullets)
					b.Draw(*m_SpRenderer);
			}
		} break;
		case (GAME_END): {
			m_SpRenderer->DrawSprite("background",
				glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);

			m_Font->SetColor(glm::vec4(0.0f, std::abs(sin(glfwGetTime())), 0.0f, 1.0f));
			glm::vec2 textSize = m_Font->GetSize("Congratulations!");
			m_Font->Print("Congratulations!",
				(this->width - textSize.x) / 2,
				(this->height - textSize.y) / 2);
		} break;
	}
}

void Game::DoCollisions() {
	if (!m_Bullets.empty()) {
		for (Bullet& bullet : m_Bullets) {
			if (bullet.type == LASER) {
				for (Bullet& bullet2 : m_Bullets) {
					if (bullet2.type != LASER && CheckCollision(bullet, bullet2)) {
						int randNbr = this->randomDist(this->engine);
						switch (bullet2.type) {
							case FAST: {
								if (randNbr < 5)
									bullet2.destroyed = true;
							} break;
							case WIGGLY: {
								if (randNbr < 2)
									bullet2.destroyed = true;
							} break;
							default: {
								bullet2.destroyed = true;
							}
						}

						bullet.destroyed = true;
						break;
					}
				}
				if (bullet.destroyed) 

				for (Entity& alien : this->levels[level].aliens) {
					if (!alien.destroyed && CheckCollision(alien, bullet)) {
						alien.destroyed = bullet.destroyed = true;
					}
				}
			}
			else {
				if (CheckCollision(*m_Player, bullet)) {
					m_Player->destroyed = true;
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

void Game::GenerateBullet(Entity& shooter, BulletType type) {
	std::string texture;
	float posX, posY, speedY;
	glm::vec2 bulletPos, bulletSpeed;
	glm::vec3 color;

	posX = shooter.position.x + ((shooter.size.x / 2) - (BULLET_SIZE.x / 2));
	posY = shooter.position.y + shooter.size.y;
	color = glm::vec3(1.0f, 0.2f, 0.2f);

	switch (type) {
		case LASER: {
			texture = "bullet_1a";
			posY = shooter.position.y - BULLET_SIZE.y;
			speedY = -BULLET_VELOCITY;
			color = glm::vec3(0.0f, 1.0f, 0.0f);
		} break;
		case SLOW: {
			texture = "bullet_2a";
			speedY = BULLET_VELOCITY * 0.75;
		} break;
		case FAST: {
			texture = "bullet_2a";
			speedY = BULLET_VELOCITY * 1.25;
		} break;
		case WIGGLY: {
			texture = "bullet_2a";
			speedY = BULLET_VELOCITY;
		} break;
	}

	bulletPos = glm::vec2(posX, posY);
	bulletSpeed = glm::vec2(0.0f, speedY);
	Bullet b(bulletPos, BULLET_SIZE, bulletSpeed, texture, type);
	b.color = color;
	m_Bullets.push_back(b);
}