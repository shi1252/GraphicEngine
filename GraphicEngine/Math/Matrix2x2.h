#pragma once
#include "Matrix3x3.h"
#include "Vector.h"
#include <math.h>

struct Matrix2x2
{
	float m00, m01, m10, m11;

	Matrix2x2(float m00, float m01, float m10, float m11)
		: m00(m00), m01(m01), m10(m10), m11(m11)
	{
	}
	Matrix2x2(Vector2 col1, Vector2 col2)
	{
		m00 = col1.x; m10 = col1.y; m01 = col2.x; m11 = col2.y;
	}

	const static Matrix2x2 identity;

	operator Matrix3x3() const
	{
		return Matrix3x3(m00, m01, 0, m10, m11, 0, 0, 0, 1);
	}
	operator Matrix4x4() const
	{
		return Matrix4x4(m00, m01, 0, 0, m10, m11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	}
	Matrix2x2 operator+(const Matrix2x2 &m)
	{
		return Matrix2x2(m00 + m.m00, m01 + m.m01, m10 + m.m10, m11 + m.m11);
	}
	Matrix2x2 operator-(const Matrix2x2 &m)
	{
		return Matrix2x2(m00 - m.m00, m01 - m.m01, m10 - m.m10, m11 - m.m11);
	}
	Matrix2x2 operator*(const Matrix2x2 &m)
	{
		return Matrix2x2(m00 * m.m00 + m01 * m.m10,
			m00 * m.m01 + m01 * m.m11,
			m10 * m.m00 + m11 * m.m10,
			m10 * m.m01 + m11 * m.m11);
	}
	Matrix3x3 operator*(const Matrix3x3 &m)
	{
		return Matrix3x3(
			m00 * m.m00 + m01 * m.m10,
			m00 * m.m01 + m01 * m.m11,
			m00 * m.m02 + m01 * m.m12,
			m10 * m.m00 + m11 * m.m10,
			m10 * m.m01 + m11 * m.m11,
			m10 * m.m02 + m11 * m.m12,
			m.m20,
			m.m21,
			m.m22
		);
	}
	Vector2& operator*(Vector2 &v)
	{
		Vector2 temp = v;
		temp.x = v.x * m00 + v.y * m01;
		temp.y = v.x * m10 + v.y * m11;
		v = temp;
		return v;
	}
};