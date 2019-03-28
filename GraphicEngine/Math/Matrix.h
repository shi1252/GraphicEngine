#pragma once
#include "Vector.h"

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
};

struct Matrix4x4
{
	float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

	Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
		: m00(m00), m01(m01), m02(m02), m03(m03),
		m10(m10), m11(m11), m12(m12), m13(m13),
		m20(m20), m21(m21), m22(m22), m23(m23),
		m30(m30), m31(m31), m32(m32), m33(m33)
	{
	}
	Matrix4x4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4)
	{
		m00 = col1.x; m10 = col1.y; m20 = col1.z; m30 = col1.w;
		m01 = col2.x; m11 = col2.y; m21 = col2.z; m31 = col2.w;
		m02 = col3.x; m12 = col3.y; m22 = col3.z; m32 = col3.w;
		m03 = col4.x; m13 = col4.y; m23 = col4.z; m33 = col4.w;
	}
};