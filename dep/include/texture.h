#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

//The glTexParameteri on the texture constructor needs to be
//further analyzed and improved in order to make the class
//more corret relating to it´s configuration

class Texture {
public:
	Texture(GLenum, const char*);

	~Texture() { Release(); }

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;

	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;

	void Bind() const;
	void Unbind() const;

	inline unsigned char* GetData() { return m_Data; }

private:
	GLuint m_TextureID;
	GLenum m_Target;
	unsigned char* m_Data;
	int m_ImgWidth, m_ImgHeight, m_NrChannels;

	void Release() noexcept {
		glDeleteTextures(1, &m_TextureID);
		m_TextureID = 0;
	}
};

#endif