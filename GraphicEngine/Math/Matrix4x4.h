#pragma once
#include "Vector.h"
#include "..\Geometry\BaseGeometry.h"
#include "Matrix3x3.h"
#include <math.h>

struct Matrix4x4
{
	float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

	Matrix4x4()
		:m00(1.f), m01(0.f), m02(0.f), m03(0.f),
		m10(0.f), m11(1.f), m12(0.f), m13(0.f),
		m20(0.f), m21(0.f), m22(1.f), m23(0.f),
		m30(0.f), m31(0.f), m32(0.f), m33(1.f)
	{}
	Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
		: m00(m00), m01(m01), m02(m02), m03(m03),
		m10(m10), m11(m11), m12(m12), m13(m13),
		m20(m20), m21(m21), m22(m22), m23(m23),
		m30(m30), m31(m31), m32(m32), m33(m33)
	{}
	Matrix4x4(Vector4 col1, Vector4 col2, Vector4 col3, Vector4 col4)
	{
		m00 = col1.x; m10 = col1.y; m20 = col1.z; m30 = col1.w;
		m01 = col2.x; m11 = col2.y; m21 = col2.z; m31 = col2.w;
		m02 = col3.x; m12 = col3.y; m22 = col3.z; m32 = col3.w;
		m03 = col4.x; m13 = col4.y; m23 = col4.z; m33 = col4.w;
	}

	const static Matrix4x4 identity;

