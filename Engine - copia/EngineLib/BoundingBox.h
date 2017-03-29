#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "Entity3D.h"

class BoundingBox: public Entity3D
{
public:
	DllExport BoundingBox(Renderer& renderer);
	DllExport ~BoundingBox();

	DllExport void buildBox(const Vector3& minPoint, const Vector3& maxPoint);
	DllExport void draw(Renderer& renderer, CollisionResult parentResult,
						const Frustum& frustum);
	DllExport void updateBV();
private:
	Renderer& _renderer;
	Primitive _primitive;
	pg2::IndexBuffer* _indexBuffer;
	pg2::VertexBuffer* _vertexBuffer;
};

#endif

