#pragma once
#include "..\Framework\HookVariable.h"
#include "Vector.h"
#include "Matrix4x4.h"

class Transform
{
private:
	Matrix4x4 matrix;
	Matrix4x4 invMatrix;
public:
	HookVariable<Vector3> position;
	HookVariable<Vector3> rotation;
	HookVariable<Vector3> scale;

	Transform();
	Transform(const Transform &t);
	~Transform();

	void Translate(Vector3 pos);
	void Translate(Vector3 dir, float distance);
	void Rotate(Vector3 rot);
	Matrix4x4 GetMatrix();
	Matrix4x4 GetInverseMatrix();
private:
	void ValueChanged();
};