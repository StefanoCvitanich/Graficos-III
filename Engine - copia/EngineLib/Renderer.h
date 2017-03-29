#ifndef RENDERER_H
#define RENDERER_H
//========================================================================================
#include "Utility.h"
#include "vertexbuffer.h"
#include <vector>
#include <string>
//========================================================================================
struct IDirect3D9;
struct IDirect3DDevice9;

struct D3DXMATRIX;
typedef D3DXMATRIX* Matrix;

struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

struct IDirect3DTexture9;
typedef IDirect3DTexture9* Texture;
#define NoTexture NULL

typedef interface ID3DXFont ID3DXFont;
typedef interface ID3DXFont *LPD3DXFONT;
typedef ID3DXFont* Font;

namespace pg2{
	class IndexBuffer;
	class VertexBuffer;
}
//========================================================================================
struct AABB{
	float maxPointX, maxPointY, maxPointZ;
	float minPointX, minPointY, minPointZ;
	float max[3], min[3];
	Vector3 points[8];
};
//========================================================================================
//Se encarga de la comunicacion con el Direct3D
class Renderer{
public:
	DllExport Renderer();
	DllExport ~Renderer();

	DllExport bool init(HWND hWnd, unsigned int uiW, unsigned int uiH);
	DllExport void beginFrame();

	DllExport void draw(Vertex* gameVertex, Primitive primitive, int vertexCount);
	DllExport void draw(TexturedVertex* gameVertex, Primitive primitive, int vertexCount);

	Font& createFont(int charSize, std::string textFont, bool italic);
	RECT& createRect(int x, int y, int width, int height);
	void displayText(Font& font, RECT& rect, std::string text);

	DllExport void endFrame();

	DllExport const Texture loadTexture(const std::string& textureName, D3DCOLOR ColorKey);
	DllExport void setCurrentTexture(const Texture& texture);

	void setMatrix(MatrixType matrixType ,const Matrix& matrix);

	Matrix& getProjectionMatrix();

	pg2::VertexBuffer* createVertexBuffer(size_t vertexSize, unsigned int fvf);
	pg2::IndexBuffer* createIndexBuffer();

	void setCurrentIndexBuffer(pg2::IndexBuffer* indexBuffer);
	void setCurrentVertexBuffer(pg2::VertexBuffer* vertexBuffer);

	void drawCurrentBuffers(Primitive primitive);

private:
	unsigned int uiWidth;
	unsigned int uiHeight;
	HWND _hwnd;

	pg1::VertexBuffer* v_buffer;
	pg1::VertexBuffer* texturedVBuffer;

	pg2::IndexBuffer* _indexBuffer;
	pg2::VertexBuffer* _vertexBuffer;

	IDirect3D9* m_pkD3D;
	IDirect3DDevice9* m_pkDevice;

	std::vector<Texture> _textureList;

	Matrix _projectionMatrix;
};
//========================================================================================
#endif