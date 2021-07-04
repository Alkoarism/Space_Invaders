#ifndef TEXTURE_LAYOUT_H
#define TEXTURE_LAYOUT_H

#include <glad/glad.h>

#include <vector>
#include <utility>

class TextureLayout {
public:
	TextureLayout(GLenum state) : m_Type(state) { }

	GLenum GetType() const { return m_Type; }

	void AddPar(GLenum first, GLenum second)
		{ m_Layout.push_back(std::make_pair(first, second)); }
	void RemovePar() { m_Layout.pop_back(); }

	void Run() const {
		for (auto a : m_Layout) {
			glTexParameteri(m_Type, a.first, a.second);
		}
	}

private:
	GLenum m_Type;
	std::vector<std::pair<GLenum, GLenum>> m_Layout;
};

#endif