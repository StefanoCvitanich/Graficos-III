#include "Entity2D.h"
//==================================================================================
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include <algorithm>
//==================================================================================
using namespace std;
//==================================================================================
Entity2D::Entity2D()
:
_transformationMatrix(new D3DXMATRIX()),
_posX(0),
_posY(0),
_previusPosX(0),
_previusPosY(0),
_rotation(0),
_scaleX(100.0f),
_scaleY(100.0f),
_flip(false)
{}
//==================================================================================
Entity2D::~Entity2D(){
}
//==================================================================================
void Entity2D::setPosX(float fPosX){
	_previusPosX = _posX;

	_posX = fPosX;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::setPosY(float fPosY){
	_previusPosY = _posY;

	_posY = fPosY;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::setRotation(float fRotation){
	_rotation = fRotation;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::setScale(float fScaleX, float fScaleY){
	_scaleX = fScaleX;
	_scaleY = fScaleY;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::flipNot(){
	_flip = false;
	if (!_flip && _scaleX < 0)
		_scaleX = -(_scaleX);
}
//==================================================================================
void Entity2D::Flip(){
	_flip = true;
	if (_flip && _scaleX > 0)
		_scaleX = -(_scaleX);
}
//==================================================================================
CollisionResult2D Entity2D::checkCollision(Entity2D& toCheck){
	float overlapX = max(0.0f,
		min(posX() + fabs(scaleX()) / 2.0f, toCheck.posX() + fabs(toCheck.scaleX()) / 2.0f) -
		max(posX() - fabs(scaleX()) / 2.0f, toCheck.posX() - fabs(toCheck.scaleX()) / 2.0f));

	float overlapY = max(0.0f,
		min(posY() + fabs(scaleY()) / 2.0f, toCheck.posY() + fabs(toCheck.scaleY()) / 2.0f) -
		max(posY() - fabs(scaleY()) / 2.0f, toCheck.posY() - fabs(toCheck.scaleY()) / 2.0f));

	if (overlapX != 0.0f && overlapY != 0.0f)
	{
		if (overlapX > overlapY)
		{
			if (posY() < 0 && posY() < toCheck.posY() || posY() > 0 && posY() < toCheck.posY()){
				return CollisionVerticalUp;
			}
			else if (posY() < 0 && posY() > toCheck.posY() || posY() > 0 && posY() > toCheck.posY()){
				return CollisionVerticalDown;
			}
		}
		else
		{
			if (posX() < 0 && posX() < toCheck.posX() || posX() > 0 && posX() < toCheck.posX())
				return CollisionHorizontalRight;
			else if (posX() < 0 && posX() > toCheck.posX() || posX() > 0 && posX() > toCheck.posX())
				return CollisionHorizontalLeft;
		}
	}
	return NoCollision;
}
//==================================================================================
void Entity2D::returnToPreviusPos(float fPosX, float fPosY){
	_posX = fPosX;
	_posY = fPosY;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::returnToPreviusPosH(){
	_posX = _previusPosX;

	updateLocalTransformation();
}
//==================================================================================
void Entity2D::returnToPreviusPosV(){
	_posY = _previusPosY;

	updateLocalTransformation();
}
//==================================================================================
float Entity2D::posX() const{
	return _posX;
}
//==================================================================================
float Entity2D::posY() const{
	return _posY;
}
//==================================================================================
float Entity2D::previusPosX() const{
	return _previusPosX;
}
//==================================================================================
float Entity2D::previusPosY() const{
	return _previusPosY;
}
//==================================================================================
float Entity2D::rotation() const{
	return _rotation;
}
//==================================================================================
float Entity2D::scaleX() const{
	return _scaleX;
}
//==================================================================================
float Entity2D::scaleY() const{
	return _scaleY;
}
//==================================================================================
void Entity2D::updateLocalTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, 0);

	D3DXMATRIX rotationMat;
	D3DXMatrixRotationZ(&rotationMat, _rotation);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, 1);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);
}
//==================================================================================