	Matrix4x4 operator+(const Matrix4x4 &m)
	{
		return Matrix4x4(
			m00 + m.m00, m01 + m.m01, m02 + m.m02, m03 + m.m03,
			m10 + m.m10, m11 + m.m11, m12 + m.m12, m13 + m.m13,
			m20 + m.m20, m21 + m.m21, m22 + m.m22, m23 + m.m23,
			m30 + m.m30, m31 + m.m31, m32 + m.m32, m33 + m.m33);
	}
	Matrix4x4 operator-(const Matrix4x4 &m)
	{
		return Matrix4x4(
			m00 - m.m00, m01 - m.m01, m02 - m.m02, m03 - m.m03,
			m10 - m.m10, m11 - m.m11, m12 - m.m12, m13 - m.m13,
			m20 - m.m20, m21 - m.m21, m22 - m.m22, m23 - m.m23,
			m30 - m.m30, m31 - m.m31, m32 - m.m32, m33 - m.m33);
	}
	Matrix4x4 operator*(const Matrix4x4 &m)
	{
		return Matrix4x4(
			m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30,
			m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31,
			m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32,
			m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33,
			m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30,
			m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31,
			m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32,
			m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33,
			m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30,
			m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31,
			m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32,
			m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33,
			m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30,
			m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31,
			m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32,
			m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33
		);
	}
	//Matrix4x4 operator*(const Matrix3x3 &m)
	//{
	//	return Matrix4x4(
	//		m00 * m.m00 + m01 * m.m10 + m02 * m.m20,
	//		m00 * m.m01 + m01 * m.m11 + m02 * m.m21,
	//		m00 * m.m02 + m01 * m.m12 + m02 * m.m22,
	//		m03,
	//		m10 * m.m00 + m11 * m.m10 + m12 * m.m20,
	//		m10 * m.m01 + m11 * m.m11 + m12 * m.m21,
	//		m10 * m.m02 + m11 * m.m12 + m12 * m.m22,
	//		m13,
	//		m20 * m.m00 + m21 * m.m10 + m22 * m.m20,
	//		m20 * m.m01 + m21 * m.m11 + m22 * m.m21,
	//		m20 * m.m02 + m21 * m.m12 + m22 * m.m22,
	//		m23,
	//		m30 * m.m00 + m31 * m.m10 + m32 * m.m20,
	//		m30 * m.m01 + m31 * m.m11 + m32 * m.m21,
	//		m30 * m.m02 + m31 * m.m12 + m32 * m.m22,
	//		m33
	//	);
	//}
	Vector3 operator*(Vector3 &v)
	{
		Vector3 temp = v;
		temp.x = v.x * m00 + v.y * m01 + v.z * m02 + 1 * m03;
		temp.y = v.x * m10 + v.y * m11 + v.z * m12 + 1 * m13;
		temp.z = v.x * m20 + v.y * m21 + v.z * m22 + 1 * m23;
		return temp;
		v = temp;
		return v;
	}
	Vector4 operator*(Vector4 &v)
	{
		Vector4 temp = v;
		temp.x = v.x * m00 + v.y * m01 + v.z * m02 + v.w * m03;
		temp.y = v.x * m10 + v.y * m11 + v.z * m12 + v.w * m13;
		temp.z = v.x * m20 + v.y * m21 + v.z * m22 + v.w * m23;
		temp.w = v.x * m30 + v.y * m31 + v.z * m32 + v.w * m33;
		return temp;
		v = temp;
		return v;
	}
	Vertex operator*(Vertex v)
	{
		Vector4 temp = (*this) * v.position;
		return Vertex(temp, v.uv, v.color);
	}
	float& operator()(int r, int c)
	{
		switch (r)
		{
		case 0:
			switch (c)
			{
			case 0:
				return m00;
			case 1:
				return m01;
			case 2:
				return m02;
			case 3:
				return m03;
			}
			break;	
		case 1:
			switch (c)
			{
			case 0:
				return m10;
			case 1:
				return m11;
			case 2:
				return m12;
			case 3:
				return m13;
			}
			break;
		case 2:
			switch (c)
			{
			case 0:
				return m20;
			case 1:
				return m21;
			case 2:
				return m22;
			case 3:
				return m23;
			}
			break;
		case 3:
			switch (c)
			{
			case 0:
				return m30;
			case 1:
				return m31;
			case 2:
				return m32;
			case 3:
				return m33;
			}
			break;
		}
	}
	static Matrix4x4 TransposeMatrix(const Matrix4x4 &m)
	{
		return Matrix4x4(
			m.m00, m.m10, m.m20, m.m30,
			m.m01, m.m11, m.m21, m.m31,
			m.m02, m.m12, m.m22, m.m32,
			m.m03, m.m13, m.m23, m.m33);
	}
	static Matrix4x4 TranslateMatrix(float x, float y, float z)
	{
		return Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(x, y, z, 1));
	}
	static Matrix4x4 TranslateMatrix(Vector3 v)
	{
		return Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(v.x, v.y, v.z, 1));
	}
	static Matrix4x4 InverseTranslateMatrix(float x, float y, float z)
	{
		return Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(-x, -y, -z, 1));
	}
	static Matrix4x4 InverseTranslateMatrix(Vector3 v)
	{
		return Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(-v.x, -v.y, -v.z, 1));
	}
	static Matrix4x4 XRotateMatrix(float degree)
	{
		return Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, cosf(degree * DegToRad), sinf(degree * DegToRad), 0), Vector4(0, -sinf(degree * DegToRad), cos(degree * DegToRad), 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 YRotateMatrix(float degree)
	{
		return Matrix4x4(Vector4(cosf(degree * DegToRad), 0, -sinf(degree * DegToRad), 0), Vector4(0, 1, 0, 0), Vector4(sinf(degree * DegToRad), 0, cos(degree * DegToRad), 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 ZRotateMatrix(float degree)
	{
		return Matrix4x4(Vector4(cosf(degree * DegToRad), sinf(degree * DegToRad), 0, 0), Vector4(-sinf(degree * DegToRad), cos(degree * DegToRad), 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 InverseXRotateMatrix(float degree)
	{
		return TransposeMatrix(Matrix4x4(Vector4(1, 0, 0, 0), Vector4(0, cosf(degree * DegToRad), sinf(degree * DegToRad), 0), Vector4(0, -sinf(degree * DegToRad), cos(degree * DegToRad), 0), Vector4(0, 0, 0, 1)));
	}
	static Matrix4x4 InverseYRotateMatrix(float degree)
	{
		return TransposeMatrix(Matrix4x4(Vector4(cosf(degree * DegToRad), 0, -sinf(degree * DegToRad), 0), Vector4(0, 1, 0, 0), Vector4(sinf(degree * DegToRad), 0, cos(degree * DegToRad), 0), Vector4(0, 0, 0, 1)));
	}
	static Matrix4x4 InverseZRotateMatrix(float degree)
	{
		return TransposeMatrix(Matrix4x4(Vector4(cosf(degree * DegToRad), sinf(degree * DegToRad), 0, 0), Vector4(-sinf(degree * DegToRad), cos(degree * DegToRad), 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1)));
	}
	static Matrix4x4 YXZRotateMatrix(Vector3 rotation)
	{
		return  YRotateMatrix(rotation.y) * XRotateMatrix(rotation.x) * ZRotateMatrix(rotation.z);
	}
	static Matrix4x4 InverseYXZRotateMatrix(Vector3 rotation)
	{
		return  InverseZRotateMatrix(rotation.z) * InverseXRotateMatrix(rotation.x) * InverseYRotateMatrix(rotation.y);
	}
	static Matrix4x4 ScaleMatrix(float scale)
	{
		return Matrix4x4(Vector4(scale, 0, 0, 0), Vector4(0, scale, 0, 0), Vector4(0, 0, scale, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 ScaleMatrix(float x, float y, float z)
	{
		return Matrix4x4(Vector4(x, 0, 0, 0), Vector4(0, y, 0, 0), Vector4(0, 0, z, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 ScaleMatrix(Vector3 v)
	{
		return Matrix4x4(Vector4(v.x, 0, 0, 0), Vector4(0, v.y, 0, 0), Vector4(0, 0, v.z, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 InverseScaleMatrix(float scale)
	{
		return Matrix4x4(Vector4(1.f/scale, 0, 0, 0), Vector4(0, 1.f/scale, 0, 0), Vector4(0, 0, 1.f/scale, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 InverseScaleMatrix(float x, float y, float z)
	{
		return Matrix4x4(Vector4(1.f/x, 0, 0, 0), Vector4(0, 1.f/y, 0, 0), Vector4(0, 0, 1.f/z, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 InverseScaleMatrix(Vector3 v)
	{
		return Matrix4x4(Vector4(1.f/v.x, 0, 0, 0), Vector4(0, 1.f/v.y, 0, 0), Vector4(0, 0, 1.f/v.z, 0), Vector4(0, 0, 0, 1));
	}
	static Matrix4x4 TRSMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
	{
		return  TranslateMatrix(position) * YXZRotateMatrix(rotation) * ScaleMatrix(scale);
	}
	static Matrix4x4 InverseTRSMatrix(Vector3 position, Vector3 rotation, Vector3 scale)
	{
		return  InverseScaleMatrix(scale) * InverseYXZRotateMatrix(rotation) * InverseTranslateMatrix(position);
	}
};