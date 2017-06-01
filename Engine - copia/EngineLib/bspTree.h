#pragma once
#include "DLLExport.h"
#include "bspPlane.h"
#include "Mesh.h"
//========================================================================================
using namespace std;
//========================================================================================
class bspTree
{
public:
	DllExport bspTree();
	DllExport ~bspTree();

	DllExport void checkTree(D3DXVECTOR3 *camPos);
	DllExport void addPlaneToVector(bspPlane plane);
	DllExport void addMeshToVector(Mesh *mesh);

	vector <bspPlane> planesVector;
	vector <Mesh*> meshesVector;
};