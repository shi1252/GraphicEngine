//#pragma once
//#include "Matrix4x4.h"
//#include "Vector.h"
//#include <math.h>
//
//struct Matrix3x3
//{
//	float m00, m01, m02, m10, m11, m12, m20, m21, m22;
//
//	Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
//		: m00(m00), m01(m01), m02(m02), m10(m10), m11(m11), m12(m12), m20(m20), m21(m21), m22(m22)
//	{
//	}
//	Matrix3x3(Vector3 col1, Vector3 col2, Vector3 col3)
//	{
//		m00 = col1.x; m10 = col1.y; m20 = col1.z;
//		m01 = col2.x; m11 = col2.y; m21 = col2.z;
//		m02 = col3.x; m12 = col3.y; m22 = col3.z;
//	}
//
//	const static Matrix3x3 identity;
//
//	Matrix3x3 operator+(const Matrix3x3 &m)
//	{
//		return Matrix3x3(m00 + m.m00, m01 + m.m01, m02 + m.m02, m10 + m.m10, m11 + m.m11, m12 + m.m12, m20 + m.m20, m21 + m.m21, m22 + m.m22);
//	}
//	Matrix3x3 operator-(const Matrix3x3 &m)
//	{
//		return Matrix3x3(m00 - m.m00, m01 - m.m01, m02 - m.m02, m10 - m.m10, m11 - m.m11, m12 - m.m12, m20 - m.m20, m21 - m.m21, m22 - m.m22);
//	}
//	Matrix3x3 operator*(const Matrix3x3 &m)
//	{
//		return Matrix3x3(
//			m00 * m.m00 + m01 * m.m10 + m02 * m.m20,
//			m00 * m.m01 + m01 * m.m11 + m02 * m.m21,
//			m00 * m.m02 + m01 * m.m12 + m02 * m.m22,
//			m10 * m.m00 + m11 * m.m10 + m12 * m.m20,
//			m10 * m.m01 + m11 * m.m11 + m12 * m.m21,
//			m10 * m.m02 + m11 * m.m12 + m12 * m.m22,
//			m20 * m.m00 + m21 * m.m10 + m22 * m.m20,
//			m20 * m.m01 + m21 * m.m11 + m22 * m.m21,
//			m20 * m.m02 + m21 * m.m12 + m22 * m.m22
//		);
//	}
//	Matrix4x4 operator*(const Matrix4x4 &m)
//	{
//		return Matrix4x4(
//			m00 * m.m00 + m01 * m.m10 + m02 * m.m20,
//			m00 * m.m01 + m01 * m.m11 + m02 * m.m21,
//			m00 * m.m02 + m01 * m.m12 + m02 * m.m22,
//			m00 * m.m03 + m01 * m.m13 + m02 * m.m23,
//			m10 * m.m00 + m11 * m.m10 + m12 * m.m20,
//			m10 * m.m01 + m11 * m.m11 + m12 * m.m21,
//			m10 * m.m02 + m11 * m.m12 + m12 * m.m22,
//			m10 * m.m03 + m11 * m.m13 + m12 * m.m23,
//			m20 * m.m00 + m21 * m.m10 + m22 * m.m20,
//			m20 * m.m01 + m21 * m.m11 + m22 * m.m21,
//			m20 * m.m02 + m21 * m.m12 + m22 * m.m22,
//			m20 * m.m03 + m21 * m.m13 + m22 * m.m23,
//			m.m30,
//			m.m31,
//			m.m32,
//			m.m33
//		);
//	}
//	Vector3& operator*(Vector3 &v)
//	{
//		Vector3 temp = v;
//		temp.x = v.x * m00 + v.y * m01 + v.z * m02;
//		temp.y = v.x * m10 + v.y * m11 + v.z * m12;
//		temp.z = v.x * m20 + v.y * m21 + v.z * m22;
//		v = temp;
//		return v;
//	}
//};