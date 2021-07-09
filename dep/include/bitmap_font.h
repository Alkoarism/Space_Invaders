#ifndef _BITMAPFONTCLASS_H
#define _BITMAPFONTCLASS_H

#include <fstream>
#include <string>
#include <memory>
#include <glad\glad.h>

#include "texture.h"
#include "vertex_array.h"

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

class CBitmapFont
{
public:
	CBitmapFont();
	~CBitmapFont() = default;
	bool Load(char* fname);
	void SetCursor(int x, int y);
	void ReverseYAxis(bool State);
	void Bind();
	void Unbind();
	//void Print(char* Text);
	//void Print(char* Text, int x, int y);
	//void ezPrint(char* Text, int x, int y);
	//int  GetWidth(char* Text);

	//Functions i´ve removed
	/*
	void Select();
	void SetBlend();
	void SetColor(float Red, float Green, float Blue);
	void SetScreen(int x, int y);

	*/

private:
	//base stuff I should change with caution
	int m_CellX, m_CellY, m_YOffset, m_RowPitch;
	char Base;
	char Width[256];
	int CurX, CurY;
	float RowFactor, ColFactor;
	float Rd, Gr, Bl;
	bool InvertYAxis;

	//things i´ve added
	Texture m_Texture;
	TextureLayout m_Layout;

	//variables i´ve removed
	/*
	GLuint TexID;
	int RenderStyle;
	*/
};

#endif