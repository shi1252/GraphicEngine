#include "Vector.h"

const Vector2 Vector2::zero(.0f, .0f);
const Vector2 Vector2::one(1.0f, 1.0f);
const Vector2 Vector2::right(1.0f, 0.0f);
const Vector2 Vector2::left(-1.0f, 0.0f);
const Vector2 Vector2::up(0.0f, 1.0f);
const Vector2 Vector2::down(0.0f, -1.0f);

const Vector3 Vector3::zero(.0f, .0f, .0f);
const Vector3 Vector3::one(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::left(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::down(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::backward(0.0f, 0.0f, -1.0f);

Vector2 operator*(float n, const Vector2 & v)
{
	return Vector2(n*v.x, n*v.y);
}

Vector3 operator*(float n, const Vector3 &v)
{
	return Vector3(n*v.x, n*v.y, n*v.z);
}

Vector4 operator*(float n, const Vector4 & v)
{
	return Vector4(n*v.x, n*v.y, n*v.z, n*v.w);
}