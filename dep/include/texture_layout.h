#ifndef TEXTURE_LAYOUT_H
#define TEXTURE_LAYOUT_H

#include <glad/glad.h>

#include <vector>
#include <utility>

class TextureLayout {
public:
	TextureLayout(GLenum state, GLenum format) 
		: m_Type(state), m_Format(format) { }

	inline GLenum GetType() const { return m_Type; }
	inline GLenum GetFormat() const { return m_Format; }

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
	GLenum m_Format;
	std::vector<std::pair<GLenum, GLenum>> m_Layout;
};

#endif