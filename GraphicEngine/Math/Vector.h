#pragma once
#include <math.h>
#include <stdio.h>
#include <vector>
#include "BaseMath.h"

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
	float Length() const
	{
		return sqrtf(x * x + y * y);
	}
	Vector2 Normalize()
	{
		return Vector2(x / this->Length(), y / this->Length());
	}
	float Cos(Vector2 &v)
	{
		return (Dot(v) / (Length()*v.Length()));
	}
	float AngleRad(Vector2 &v)
	{
		return acosf(this->Dot(v) / (this->Length()*v.Length()));
	}
	float AngleDeg(Vector2 &v) 
	{
		return AngleRad(v) * 180.0f / PI;
	}
	Vector2 Proj(Vector2 &v)
	{
		return (Length() * Cos(v) * v.Normalize());
	}
	static Vector2& MinX(Vector2 &v1, Vector2 &v2)
	{
		if (v1.x > v2.x)
			return v2;
		return v1;
	}
	static Vector2& MinX(Vector2 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector2 &min = v[0];
		for (int i = 1; i < length; i++)
		{
			if (min.x > v[i].x)
			{
				min = v[i];
			}
		}
		return min;
	}
	static int MinXIndex(Vector2 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector2 &min = v[0];
		int index = 0;
		for (int i = 1; i < length; i++)
		{
			if (min.x > v[i].x)
			{
				min = v[i];
				index = i;
			}
		}
		return index;
	}
	static int MinXIndex(std::vector<Vector2> list)
	{
		Vector2 &min = list[0];
		int index = 0;
		for (int i = 1; i < list.size(); i++)
		{
			if (min.x > list[i].x)
			{
				min = list[i];
				index = i;
			}
		}
		return index;
	}
	static Vector2& MinY(Vector2 &v1, Vector2 &v2)
	{
		if (v1.y > v2.y)
			return v2;
		return v1;
	}
	static Vector2& MinY(Vector2 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector2 &min = v[0];
		for (int i = 1; i < length; i++)
		{
			if (min.y > v[i].y)
			{
				min = v[i];
			}
		}
		return min;
	}
	static int MinYIndex(Vector2 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector2 &min = v[0];
		int index = 0;
		for (int i = 1; i < length; i++)
		{
			if (min.y > v[i].y)
			{
				min = v[i];
				index = i;
			}
		}
		return index;
	}
	static int MinYIndex(std::vector<Vector2> list)
	{
		Vector2 &min = list[0];
		int index = 0;
		for (int i = 1; i < list.size(); i++)
		{
			if (min.y > list[i].y)
			{
				min = list[i];
				index = i;
			}
		}
		return index;
	}
	static Vector2 Lerp(Vector2 &v1, Vector2 &v2, float ratio)
	{
		return Vector2(BaseMath::Lerp(v1.x, v2.x, ratio), BaseMath::Lerp(v1.y, v2.y, ratio));
	}
	static float Distance(Vector2 &v1, Vector2 &v2)
	{
		return sqrtf(powf(v2.x - v1.x, 2.0f) + powf(v2.y - v1.y, 2.0f));
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
	float Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector3 Normalize()
	{
		float d = Length();
		return Vector3(x / d, y / d, z / d);
	}
	float Cos(Vector3 &v)
	{
		return (Dot(v) / (Length() * v.Length()));
	}
	float AngleRad(Vector3 &v)
	{
		return acosf(this->Dot(v) / this->Length()*v.Length());
	}
	float AngleDeg(Vector3 &v)
	{
		return AngleRad(v) * 180.0f / PI;
	}
	Vector3 Proj(Vector3 &v)
	{
		return (Length() * Cos(v) * v.Normalize());
	}
	static Vector3& MinX(Vector3 &v1, Vector3 &v2)
	{
		if (v1.x > v2.x)
			return v2;
		return v1;
	}
	static Vector3& MinX(Vector3 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector3 &min = v[0];
		for (int i = 1; i < length; i++)
		{
			if (min.x > v[i].x)
			{
				min = v[i];
			}
		}
		return min;
	}
	static int MinXIndex(Vector3 *v, int length)
	{
		if (!v)
			throw "Trying to access null array";
		Vector3 &min = v[0];
		int index = 0;
		for (int i = 1; i < length; i++)
		{
			if (min.x > v[i].x)
			{
				min = v[i];
				index = i;
			}
		}
		return index;
	}
	static int MinXIndex(std::vector<Vector3> list)
	{
		Vector3 &min = list[0];
		int index = 0;
		for (int i = 1; i < list.size(); i++)
		{
			if (min.x > list[i].x)
			{
				min = list[i];
				index = i;
			}
		}
		return index;
	}
	static Vector3 Lerp(Vector3 &v1, Vector3 &v2, float ratio)
	{
		return Vector3(BaseMath::Lerp(v1.x, v2.x, ratio), BaseMath::Lerp(v1.y, v2.y, ratio), BaseMath::Lerp(v1.z, v2.z, ratio));
	}
	static float Distance(Vector3 &v1, Vector3 &v2)
	{
		return sqrtf(powf(v2.x - v1.x, 2.0f) + powf(v2.y - v1.y, 2.0f) + powf(v2.z - v1.z, 2.0f));
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
	float Length3()
	{
		return sqrtf(x * x + y * y + z * z);
	}
	Vector4 Normalize3()
	{
		float d = Length3();
		return Vector4(x / d, y / d, z / d);
	}
	float Cos3(Vector4 &v)
	{
		return (Dot3(v) / (Length3() * v.Length3()));
	}
	float AngleRad3(Vector4 &v)
	{
		return acosf(this->Dot3(v) / this->Length3()*v.Length3());
	}
	float AngleDeg3(Vector4 &v)
	{
		return AngleRad3(v) * 180.0f / PI;
	}
	Vector4 Proj3(Vector4 &v)
	{
		return (Length3() * Cos3(v) * v.Normalize3());
	}
};