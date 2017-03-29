#include "Quad.h"
//==================================================================================
Quad::Quad():
Entity2D()
{
	Vert[0].x = -0.5;	Vert[0].y = 0.5;	Vert[0].z = 0.0f;
	Vert[1].x = 0.5;	Vert[1].y = 0.5;	Vert[1].z = 0.0f;
	Vert[2].x = -0.5;	Vert[2].y = -0.5;	Vert[2].z = 0.0f;
	Vert[3].x = 0.5;	Vert[3].y = -0.5;	Vert[3].z = 0.0f;

	Vert[0].color = D3DCOLOR_ARGB(255, 255, 0, 0);
	Vert[1].color = D3DCOLOR_ARGB(255, 0, 255, 0);
	Vert[2].color = D3DCOLOR_ARGB(255, 0, 0, 255);
	Vert[3].color = D3DCOLOR_ARGB(255, 255, 255, 0);

	updateLocalTransformation();
}
//==================================================================================
Quad::~Quad(){
}
//==================================================================================
void Quad::draw(Renderer& rkRenderer){
	rkRenderer.setCurrentTexture(NoTexture);
	rkRenderer.setMatrix(WORLD, _transformationMatrix);
	rkRenderer.draw(Vert,TRIANGLESTRIP, ARRAY_SIZE(Vert));
}
//==================================================================================
