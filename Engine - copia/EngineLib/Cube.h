#ifndef CUBE_H
#define CUBE_H

#include "Entity2D.h"

#define DLLexport __declspec(dllexport)

class Cube : public Entity2D
{
public:
	DLLexport Cube();
	DLLexport ~Cube();

	DLLexport void draw(Renderer& rkRenderer);

	Vertex _verts[8];
};

#endif

