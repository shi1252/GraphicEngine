#pragma once
#include "Vector.h"
#include "Matrix4x4.h"

class Transform
{
public:
	Vector3 position = Vector3::zero;
	Vector3 rotation = Vector3::zero;
	Vector3 scale = Vector3::one;

	Transform();
	Transform(const Transform &t);
	~Transform();

	void Translate(Vector3 pos);
	void Translate(Vector3 dir, float distance);
	void Rotate(Vector3 rot);
	Matrix4x4 GetMatrix();
};