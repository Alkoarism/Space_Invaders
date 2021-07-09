#include "bitmap_font.h"

using namespace std;

CBitmapFont::CBitmapFont()
{
    CurX = CurY = 0;
    Rd = Gr = Bl = 1.0f;
    InvertYAxis = false;
}

bool CBitmapFont::Load(char* fname)
{
    fstream in;
    char bpp;
    int ImgX, ImgY;

    in.open(fname, ios_base::binary | ios_base::in);

    if (in.fail())
        return false;

    // Get Filesize
    in.seekg(0, ios_base::end);
    auto fileSize = in.tellg();
    in.seekg(0, ios_base::beg);

    // allocate space for file data
    unique_ptr<char> dat(new char[fileSize]);

    // Read filedata
    if (!dat)
        return false;

    in.read(dat.get(), fileSize);

    if (in.fail())
    {
        in.close();
        return false;
    }

    in.close();

    // Check ID is 'BFF2'
    if ((unsigned char)dat.get()[0] != 0xBF || (unsigned char)dat.get()[1] != 0xF2)
        return false;

    // Grab the rest of the header
    memcpy(&ImgX, &dat.get()[2], sizeof(int));
    memcpy(&ImgY, &dat.get()[6], sizeof(int));
    memcpy(&m_CellX, &dat.get()[10], sizeof(int));
    memcpy(&m_CellY, &dat.get()[14], sizeof(int));
    bpp = dat.get()[18];
    Base = dat.get()[19];

    // Check filesize
    if (fileSize != ((MAP_DATA_OFFSET)+((ImgX * ImgY) * (bpp / 8))))
        return false;

    // Calculate font params
    m_RowPitch = ImgX / m_CellX;
    ColFactor = (float)m_CellX / (float)ImgX;
    RowFactor = (float)m_CellY / (float)ImgY;
    m_YOffset = m_CellY;

    // Determine blending options based on BPP
    switch (bpp)
    {
    case 8:
        //OpenGL supports single channel images through the RED channel
        m_Layout.SetFormat(GL_RED);
        break;

    case 24:
        m_Layout.SetFormat(GL_RGB);
        break;

    case 32:
        m_Layout.SetFormat(GL_RGBA);
        break;

    default: // Unsupported BPP
        return false;
        break;
    }

    // Allocate space for image
    unique_ptr<char> img(new char[(ImgX * ImgY) * (bpp / 8)]);

    if (!img)
        return false;

    // Grab char widths
    memcpy(Width, &dat.get()[WIDTH_DATA_OFFSET], 256);

    // Grab image data
    memcpy(img.get(), &dat.get()[MAP_DATA_OFFSET], (ImgX * ImgY) * (bpp / 8));

    m_Layout.SetType(GL_TEXTURE_2D);

    // Fonts should be rendered at native resolution so no need for texture filtering
    m_Layout.AddPar(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    m_Layout.AddPar(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Stop chararcters from bleeding over edges
    m_Layout.AddPar(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    m_Layout.AddPar(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    m_Texture.SetLayout(m_Layout);
    m_Texture.DirectLoad(img.get(), ImgX, ImgY);

    return true;
}

// Set the position for text output, this will be updated as text is printed
void CBitmapFont::SetCursor(int x, int y)
{
    CurX = x;
    CurY = y;
}

void CBitmapFont::Bind()
{
    m_Texture.Bind();
}

void CBitmapFont::Unbind()
{
    m_Texture.Unbind();
}

void CBitmapFont::ReverseYAxis(bool State)
{
    if (State)
        m_YOffset = -m_CellY;
    else
        m_YOffset = m_CellY;

    InvertYAxis = State;
}

//// Prints text at the cursor position, cursor is moved to end of text
//void CBitmapFont::Print(char* Text)
//{
//    int sLen, Loop;
//    int Row, Col;
//    float U, V, U1, V1;
//
//    sLen = (int)strnlen(Text, BFG_MAXSTRING);
//
//    glBegin(GL_QUADS);
//
//    for (Loop = 0; Loop != sLen; ++Loop)
//    {
//        Row = (Text[Loop] - Base) / m_RowPitch;
//        Col = (Text[Loop] - Base) - Row * m_RowPitch;
//
//        U = Col * ColFactor;
//        V = Row * RowFactor;
//        U1 = U + ColFactor;
//        V1 = V + RowFactor;
//
//        glTexCoord2f(U, V1); glVertex2i(CurX, CurY);
//        glTexCoord2f(U1, V1); glVertex2i(CurX + m_CellX, CurY);
//        glTexCoord2f(U1, V); glVertex2i(CurX + m_CellX, CurY + m_YOffset);
//        glTexCoord2f(U, V); glVertex2i(CurX, CurY + m_YOffset);
//
//        CurX += Width[Text[Loop]];
//    }
//    glEnd();
//
//}

//// Prints text at a specifed position, again cursor is updated
//void CBitmapFont::Print(char* Text, int x, int y)
//{
//    int sLen, Loop;
//    int Row, Col;
//    float U, V, U1, V1;
//
//    CurX = x;
//    CurY = y;
//
//    sLen = (int)strnlen(Text, BFG_MAXSTRING);
//
//    glBegin(GL_QUADS);
//
//    for (Loop = 0; Loop != sLen; ++Loop)
//    {
//        Row = (Text[Loop] - Base) / m_RowPitch;
//        Col = (Text[Loop] - Base) - Row * m_RowPitch;
//
//        U = Col * ColFactor;
//        V = Row * RowFactor;
//        U1 = U + ColFactor;
//        V1 = V + RowFactor;
//
//        glTexCoord2f(U, V1);  glVertex2i(CurX, CurY);
//        glTexCoord2f(U1, V1);  glVertex2i(CurX + m_CellX, CurY);
//        glTexCoord2f(U1, V); glVertex2i(CurX + m_CellX, CurY + m_CellY);
//        glTexCoord2f(U, V); glVertex2i(CurX, CurY + m_CellY);
//
//        CurX += Width[Text[Loop]];
//    }
//    glEnd();
//}
//
//// Lazy way to draw text.
//// Preserves all GL attributes and does everything for you.
//// Performance could be an issue.
//void CBitmapFont::ezPrint(char* Text, int x, int y)
//{
//    GLint CurMatrixMode;
//    GLint ViewPort[4];
//
//    // Save current setup
//    glGetIntegerv(GL_MATRIX_MODE, &CurMatrixMode);
//    glGetIntegerv(GL_VIEWPORT, ViewPort);
//    glPushAttrib(GL_ALL_ATTRIB_BITS);
//
//    // Setup projection
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    if (InvertYAxis)
//        glOrtho(0, ViewPort[2], ViewPort[3], 0, -1, 1);
//    else
//        glOrtho(0, ViewPort[2], 0, ViewPort[3], -1, 1);
//    glDisable(GL_DEPTH_TEST);
//    glDepthMask(false);
//
//    // Setup Modelview
//    glMatrixMode(GL_MODELVIEW);
//    glPushMatrix();
//    glLoadIdentity();
//
//    // Setup Texture, color and blend options
//    glEnable(GL_TEXTURE_2D);
//    glBindTexture(GL_TEXTURE_2D, TexID);
//    SetBlend();
//
//    // Render text
//    Print(Text, x, y);
//
//    // Restore previous state
//    glPopAttrib();
//
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//    glPopMatrix();
//
//    glMatrixMode(CurMatrixMode);
//}
//
//// Returns the width in pixels of the specified text
//int CBitmapFont::GetWidth(char* Text)
//{
//    int Size = 0, sLen, Loop;
//
//    // How many chars in string?
//    sLen = (int)strnlen(Text, BFG_MAXSTRING);
//
//    // Add up all width values
//    for (Loop = 0; Loop != sLen; ++Loop)
//    {
//        Size += Width[Text[Loop]];
//    }
//
//    return Size;
//}