#include "Camera.h"
#include "..\Math\Matrix4x4.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

Matrix4x4 Camera::GetViewMatrix()
{
	return transform.GetInverseMatrix();
}