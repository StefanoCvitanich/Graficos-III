#include <iostream>
#include "bspTree.h"
#include <d3d9.h>
#include <d3dx9.h>
//========================================================================================
bspTree::bspTree() {
}
//=====================================================
bspTree::~bspTree() {
}
//=====================================================
void bspTree::checkTree(D3DXVECTOR3 *camPos) {

	for (int j = 0; j < meshesVector.size(); j++)
	{
		D3DXVECTOR3 *max = new D3DXVECTOR3(meshesVector[j]->getAABB().max[0], meshesVector[j]->getAABB().max[1], meshesVector[j]->getAABB().max[2]);
		D3DXVECTOR3 *min = new D3DXVECTOR3(meshesVector[j]->getAABB().min[0], meshesVector[j]->getAABB().min[1], meshesVector[j]->getAABB().min[2]);

		for (int i = 0; i < planesVector.size(); i++)
		{
			float meshMaxCheck = D3DXPlaneDotCoord(planesVector[i].plane, max);
			float meshMinCheck = D3DXPlaneDotCoord(planesVector[i].plane, min);
			float camCheck = D3DXPlaneDotCoord(planesVector[i].plane, camPos);

			if ((camCheck > 0 && meshMaxCheck > 0) || (camCheck < 0 && meshMaxCheck < 0) || (camCheck > 0 && meshMinCheck > 0) || (camCheck < 0 && meshMinCheck < 0) || camCheck == 0 || meshMaxCheck == 0 || meshMinCheck == 0)
			{
				meshesVector[j]->canBeDrawn = true;
			}
			else
			{
				meshesVector[j]->canBeDrawn = false;
				break;
			}
		}
	}
}
//=====================================================
void bspTree::addPlaneToVector(bspPlane plane) {

planesVector.push_back(plane);
}
//=====================================================
void bspTree::addMeshToVector(Mesh *mesh) {

meshesVector.push_back(mesh);
}
//=====================================================