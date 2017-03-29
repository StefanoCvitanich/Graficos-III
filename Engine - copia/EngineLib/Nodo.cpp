#include "Nodo.h"
#include <algorithm>
#include <iostream>
#include <d3dx9.h>
//=====================================================================
using namespace std;
//=====================================================================
Nodo::Nodo(){}
//=====================================================================
Nodo::~Nodo(){
	if (!_childs.empty()){
		for (size_t i = 0; i < _childs.size(); i++)
			delete _childs[i];
	}
}
//=====================================================================
bool Nodo::addChild(Entity3D& child){
	_childs.push_back(&child);
	return true;
}
//=====================================================================
bool Nodo::removeChild(Entity3D& child){
	vector<Entity3D*>::iterator _remove;
	_remove = std::find(_childs.begin(), _childs.end(), &child);

	if (_remove != _childs.end()){
		_childs.erase(_remove);
		return true;
	}
	
	else return false;
}
//=====================================================================
void Nodo::updateWorldTransformation(){
	Entity3D::updateWorldTransformation();

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateWorldTransformation();
	}
}
//=====================================================================
void Nodo::draw(Renderer& renderer, CollisionResult parentResult,
	const Frustum& frustum){
	if (!_parent) updateWorldTransformation();

	if (parentResult == AllOutside){
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw(renderer, AllOutside, frustum);
			_isDrawn = false;
		}
	}
	else if (parentResult == PartiallyInside){
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw(renderer, frustum.aabbVsFrustum(_childs[i]->getAABB()), frustum);
			_isDrawn = true;
		}
	}

	else{
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw(renderer, AllInside, frustum);
			_isDrawn = true;
		}
	}
}
//=====================================================================
const vector<Entity3D*> Nodo::childs() const{
	return _childs;
}
//=====================================================================
void Nodo::updateBV(){
	float newMinPointX = FLT_MAX;
	float newMinPointY = FLT_MAX;
	float newMinPointZ = FLT_MAX;

	float newMaxPointX = FLT_MIN;
	float newMaxPointY = FLT_MIN;
	float newMaxPointZ = FLT_MIN;

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateBV();

		if (newMinPointX > _childs[i]->getAABB().min[0])
			newMinPointX = _childs[i]->getAABB().min[0];
		if (newMinPointY > _childs[i]->getAABB().min[1])
			newMinPointY = _childs[i]->getAABB().min[1];
		if (newMinPointZ > _childs[i]->getAABB().min[2])
			newMinPointZ = _childs[i]->getAABB().min[2];

		if (newMaxPointX < _childs[i]->getAABB().max[0])
			newMaxPointX = _childs[i]->getAABB().max[0];
		if (newMaxPointY < _childs[i]->getAABB().max[1])
			newMaxPointY = _childs[i]->getAABB().max[1];
		if (newMaxPointZ < _childs[i]->getAABB().max[2])
			newMaxPointZ = _childs[i]->getAABB().max[2];
	}
	_aabb.max[0] = newMaxPointX;	_aabb.max[1] = newMaxPointY;	_aabb.max[2] = newMaxPointZ;
	_aabb.min[0] = newMinPointX;	_aabb.min[1] = newMinPointY;	_aabb.min[2] = newMinPointZ;

	_aabb.points[0]->x = newMinPointX;	_aabb.points[0]->y = newMaxPointY;	_aabb.points[0]->z = newMinPointZ;
	_aabb.points[1]->x = newMaxPointX;	_aabb.points[1]->y = newMaxPointY;	_aabb.points[1]->z = newMinPointZ;
	_aabb.points[2]->x = newMinPointX;	_aabb.points[2]->y = newMinPointY;	_aabb.points[2]->z = newMinPointZ;
	_aabb.points[3]->x = newMaxPointX;	_aabb.points[3]->y = newMinPointY;	_aabb.points[3]->z = newMinPointZ;
	_aabb.points[4]->x = newMinPointX;	_aabb.points[4]->y = newMaxPointY;	_aabb.points[4]->z = newMaxPointZ;
	_aabb.points[5]->x = newMaxPointX;	_aabb.points[5]->y = newMaxPointY;	_aabb.points[5]->z = newMaxPointZ;
	_aabb.points[6]->x = newMinPointX;	_aabb.points[6]->y = newMinPointY;	_aabb.points[6]->z = newMaxPointZ;
	_aabb.points[7]->x = newMaxPointX;	_aabb.points[7]->y = newMinPointY;	_aabb.points[7]->z = newMaxPointZ;
}
//=====================================================================
void Nodo::getNames(vector<string>& names){
	names.push_back(getName());
	for (size_t i = 0; i < _childs.size(); i++)
	{
		_childs[i]->getNames(names);
	}
}
//=====================================================================
void Nodo::updateNames(std::vector<std::string>& names, int& entityIndex){
	names[entityIndex] = getName();

	for (size_t i = 0; i < _childs.size(); i++){
		entityIndex++;
		_childs[i]->updateNames(names, entityIndex);
	}
}
//=====================================================================
Entity3D& Nodo::findEntity(string name){
	for (size_t i = 0; i < _childs.size(); i++){
		if (_childs[i]->getName() == name)
			return *_childs[i];
	}
	//return _childs[i]->findEntity(name);
}
