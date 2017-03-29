#ifndef VECTOR2_H
#define VECTOR2_H
//========================================================================================
#include "DLLExport.h"
//========================================================================================
class Vector2
{
public:
	DllExport Vector2(float x, float y);
	DllExport ~Vector2();

public:
	DllExport float x();
	DllExport float y();

public:
	DllExport static Vector2 Normalize();
	DllExport float getMagnitud();
private:
	float _x, _y;
};
//========================================================================================
#endif

