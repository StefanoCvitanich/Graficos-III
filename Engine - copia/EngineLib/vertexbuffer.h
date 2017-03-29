#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
//========================================================================================
#include <cassert>
//========================================================================================
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")
//========================================================================================
class Renderer;
//========================================================================================
#include "DLLExport.h"
namespace pg1{
	//========================================================================================
	class VertexBuffer{
	public:
		DllExport VertexBuffer(IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF);
		DllExport ~VertexBuffer();
		DllExport bool create();
		DllExport void bind();
		DllExport void flush();
		DllExport void draw(const void* pvVertices, D3DPRIMITIVETYPE ePrimitiveType, unsigned int uiVertexCount);
		DllExport void release();

	private:
		static const unsigned int SIZE = 400;
		static const unsigned int FLUSH_COUNT = 200;

		unsigned int m_uiBase;
		unsigned int m_uiVertexToLock;
		unsigned int m_uiVertexSize;
		unsigned int m_uiFVF;

		D3DPRIMITIVETYPE m_ePrimitiveType;
		LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer;
		IDirect3DDevice9 * m_pkDevice;
	};
}
//========================================================================================
#endif