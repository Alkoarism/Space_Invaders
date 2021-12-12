#include "OpenGL\renderer.h"

class SpriteRenderer {
public:
	SpriteRenderer(Shader& shader);
	SpriteRenderer(SpriteRenderer&) = delete;
	~SpriteRenderer();

	void DrawSprite(Texture& texture, glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f));
	//IndexBuffer& GetIBO() { return *(m_ibo.get()); } //Dangerous, be careful.

private:
	Shader m_shader;
	std::unique_ptr<IndexBuffer> m_ibo;
	std::unique_ptr<VertexBuffer> m_vbo;
	VertexArray m_quadVAO;
};