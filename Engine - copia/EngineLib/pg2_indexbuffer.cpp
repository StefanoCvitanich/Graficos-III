
//---------------------------------------------------------------------------
#include "pg2_indexbuffer.h"
//---------------------------------------------------------------------------
using namespace pg2;
//---------------------------------------------------------------------------
#include "Renderer.h"
//---------------------------------------------------------------------------
IndexBuffer::IndexBuffer (Renderer& rkRenderer, IDirect3DDevice9* pkDevice)
:
m_uiIndexCount(0),
m_IndexBuffer(NULL),
m_pkDevice(pkDevice),
m_rkRenderer(rkRenderer)
{
	// nothing to do
}
//---------------------------------------------------------------------------
IndexBuffer::~IndexBuffer ()
{
	if(m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = NULL;
	}
}
//---------------------------------------------------------------------------
void IndexBuffer::setIndexData (const unsigned short* pausIndices, size_t uiIndexCount)
{
	// release if previously created
	if(m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = NULL;
	}

	// create vertex buffer
	HRESULT hr = m_pkDevice->CreateIndexBuffer(
												uiIndexCount * sizeof(unsigned short),
												D3DUSAGE_WRITEONLY,
												D3DFMT_INDEX16,
												D3DPOOL_MANAGED,
												&m_IndexBuffer,
												NULL
	);

	assert(hr == D3D_OK);

	// copy index data
	void* pvIndices;

	m_IndexBuffer->Lock(0, uiIndexCount * sizeof(unsigned short), &pvIndices, 0);
	memcpy(pvIndices, pausIndices, sizeof(unsigned short) * uiIndexCount);
	m_IndexBuffer->Unlock();

	// update internal state
	m_uiIndexCount = uiIndexCount;
}
//---------------------------------------------------------------------------
void IndexBuffer::bind ()
{
	HRESULT hr = m_pkDevice->SetIndices(m_IndexBuffer);
	assert(hr == D3D_OK);

	m_rkRenderer.setCurrentIndexBuffer(this);
}
//---------------------------------------------------------------------------