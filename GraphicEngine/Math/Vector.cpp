#include "Vector.h"



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