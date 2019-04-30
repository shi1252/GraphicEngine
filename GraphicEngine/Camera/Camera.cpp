#include "Camera.h"
#include "..\Math\BaseMath.h"
#include "..\Math\Matrix4x4.h"

Camera::Camera(int w, int h, float fov, float n, float f)
{
	width = w;
	height = h;
	aspect = w / (float)h;

	fieldOfView = fov;
	near_Plane = n;
	fieldOfView.SetHook(std::bind(&Camera::SetProjectionMatrix, this));
	near_Plane.SetHook(std::bind(&Camera::SetProjectionMatrix, this));
	far_Plane.SetHook(std::bind(&Camera::SetProjectionMatrix, this));
	far_Plane = f;
}

Camera::~Camera()
{
}

Matrix4x4 Camera::GetViewMatrix()
{
	return transform.GetInverseMatrix();
}

Matrix4x4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::SetProjectionMatrix()
{
	focalLength = tanf((fieldOfView * DegToRad) / 2.0f);

	projectionMatrix = Matrix4x4(
		focalLength / aspect, 0, 0, 0,
		0, focalLength, 0, 0,
		0, 0, (near_Plane + far_Plane) / (near_Plane - far_Plane), (2 * near_Plane * far_Plane) / (near_Plane - far_Plane),
		0, 0, -1, 0);
}