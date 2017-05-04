#ifndef CAMERA_H
#define CAMERA_H
//==================================================================================
#include "Renderer.h"
#include "Frustum.h"
//==================================================================================
class Camera
{
public:
	DllExport Camera();
	DllExport ~Camera();

public:
	DllExport void roll(float value);
	DllExport void pitch(float value);
	DllExport void yaw(float value);

	DllExport void walk(float value);
	DllExport void strafe(float value);
	DllExport void fly(float value);

public:
	DllExport void setPos(float x, float y, float z);
	DllExport Vector3 getPos();
	DllExport void setForward(float x, float y, float z);

	DllExport void update(Renderer& renderer);

	DllExport void updateFrustum(Renderer& renderer);
	DllExport const Frustum& getFrustum() const;

	Vector3 cameraPosition;

private:
	Vector3 _eye;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _right;

	Matrix _viewMatrix;

	Frustum* _frustum;
};
//==================================================================================
#endif

