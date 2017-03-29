#include "Tile.h"
//================================================
Tile::Tile(){
	_collidable = false;
	_id = 0;
}
//================================================
Tile::~Tile(){
}
//================================================
void Tile::makeSolid(bool collidable){
	_collidable = collidable;
}
//================================================
bool Tile::isWalkable(){
	if(_collidable) return false;

	else	return true;
}
//================================================
void Tile::setId(unsigned int id){
	_id = id;
}
//================================================
unsigned int Tile::getId(){
	return _id;
}
//================================================