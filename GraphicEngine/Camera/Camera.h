#pragma once
#include "..\Math\Transform.h"

class Matrix4x4;

class Camera
{
public:
	Transform transform;

	float fieldOfView = 60.f;
	float near_Plane = 0.001f;
	float far_Plane = 1000.f;

	Camera();
	~Camera();

	Matrix4x4 GetViewMatrix();
};