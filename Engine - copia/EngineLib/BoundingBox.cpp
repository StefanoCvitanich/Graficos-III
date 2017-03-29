#include "BoundingBox.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

BoundingBox::BoundingBox(Renderer& renderer) :
_renderer(renderer)
{}

BoundingBox::~BoundingBox(){
	delete _vertexBuffer;
	_vertexBuffer = NULL;
	delete _indexBuffer;
	_indexBuffer = NULL;
}

void BoundingBox::buildBox(const Vector3& minPoint, const Vector3& maxPoint){
	Vertex vertices[8];
	vertices[0].x = -1.0f; vertices[0].y = 1.0f; vertices[0].z = -1.0f; vertices[0].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[1].x = 1.0f; vertices[1].y = 1.0f; vertices[1].z = -1.0f; vertices[1].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[2].x = -1.0f; vertices[2].y = -1.0f; vertices[2].z = -1.0f; vertices[2].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[3].x = 1.0f; vertices[3].y = -1.0f; vertices[3].z = -1.0f; vertices[3].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[4].x = -1.0f; vertices[4].y = 1.0f; vertices[4].z = 1.0f; vertices[4].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[5].x = 1.0f; vertices[5].y = 1.0f; vertices[5].z = 1.0f; vertices[5].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[6].x = -1.0f; vertices[6].y = -1.0f; vertices[6].z = 1.0f; vertices[6].color = D3DCOLOR_ARGB(155, 0, 255, 0);
	vertices[7].x = 1.0f; vertices[7].y = -1.0f; vertices[7].z = 1.0f; vertices[7].color = D3DCOLOR_ARGB(155, 0, 255, 0);

	unsigned short indices[] = {
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	_indexBuffer = _renderer.createIndexBuffer();
	_vertexBuffer = _renderer.createVertexBuffer(sizeof(Vertex), 1);

	_vertexBuffer->setVertexData(vertices, 8);
	_indexBuffer->setIndexData(indices, 36);

	_renderer.setCurrentIndexBuffer(_indexBuffer);
	_renderer.setCurrentVertexBuffer(_vertexBuffer);
}

void BoundingBox::draw(Renderer& renderer, CollisionResult parentResult,
					   const Frustum& frustum)
{
		_renderer.setMatrix(MatrixType::WORLD, _worldTransformationMatrix);

		_vertexBuffer->bind();
		_indexBuffer->bind();

		_renderer.drawCurrentBuffers(TRIANGLELIST);
}

void BoundingBox::updateBV(){}
