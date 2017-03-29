#ifndef FRUSTUM_H
#define FRUSTUM_H
//=============================================================================
#include "DLLExport.h"
#include "Renderer.h"
//=============================================================================
struct D3DXPLANE;
typedef D3DXPLANE* Plane;
//=============================================================================
class Frustum{
public:
	Frustum();
	~Frustum();

	void buildFrustum(Matrix& viewMatrix, Matrix& projectionMatrix);
	bool pointInFrustum(const Vector3& point) const;

	DllExport CollisionResult aabbVsFrustum(const AABB& aabb) const;

private:
	Plane _planes[6];
};
//=============================================================================
#endif
//=============================================================================