#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader) : m_shader(shader){
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    VertexBufferLayout vbl;
    vbl.Push<float>(4);
    m_quadVAO.Bind();
    m_ibo.reset(new IndexBuffer(indices, 6));
    VertexBuffer vb(vertices, sizeof(vertices));
    m_quadVAO.AddBuffer(vb, vbl);
    //this->quadVAO.Unbind();       //--> Usually unnecessary.
}

SpriteRenderer::~SpriteRenderer() {

}

void SpriteRenderer::DrawSprite(Texture& texture, glm::vec2 position,
	glm::vec2 size, float rotate, glm::vec3 color) {
    m_shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    m_shader.SetUniform("model", model);
    m_shader.SetUniform("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    Renderer::Render(m_quadVAO, *m_ibo, m_shader);
}