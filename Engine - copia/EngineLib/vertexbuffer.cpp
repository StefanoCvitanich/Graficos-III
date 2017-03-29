#include "vertexbuffer.h"
using namespace pg1;
//===============================================================================================================
VertexBuffer::VertexBuffer (IDirect3DDevice9* pkDevice, size_t uiVertexSize, unsigned int uiFVF)
	:
	m_uiBase(0),
	m_uiVertexToLock(0),
	m_uiVertexSize(uiVertexSize),
	m_uiFVF(uiFVF),
	m_pkDevice(NULL)
{
	m_pkDevice = pkDevice;

	HRESULT hr = pkDevice->CreateVertexBuffer(
		SIZE * uiVertexSize,
		0,
		uiFVF,
		D3DPOOL_DEFAULT,
		&m_pkVertexBuffer,
		NULL
		);

	assert(hr == D3D_OK);
}
//===============================================================================================================
VertexBuffer::~VertexBuffer()
{
	if(m_pkVertexBuffer){
		m_pkVertexBuffer->Release();
		m_pkVertexBuffer = NULL;
	}
}
//===============================================================================================================
void VertexBuffer::draw (const void* pvVertices, D3DPRIMITIVETYPE ePrimitiveType, unsigned int uiVertexCount)
{
	m_ePrimitiveType = ePrimitiveType;

	if(FLUSH_COUNT < uiVertexCount){
		m_uiVertexToLock = FLUSH_COUNT;
	}
	else{
		m_uiVertexToLock = uiVertexCount;
	}
	
	if((m_uiBase + m_uiVertexToLock) > SIZE){
		m_uiBase = 0;
	}
	//--------------------------------------------------------------------
	void* pvDestination = NULL;

	HRESULT hr = m_pkVertexBuffer->Lock(
		m_uiBase * m_uiVertexSize,
		m_uiVertexToLock * m_uiVertexSize,
		(void**) (&pvDestination),
		m_uiBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
		);
	//--------------------------------------------------------------------
	unsigned int uiVtxProcNow = 0;

	while(m_uiVertexToLock > 0){
		memcpy(pvDestination, 
			(char*)pvVertices + (uiVtxProcNow * m_uiVertexSize), 
			m_uiVertexSize* m_uiVertexToLock
			);
		//--------------------------------------------------------------------
		uiVtxProcNow += m_uiVertexToLock;
		hr = m_pkVertexBuffer->Unlock();
		flush();

		m_uiBase += m_uiVertexToLock;
		//--------------------------------------------------------------------
		if(m_uiBase > (SIZE - 1)){
			m_uiBase = 0;
		}
		//--------------------------------------------------------------------
		if(FLUSH_COUNT < (uiVertexCount - uiVtxProcNow)){
			m_uiVertexToLock = FLUSH_COUNT;
		}
		else{
			m_uiVertexToLock = uiVertexCount - uiVtxProcNow;
		}
		//--------------------------------------------------------------------
		hr = m_pkVertexBuffer->Lock(
			m_uiBase * m_uiVertexSize, 
			m_uiVertexToLock * m_uiVertexSize, 
			(void **)(&pvDestination),
			m_uiBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD
			);
	}

	m_pkVertexBuffer->Unlock();

}
//===============================================================================================================
void VertexBuffer::flush ()
{
	int iPrimitiveCount = 0;

	if(m_ePrimitiveType == D3DPT_POINTLIST){
		iPrimitiveCount = m_uiVertexToLock;
	}
	//--------------------------------------------------------------------
	else if(m_ePrimitiveType == D3DPT_LINELIST){
		iPrimitiveCount = m_uiVertexToLock / 2;
	}
	//--------------------------------------------------------------------
	else if(m_ePrimitiveType == D3DPT_LINESTRIP){
		iPrimitiveCount = m_uiVertexToLock - 1;
	}
	//--------------------------------------------------------------------
	else if(m_ePrimitiveType == D3DPT_TRIANGLELIST){
		iPrimitiveCount = m_uiVertexToLock / 3;
	}
	//--------------------------------------------------------------------
	else if(m_ePrimitiveType == D3DPT_TRIANGLESTRIP){
		iPrimitiveCount = m_uiVertexToLock - 2;
	}
	//--------------------------------------------------------------------
	else if(m_ePrimitiveType == D3DPT_TRIANGLEFAN){
		iPrimitiveCount = m_uiVertexToLock - 2;
	}
	//--------------------------------------------------------------------
	HRESULT hr = m_pkDevice->DrawPrimitive(m_ePrimitiveType, m_uiBase, iPrimitiveCount);

	assert(hr == D3D_OK);
}
//===============================================================================================================
void VertexBuffer::bind ()
{
	HRESULT hr = m_pkDevice->SetVertexShader(NULL);
	hr = m_pkDevice->SetFVF(m_uiFVF);
	hr = m_pkDevice->SetStreamSource(0, m_pkVertexBuffer, NULL, m_uiVertexSize);
}
//===============================================================================================================