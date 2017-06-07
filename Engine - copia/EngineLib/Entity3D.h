#ifndef ENTITY3D_H
#define ENTITY3D_H
//========================================================================================
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0]))) //dinamic array size
//========================================================================================
#include "Renderer.h"
#include "Frustum.h"
#include <list>
//========================================================================================
class Nodo;
class BoundingBox;
class D3DXQUATERNION;

//========================================================================================
class Entity3D
{
public:
	DllExport Entity3D();
	DllExport ~Entity3D();
	DllExport void setPosX(float fPosX);
	DllExport void setPosY(float fPosY);
	DllExport void setPosZ(float fPosZ);
	DllExport void setRotation(float rotationX, float rotationY, float rotationZ, float rotationW);
	//DllExport void setRotation(D3DXQUATERNION rotationQuaternion);
	DllExport void setScale(float fScaleX, float fScaleY);
	DllExport void setScale(float fScaleX, float fScaleY, float scaleZ);

	DllExport void Flip(bool flipped);

	DllExport CollisionResult checkCollision(Entity3D& toCheck);

	DllExport void returnToPreviusPos(float fPosX, float fPosY);
	DllExport void returnToPreviusPosH();
	DllExport void returnToPreviusPosV();

	DllExport float posX() const;
	DllExport float posY() const;
	DllExport float posZ() const;

	DllExport float previusPosX() const;
	DllExport float previusPosY() const;

	DllExport float rotationX() const;
	DllExport float rotationY() const;
	DllExport float rotationZ() const;

	DllExport float scaleX() const;
	DllExport float scaleY() const;
	DllExport float scaleZ() const;

	DllExport void setName(std::string name);
	DllExport std::string getName() const;

	DllExport void setParent(Nodo* parent);
	DllExport const Matrix& worldMatrix() const;
	DllExport virtual void updateWorldTransformation();
	DllExport virtual void draw(Renderer& renderer, CollisionResult parentResult,
								const Frustum& frustum) = 0;

	DllExport const AABB& getAABB() const;
	DllExport virtual void updateBV() = 0;
	const Vector3* getPoints() const;
	DllExport virtual void getNames(std::vector<std::string>& names) = 0;
	DllExport virtual void updateNames(std::vector<std::string>& names, int& entityIndex) = 0;
	DllExport virtual Entity3D& findEntity(std::string name);

	bool canBeDrawn;

protected:
	void updateLocalTransformation();
	float _posX, _posY, _posZ;
	float _previusPosX, _previusPosY;
	std::string _name;
	bool _isDrawn;

	float _rotationX, _rotationY, _rotationZ, _rotationW;
	D3DXQUATERNION* _rotationQuaternion;

	float _scaleX, _scaleY, _scaleZ;

	AABB _aabb;
	
	BoundingBox* _boundingBox;

	Matrix _transformationMatrix;
	Matrix _worldTransformationMatrix;

	Nodo* _parent;
};
//========================================================================================
#endif

