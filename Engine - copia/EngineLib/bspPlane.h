#pragma once
#include "DLLExport.h"
//========================================================================================
class D3DXPLANE;
class D3DXVECTOR3;
//========================================================================================
using namespace std;
//========================================================================================
class bspPlane
{
public:
	DllExport bspPlane();
	DllExport ~bspPlane();

	DllExport D3DXPLANE* createPlane(D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *p3);

	D3DXPLANE* plane;
};
//========================================================================================