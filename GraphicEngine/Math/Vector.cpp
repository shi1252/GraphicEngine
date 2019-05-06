#include "Vector.h"

//#ifndef _VECTOR__
//#define _VECTOR__
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

const Vector4 Vector4::zero(.0f, .0f, .0f);
const Vector4 Vector4::one(1.0f, 1.0f, 1.0f);
const Vector4 Vector4::right(1.0f, 0.0f, 0.0f);
const Vector4 Vector4::left(-1.0f, 0.0f, 0.0f);
const Vector4 Vector4::up(0.0f, 1.0f, 0.0f);
const Vector4 Vector4::down(0.0f, -1.0f, 0.0f);
const Vector4 Vector4::forward(0.0f, 0.0f, 1.0f);
const Vector4 Vector4::backward(0.0f, 0.0f, -1.0f);
//#endif

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

void Vector3::BarycentricCoordinate(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 p, Vector3 & out)
{
	Vector3 u = v2 - v1;
	Vector3 v = v3 - v1;
	Vector3 w = p - v1;

	float denom = (u.Dot(u) * v.Dot(v)) - (u.Dot(v) * v.Dot(u));
	out.y = (w.Dot(u) * v.Dot(v) - w.Dot(v) * v.Dot(u)) / denom;
	out.z = (w.Dot(v) * u.Dot(u) - w.Dot(u) * u.Dot(v)) / denom;
	out.x = 1 - out.y - out.z;
}