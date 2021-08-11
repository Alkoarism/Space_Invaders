#ifndef _BITMAP_FONTCLASS_H
#define _BITMAP_FONTCLASS_H

#include "texture.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

#define BFG_MAXSTRING 255     // Maximum string length

#define WIDTH_DATA_OFFSET  20 // Offset to width data with BFF file
#define MAP_DATA_OFFSET   276 // Offset to texture image data with BFF file

typedef struct
{
	unsigned char ID1, ID2;
	unsigned char BPP;
	int ImageWidth, ImageHeight, CellWidth, CellHeight;
	unsigned char StartPoint;
}FontFileHeader;

class BitmapFont
{
public:
	BitmapFont(const char*, const char*);

	bool Load(char* fname);
	int  GetWidth(char* Text);

	void SetCursor(int x, int y);
	void ReverseYAxis(bool State);
	void Print(const char* Text);
	void Print(const char* Text, int x, int y);
	void Select();

	void SetCamera(const glm::mat4&) const;
	void SetView(const glm::mat4&) const;
	void SetModel(const glm::mat4&) const;

private:
	int m_CellX, m_CellY, m_YOffset, m_RowPitch;
	char m_Base;
	char m_Width[256];
	int m_CurX, m_CurY;
	float m_RowFactor, m_ColFactor;
	bool m_InvertYAxis;

	Shader m_Shader;
	Texture m_Texture;
	TextureLayout m_Layout;

	void Bind();
	void Unbind();
};

#endif