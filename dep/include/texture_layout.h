#ifndef TEXTURE_LAYOUT_H
#define TEXTURE_LAYOUT_H

#include "headers.h"

class TextureLayout {
public:
	TextureLayout() = default;
	TextureLayout(GLenum type, GLenum format) 
		: m_Type(type), m_Format(format) { }

	inline GLenum GetType() const { return m_Type; }
	inline GLenum GetFormat() const { return m_Format; }

	inline void SetType(GLenum type) { m_Type = type; }
	inline void SetFormat(GLenum format) { m_Format = format; }

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