#ifndef QUAD_H
#define QUAD_H
//========================================================================================
#include "Entity2D.h"
//========================================================================================
class Quad: public Entity2D
{
public:
	DllExport Quad();
	DllExport ~Quad();
	DllExport void draw(Renderer& rkRenderer);

private:
	Vertex Vert[4];	
};
//========================================================================================
#endif