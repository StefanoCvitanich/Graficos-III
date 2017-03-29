#ifndef PHYSICS_H
#define PHYSICS_H
//===================================================================
#include "Entity2D.h"
//===================================================================
class Physics
{
public:
	DllExport static bool checkCollision(Entity2D& objA, Entity2D& objB);
};
//===================================================================
#endif

