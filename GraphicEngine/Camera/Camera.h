#pragma once
#include "..\Framework\HookVariable.h"
#include "..\Math\Transform.h"

class Matrix4x4;

class Camera
{
private:
	int width;
	int height;
	Matrix4x4 projectionMatrix;
public:
	Transform transform;

	HookVariable<float> fieldOfView;
	HookVariable<float> near_Plane;
	HookVariable<float> far_Plane;
	float focalLength;
	float aspect;

	Camera(int w, int h, float fov = 60.f, float n = 0.001f, float f = 1000.f);
	~Camera();

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
private:
	void SetProjectionMatrix();
};