#ifndef TILE_H
#define TILE_H
//============================================
#include "Sprite.h"
//============================================
class Tile : public Sprite
{
public:
	DllExport Tile();
	DllExport ~Tile();
	
	DllExport bool isWalkable();
	DllExport void makeSolid(bool collidable);
	DllExport void setId(unsigned int id);
	DllExport unsigned int getId();

private:
	bool _collidable;
	unsigned int _id;
};
//============================================
#endif

