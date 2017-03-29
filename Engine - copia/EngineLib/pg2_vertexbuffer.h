
//---------------------------------------------------------------------------
#ifndef PG2_VERTEXBUFFER_H
#define PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>
#include <cassert>
//---------------------------------------------------------------------------
class Renderer;
namespace pg2
{
//---------------------------------------------------------------------------
class VertexBuffer
{
public:
	VertexBuffer (Renderer& rkRenderer, IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF);
	~VertexBuffer ();

	void bind ();
	void setVertexData (const void* pakVertices, size_t uiVertexCount);
	
	size_t vertexCount () const;

private:
	unsigned int m_uiFVF;
	size_t m_uiVertexSize;
	size_t m_uiVertexCount;

	LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer;
	IDirect3DDevice9* m_pkDevice;
	Renderer& m_rkRenderer;
};
//---------------------------------------------------------------------------
#include "pg2_vertexbuffer.inl"
//---------------------------------------------------------------------------
} // end namespace
//---------------------------------------------------------------------------
#endif  // PG2_VERTEXBUFFER_H
//---------------------------------------------------------------------------
