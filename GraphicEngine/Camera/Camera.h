#pragma once
#include "..\Math\Transform.h"

class Camera
{
public:
	Transform transform;

	float fieldOfView;
	float near_Plane;
	float far_Plane;

	Camera();
	~Camera();
};