#include "bspPlane.h"
#include <d3dx9math.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
//========================================================================================
bspPlane::bspPlane() {
	plane = new D3DXPLANE();
}
//========================================================================================
bspPlane::~bspPlane() {
	/*if (plane) {
		delete plane;
		plane = NULL;
		
	}*/
}
//========================================================================================
D3DXPLANE* bspPlane::createPlane(D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, D3DXVECTOR3 *p3) {

	D3DXPlaneFromPoints(plane, p1, p2, p3);

	D3DXPlaneNormalize(plane, plane);

	D3DXVECTOR3 normal;
	normal.x = plane->a;
	normal.y = plane->b;
	normal.z = plane->c;
	cout << "Normal: "<< normal.x << " " << normal.y << " " << normal.z << endl;

	return plane;
}
//========================================================================================