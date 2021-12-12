#include "space_invaders.h"

using std::string;

SpaceInvaders::SpaceInvaders(unsigned int width, unsigned int height) 
	: state(GAME_ACTIVE), width(width), height(height){
	//load shaders
	Renderer::LoadShader("sprite",
						 "res\\shaders\\main_vert_2D.shader", 
						 "res\\shaders\\main_frag_2D.shader");
	//configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	Renderer::GetShader("sprite").SetUniform("image", 0);
	Renderer::GetShader("sprite").SetUniform("projection", projection);
	//set render-specific controls
	sprite.reset(new SpriteRenderer(Renderer::GetShader("sprite")));
	Renderer::LoadTexture
	("res\\textures\\alien_triangle_0.png", true, "alient_triangle_0");
}

SpaceInvaders::~SpaceInvaders() {

}

void SpaceInvaders::ProcessInput(float) {

}

void SpaceInvaders::Update(float) {

}

void SpaceInvaders::Render() {
	sprite->DrawSprite(Renderer::GetTexture("alien_triangle_0"),
		glm::vec2(1.0f, 1.0f),			//position 
		glm::vec2(1.0f, 1.0f), 0.0f,	//size / rotation
		glm::vec3(1.0f, 1.0f, 1.0f));		//color
}

void SpaceInvaders::NotYetImplemented() {

}

void SpaceInvaders::Debug() {

}