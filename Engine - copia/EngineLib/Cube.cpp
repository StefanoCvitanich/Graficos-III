#include "Cube.h"


Cube::Cube()
{
	//front face
	_verts[0].x = -1.0f;	_verts[0].y = 1.0f;	_verts[0].z = -1.0f;	_verts[0].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[1].x = 1.0f;	_verts[1].y = 1.0f;	_verts[1].z = -1.0f;	_verts[1].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[2].x = -1.0f;	_verts[2].y = -1.0f;	_verts[2].z = -1.0f;	_verts[2].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[3].x = 1.0f;	_verts[3].y = -1.0f;	_verts[3].z = -1.0f;	_verts[3].color = D3DCOLOR_ARGB(255, 200, 200, 200);

	//right face
	_verts[1].x = 1.0f;	_verts[0].y = 1.0f;	_verts[0].z = -1.0f;	_verts[0].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[5].x = 1.0f;	_verts[5].y = 1.0f;	_verts[5].z = 1.0f;	_verts[5].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[3].x = 1.0f;	_verts[3].y = -1.0f;	_verts[3].z = -1.0f;	_verts[3].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[7].x = 1.0f;	_verts[7].y = -1.0f;	_verts[7].z = 1.0f;	_verts[7].color = D3DCOLOR_ARGB(255, 200, 200, 200);

	//top face
	_verts[4].x = -1.0f;	_verts[4].y = 1.0f;	_verts[4].z = 1.0f;	_verts[4].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[5].x = 1.0f;	_verts[5].y = 1.0f;	_verts[5].z = 1.0f;	_verts[5].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[0].x = -1.0f;	_verts[0].y = 1.0f;	_verts[0].z = -1.0f;	_verts[0].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[1].x = 1.0f;	_verts[1].y = 1.0f;	_verts[1].z = -1.0f;	_verts[1].color = D3DCOLOR_ARGB(255, 200, 200, 200);

	//back face
	_verts[5].x = 1.0f;	_verts[5].y = 1.0f;	_verts[5].z = 1.0f;	_verts[5].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[4].x = -1.0f;	_verts[4].y = 1.0f;	_verts[4].z = 1.0f;	_verts[4].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[7].x = 1.0f;	_verts[7].y = -1.0f;	_verts[7].z = 1.0f;	_verts[7].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[6].x = -1.0f;	_verts[6].y = -1.0f;	_verts[6].z = 1.0f;	_verts[6].color = D3DCOLOR_ARGB(255, 200, 200, 200);

	//left face
	_verts[4].x = -1.0f;	_verts[4].y = 1.0f;	_verts[4].z = 1.0f;	_verts[4].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[0].x = -1.0f;	_verts[0].y = 1.0f;	_verts[0].z = -1.0f;	_verts[0].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[6].x = -1.0f;	_verts[6].y = -1.0f;	_verts[6].z = 1.0f;	_verts[6].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[2].x = -1.0f;	_verts[2].y = -1.0f;	_verts[2].z = -1.0f;	_verts[2].color = D3DCOLOR_ARGB(255, 200, 200, 200);

	//bottom face
	_verts[2].x = -1.0f;	_verts[2].y = -1.0f;	_verts[2].z = -1.0f;	_verts[2].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[3].x = 1.0f;	_verts[3].y = -1.0f;	_verts[3].z = -1.0f;	_verts[3].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[6].x = -1.0f;	_verts[6].y = -1.0f;	_verts[6].z = 1.0f;	_verts[6].color = D3DCOLOR_ARGB(255, 200, 200, 200);
	_verts[7].x = 1.0f;	_verts[7].y = -1.0f;	_verts[7].z = 1.0f;	_verts[7].color = D3DCOLOR_ARGB(255, 200, 200, 200);
}


Cube::~Cube()
{
}

void Cube::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(NoTexture);
	rkRenderer.setMatrix(WORLD, _transformationMatrix);
	rkRenderer.draw(_verts, TRIANGLESTRIP, ARRAY_SIZE(_verts));
}
