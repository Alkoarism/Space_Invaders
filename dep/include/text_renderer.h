#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

struct FontFileHeader {
//	unsigned char ID1, ID2;
	unsigned char BPP;
	int imageWidth, imageHeight, cellWidth, cellHeight;
	unsigned char startPoint;
};

class TextRenderer {
public:
	TextRenderer();
	~TextRenderer() = default;

	bool Load(char* fName);
	void SetScreen(int, int);
	void SetCursor(int, int);
	void Bind();
	void Unbind();
	void Print(char*);
	void Print(char*, int, int);
	int GetWidth(char*);

private:

};

#endif