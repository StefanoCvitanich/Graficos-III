#include "Frustum.h"
//=============================================================================================
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 
//=============================================================================================
Frustum::Frustum(){
	for (size_t i = 0; i < 6; i++){
		_planes[i] = new D3DXPLANE();
	}
}
//=============================================================================================
Frustum::~Frustum(){
	for (size_t i = 0; i < 6; i++)
		delete _planes[i];
}
//=============================================================================================
void Frustum::buildFrustum(Matrix& viewMatrix, Matrix& projectionMatrix){
	D3DXMATRIX frustumMatrix;
	D3DXMatrixMultiply(&frustumMatrix, viewMatrix, projectionMatrix);

	// Left plane
	_planes[0]->a = frustumMatrix._14 + frustumMatrix._11;
	_planes[0]->b = frustumMatrix._24 + frustumMatrix._21;
	_planes[0]->c = frustumMatrix._34 + frustumMatrix._31;
	_planes[0]->d = frustumMatrix._44 + frustumMatrix._41;
	D3DXPlaneNormalize(_planes[0], _planes[0]);

	// Right plane
	_planes[1]->a = frustumMatrix._14 - frustumMatrix._11;
	_planes[1]->b = frustumMatrix._24 - frustumMatrix._21;
	_planes[1]->c = frustumMatrix._34 - frustumMatrix._31;
	_planes[1]->d = frustumMatrix._44 - frustumMatrix._41;
	D3DXPlaneNormalize(_planes[1], _planes[1]);

	// Top plane
	_planes[2]->a = frustumMatrix._14 - frustumMatrix._12;
	_planes[2]->b = frustumMatrix._24 - frustumMatrix._22;
	_planes[2]->c = frustumMatrix._34 - frustumMatrix._32;
	_planes[2]->d = frustumMatrix._44 - frustumMatrix._42;
	D3DXPlaneNormalize(_planes[2], _planes[2]);

	// Bottom plane
	_planes[3]->a = frustumMatrix._14 + frustumMatrix._12;
	_planes[3]->b = frustumMatrix._24 + frustumMatrix._22;
	_planes[3]->c = frustumMatrix._34 + frustumMatrix._32;
	_planes[3]->d = frustumMatrix._44 + frustumMatrix._42;
	D3DXPlaneNormalize(_planes[3], _planes[3]);

	// Near plane
	_planes[4]->a = frustumMatrix._13;
	_planes[4]->b = frustumMatrix._23;
	_planes[4]->c = frustumMatrix._33;
	_planes[4]->d = frustumMatrix._43;
	D3DXPlaneNormalize(_planes[4], _planes[4]);

	// Far plane
	_planes[5]->a = frustumMatrix._14 - frustumMatrix._13;
	_planes[5]->b = frustumMatrix._24 - frustumMatrix._23;
	_planes[5]->c = frustumMatrix._34 - frustumMatrix._33;
	_planes[5]->d = frustumMatrix._44 - frustumMatrix._43;
	D3DXPlaneNormalize(_planes[5], _planes[5]);
}
//=============================================================================================
bool Frustum::pointInFrustum(const Vector3& point) const{
	for (size_t i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(_planes[i], point) < 0)
			return false;
	}
	return true;
}
//=============================================================================================
CollisionResult Frustum::aabbVsFrustum(const AABB& aabb) const{
	int pointsInFrustrum = 0;

	for (size_t i = 0; i < 8; i++){
		if (pointInFrustum(aabb.points[i]))
			pointsInFrustrum++;
	}

	if (pointsInFrustrum == 0)	return AllOutside;
	else if (pointsInFrustrum > 0 && pointsInFrustrum < 8) return PartiallyInside;
	else if (pointsInFrustrum == 8) return AllInside;
}
//=============================================================================================