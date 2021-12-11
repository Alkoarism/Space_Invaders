#include "space_invaders.h"

using std::string;

SpaceInvaders::SpaceInvaders(unsigned int width, unsigned int height) 
	: state(GAME_ACTIVE), width(width), height(height){
	//load shaders
	Renderer::LoadShader("res\\shaders\\main_vert2D.shader", 
						 "res\\shaders\\main_frag2D.shader", 
						 "sprite");
	//configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width),
		static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	Renderer::GetShader("sprite").SetUniform("image", 0);
	Renderer::GetShader("sprite").SetUniform("projection", projection);
	//set render-specific controls
	sprite.reset(new SpriteRenderer(Renderer::GetShader("sprite")));
	Renderer::LoadTexture("res\\textures\\alien_triangle_0.png");
}

SpaceInvaders::~SpaceInvaders() {

}

void SpaceInvaders::ProcessInput(float) {

}

void SpaceInvaders::Update(float) {

}

void SpaceInvaders::Render() {

}

void SpaceInvaders::NotYetImplemented() {

}

void SpaceInvaders::Debug() {

}