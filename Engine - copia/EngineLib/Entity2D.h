#ifndef ENTITY2D_H
#define ENTITY2D_H
//========================================================================================
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0]))) //dinamic array size
//========================================================================================
#include "Renderer.h"
//========================================================================================
enum CollisionResult2D
{
	CollisionVerticalUp,
	CollisionVerticalDown,
	CollisionHorizontalRight,
	CollisionHorizontalLeft,
	NoCollision
};
//========================================================================================
class Entity2D
{
public:
	DllExport Entity2D();
	DllExport ~Entity2D();
	DllExport void setPosX(float fPosX);
	DllExport void setPosY(float fPosY);
	DllExport void setRotation(float fRotation);
	DllExport void setScale(float fScaleX, float fScaleY);

	DllExport void flipNot();
	DllExport void Flip();

	DllExport CollisionResult2D checkCollision(Entity2D& toCheck);

	DllExport void returnToPreviusPos(float fPosX, float fPosY);
	DllExport void returnToPreviusPosH();
	DllExport void returnToPreviusPosV();

	DllExport float posX() const;
	DllExport float posY() const;

	DllExport float previusPosX() const;
	DllExport float previusPosY() const;

	DllExport float rotation() const;
	DllExport float scaleX() const;
	DllExport float scaleY() const;

protected:
	void updateLocalTransformation();
	float _posX;
	float _posY;
	float _previusPosX;
	float _previusPosY;
	float _rotation;
	float _scaleX;
	float _scaleY;
	bool _flip;

	Matrix _transformationMatrix;

};
//========================================================================================
#endif

