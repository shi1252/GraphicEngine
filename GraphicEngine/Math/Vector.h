#pragma once
#include <math.h>

#define PI 3.141592f

struct Vector2
{
	float x;
	float y;

	Vector2(float x = 0, float y = 0) : x(x), y(y)
	{
	}
	const static Vector2 zero;
	const static Vector2 one;
	const static Vector2 right;
	const static Vector2 left;
	const static Vector2 up;
	const static Vector2 down;

	Vector2& operator+=(const Vector2 &v)
	{
		this->x += v.x;
		this->y += v.y;

		return *this;
	}
	Vector2& operator-=(const Vector2 &v)
	{
		this->x -= v.x;
		this->y -= v.y;

		return *this;
	}
	Vector2 operator+(const Vector2 &v) const
	{
		return Vector2(*this) += v;
	}
	Vector2 operator-(const Vector2 &v) const
	{
		return Vector2(*this) -= v;
	}
	friend Vector2 operator*(float v, const Vector2 &);
	Vector2 operator*(const float n) const
	{
		return Vector2(n*x, n*y);
	}
	Vector2 operator*(const Vector2 &v) const
	{
		return Vector2(x*v.x, y*v.y);
	}
	Vector2 operator/(const float n) const
	{
		return Vector2(x / n, y / n);
	}
	Vector2 operator/(const Vector2 &v) const
	{
		return Vector2(x / v.x, y / v.y);
	}
	bool operator==(const Vector2 &v) const
	{
		if (this->x == v.x && this->y == v.y)
			return true;
		return false;
	}
	bool operator!=(const Vector2 &v) const
	{
		return !(this->operator==(v));
	}
	float Dot(const Vector2 &v) const
	{
		return (this->x * v.x + this->y * v.y);
	}
	float Cross(const Vector2 &v) const
	{
		return (this->x*v.y - this->y*v.x);
	}
	float Distance() const
	{
		return sqrtf(x * x + y * y);
	}
	Vector2 Normalize()
	{
		return Vector2(x / this->Distance(), y / this->Distance());
	}
	float Cos(Vector2 &v)
	{
		return (Dot(v) / (Distance()*v.Distance()));
	}
	float AngleRad(Vector2 &v)
	{
		return acosf(this->Dot(v) / (this->Distance()*v.Distance()));
	}
	float AngleDeg(Vector2 &v) 
	{
		return AngleRad(v) * 180.0f / PI;
	}
	Vector2 Proj(Vector2 &v)
	{
		return (Distance() * Cos(v) * v.Normalize());
	}
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z)
	{
	}
	const static Vector3 zero;
	const static Vector3 one;
	const static Vector3 right;
	const static Vector3 left;
	const static Vector3 up;
	const static Vector3 down;
	const static Vector3 forward;
	const static Vector3 backward;

	Vector3& operator+=(const Vector3 &v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;

		return *this;
	}
	Vector3& operator-=(const Vector3 &v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;

		return *this;
	}
	Vector3 operator+(const Vector3 &v) const
	{
		return Vector3(*this) += v;
	}
	Vector3 operator-(const Vector3 &v) const
	{
		return Vector3(*this) -= v;
	}
	friend Vector3 operator*(float n, const Vector3 &v);
	Vector3 operator*(const float n) const
	{
		return Vector3(n*x, n*y, n*z);
	}
	Vector3 operator*(const Vector3 &v) const
	{
		return Vector3(x*v.x, y*v.y, z*v.z);
	}
	Vector3 operator/(const float n) const
	{
		return Vector3(x / n, y / n, z / n);
	}
	Vector3 operator/(const Vector3 &v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}
	bool operator==(const Vector3 &v) const
	{
		if (this->x == v.x && this->y == v.y && this->z == v.z)
			return true;
		return false;
	}
	bool operator!=(const Vector3 &v) const
	{
		return !(this->operator==(v));
	}
	float Dot(const Vector3 &v) const
	{
		return (this->x * v.x + this->y * v.y + this->z * v.z);
	}
	Vector3 Cross(const Vector3 &v) const
	{
		return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
	}
	float Distance()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector3 Normalize()
	{
		float d = Distance();
		return Vector3(x / d, y / d, z / d);
	}
	float Cos(Vector3 &v)
	{
		return (Dot(v) / (Distance() * v.Distance()));
	}
	float AngleRad(Vector3 &v)
	{
		return acosf(this->Dot(v) / this->Distance()*v.Distance());
	}
	float AngleDeg(Vector3 &v)
	{
		return AngleRad(v) * 180.0f / PI;
	}
	Vector3 Proj(Vector3 &v)
	{
		return (Distance() * Cos(v) * v.Normalize());
	}
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 1) : x(x), y(y), z(z), w(w)
	{
	}

	Vector4& operator+=(const Vector4 &v)
	{
		this->x += v.x;
		this->y += v.y;
		this->z += v.z;
		this->w += v.w;

		return *this;
	}
	Vector4& operator-=(const Vector4 &v)
	{
		this->x -= v.x;
		this->y -= v.y;
		this->z -= v.z;
		this->w -= v.w;

		return *this;
	}
	Vector4 operator+(const Vector4 &v) const
	{
		return Vector4(*this) += v;
	}
	Vector4 operator-(const Vector4 &v) const
	{
		return Vector4(*this) -= v;
	}
	friend Vector4 operator*(float n, const Vector4 &v);
	Vector4 operator*(const float n) const
	{
		return Vector4(n*x, n*y, n*z, n*w);
	}
	Vector4 operator*(const Vector4 &v) const
	{
		return Vector4(x*v.x, y*v.y, z*v.z, w*v.w);
	}
	Vector4 operator/(const float n) const
	{
		return Vector4(x / n, y / n, z / n, w / n);
	}
	Vector4 operator/(const Vector4 &v) const
	{
		return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
	}
	bool operator==(const Vector4 &v) const
	{
		if (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w)
			return true;
		return false;
	}
	bool operator!=(const Vector4 &v) const
	{
		return !(this->operator==(v));
	}
	float Dot3(const Vector4 &v) const
	{
		return (this->x * v.x + this->y * v.y + this->z * v.z);
	}
	Vector4 Cross3(const Vector4 &v) const
	{
		return Vector4(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
	}
	float Distance3()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector4 Normalize3()
	{
		float d = Distance3();
		return Vector4(x / d, y / d, z / d);
	}
	float Cos3(Vector4 &v)
	{
		return (Dot3(v) / (Distance3() * v.Distance3()));
	}
	float AngleRad3(Vector4 &v)
	{
		return acosf(this->Dot3(v) / this->Distance3()*v.Distance3());
	}
	float AngleDeg3(Vector4 &v)
	{
		return AngleRad3(v) * 180.0f / PI;
	}
	Vector4 Proj3(Vector4 &v)
	{
		return (Distance3() * Cos3(v) * v.Normalize3());
	}
};