#pragma once
#include "Vector.h"
class Transform
{
public:
	Vector3 position = Vector3::zero;
	Vector3 rotation = Vector3::zero;
	Vector3 scale = Vector3::zero;

	Transform();
	~Transform();

	void Translate(Vector3 pos);
	void Translate(Vector3 dir, float distance);
	void Rotate(Vector3 rot);
};