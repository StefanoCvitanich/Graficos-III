#include "Camera.h"
#include "Utility.h"
//==================================================================================
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 
//==================================================================================
Camera::Camera(){

	_eye = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up = new D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_lookAt = new D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	_viewMatrix = new D3DXMATRIX();

	_frustum = new Frustum();
}
//==================================================================================
Camera::~Camera(){
	delete _eye;
	delete _right;
	delete _up;
	delete _lookAt;

	delete _viewMatrix;
}
//==================================================================================
void Camera::roll(float value){
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationAxis(&rotationMatrix, _lookAt, value);

	D3DXVec3TransformCoord(_right, _right, &rotationMatrix);
	D3DXVec3TransformCoord(_up, _up, &rotationMatrix);
}
//==================================================================================
void Camera::pitch(float value){
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationAxis(&rotationMatrix, _right, value);
	
	D3DXVec3TransformCoord(_up, _up, &rotationMatrix);
	D3DXVec3TransformCoord(_lookAt, _lookAt, &rotationMatrix);
}
//==================================================================================
void Camera::yaw(float value){
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationAxis(&rotationMatrix, _up, value);

	D3DXVec3TransformCoord(_right, _right, &rotationMatrix);
	D3DXVec3TransformCoord(_lookAt, _lookAt, &rotationMatrix);
}
//==================================================================================
void Camera::walk(float value){
	_eye->x += _lookAt->x * value;
	_eye->y += _lookAt->y * value;
	_eye->z += _lookAt->z * value;
}
//==================================================================================
void Camera::strafe(float value){
	_eye->x += _right->x * value;
	_eye->y += _right->y * value;
	_eye->z += _right->z * value;
}
//==================================================================================
void Camera::fly(float value){
	_eye->x += _up->x * value;
	_eye->y += _up->y * value;
	_eye->z += _up->z * value;
}
//==================================================================================
void Camera::setPos(float x, float y, float z){
	_eye->x = x;
	_eye->y = y;
	_eye->z = z;
}
//==================================================================================
void Camera::setForward(float x, float y, float z){
	_lookAt->x = x;
	_lookAt->y = y;
	_lookAt->z = z;
}
//==================================================================================
void Camera::update(Renderer& renderer){
	D3DXVec3Normalize(_lookAt, _lookAt);

	D3DXVec3Cross(_right, _up, _lookAt);
	D3DXVec3Normalize(_right, _right);

	D3DXVec3Cross(_up, _lookAt, _right);
	D3DXVec3Normalize(_up, _up);

	float x = -D3DXVec3Dot(_right, _eye);
	float y = -D3DXVec3Dot(_up, _eye);
	float z = -D3DXVec3Dot(_lookAt, _eye);

	(*_viewMatrix)(0, 0) = _right->x;
	(*_viewMatrix)(0, 1) = _up->x;
	(*_viewMatrix)(0, 2) = _lookAt->x;
	(*_viewMatrix)(0, 3) = 0.0f;

	(*_viewMatrix)(1, 0) = _right->y;
	(*_viewMatrix)(1, 1) = _up->y;
	(*_viewMatrix)(1, 2) = _lookAt->y;
	(*_viewMatrix)(1, 3) = 0.0f;

	(*_viewMatrix)(2, 0) = _right->z;
	(*_viewMatrix)(2, 1) = _up->z;
	(*_viewMatrix)(2, 2) = _lookAt->z;
	(*_viewMatrix)(2, 3) = 0.0f;

	(*_viewMatrix)(3, 0) = x;
	(*_viewMatrix)(3, 1) = y;
	(*_viewMatrix)(3, 2) = z;
	(*_viewMatrix)(3, 3) = 1.0f;

	renderer.setMatrix(VIEW, _viewMatrix);

	updateFrustum(renderer);
}
//==================================================================================
const Frustum& Camera::getFrustum() const{
	return *_frustum;
}
//==================================================================================
void Camera::updateFrustum(Renderer& renderer){
	_frustum->buildFrustum(_viewMatrix, renderer.getProjectionMatrix());
}
//==================================================================================