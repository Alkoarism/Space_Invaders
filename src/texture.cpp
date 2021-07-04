#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STBI_FAILURE_USERMSG
#define STBI_ONLYJPEG

#include <iostream>
#include <utility>

#include "texture.h"

Texture::Texture(TextureLayout layout, const char* location) : m_Layout(layout) {
	glGenTextures(1, &m_TextureID);
	glBindTexture(m_Layout.GetType(), m_TextureID);

	stbi_set_flip_vertically_on_load(true);
	int imgWidth, imgHeight, nrChannels;
	unsigned char* data
		= stbi_load(location, &imgWidth, &imgHeight, &nrChannels, 0);
	if (data) {
		glTexImage2D(m_Layout.GetType(), 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(m_Layout.GetType());
	}
	else {
		const char* failLog = stbi_failure_reason();
		std::cout << "FAILED_TO_LOAD_TEXTURE\n" << failLog << std::endl;
	}
	stbi_image_free(data);

	m_Layout.Run();
}

Texture::Texture(Texture&& other) noexcept
	: m_TextureID(other.m_TextureID), m_Layout(other.m_Layout) {
	other.m_TextureID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept {
	if (this != &other) {
		Release();
		std::swap(m_TextureID, other.m_TextureID);
		m_Layout = other.m_Layout;
	}
	return *this;
}

void Texture::Bind() const {
	glBindTexture(m_Layout.GetType(), m_TextureID);
}

void Texture::Unbind() const {
	glBindTexture(m_Layout.GetType(), 0);
}