#include "invaders.h"

Invaders::Invaders(unsigned int width, unsigned int height) 
	: state(GAME_ACTIVE), width(width), height(height), m_SpriteTextName("al_tr_0") {

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

	m_Sprite.reset(new SpriteRenderer(spriteShaderName));
	Renderer::LoadTexture(m_SpriteTextName, "res\\textures\\alien_triangle_0.png", true);
	Renderer::GetTexture(m_SpriteTextName).SetPar(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	Renderer::GetTexture(m_SpriteTextName).SetPar(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Renderer::GetTexture(m_SpriteTextName).SetPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	Renderer::GetTexture(m_SpriteTextName).SetPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

Invaders::~Invaders() {

}

void Invaders::ProcessInput(float) {

}

void Invaders::Update(float) {

}

void Invaders::Render() {
	m_Sprite->DrawSprite(m_SpriteTextName,
		glm::vec2(200.0f, 100.0f),			//position
		glm::vec2(400.0f, 300.0f), 0.0f,	//size, rotation
		glm::vec3(1.0f, 1.0f, 1.0f));	//color
}
