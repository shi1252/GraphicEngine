#pragma once
class Camera
{
public:
	float fieldOfView;
	float near_Plane;
	float far_Plane;
	Camera();
	~Camera();
};