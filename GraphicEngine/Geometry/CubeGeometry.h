#pragma once
#include "BaseGeometry.h"
#include "..\Draw\Draw.h"
#include "..\Math\Transform.h"

class CubeGeometry : public BaseGeometry
{
public:
	CubeGeometry(float width = 1, float height = 1, float depth = 1, DWORD color = 0)
	{
		transform = new Transform();

		width = width;
		height = height;
		depth = depth;

		vertices = new Vertex[24]
		{
			Matrix4x4::TranslateMatrix(Vector3(0, 0, -depth)) * Vertex(-width, -height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, -depth)) * Vertex(-width, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, -depth)) * Vertex(width, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, -depth)) * Vertex(width, -height, 0, color),

			Matrix4x4::TranslateMatrix(Vector3(0, 0, depth)) * Matrix4x4::YRotateMatrix(180) * Vertex(-width, -height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, depth)) * Matrix4x4::YRotateMatrix(180) * Vertex(-width, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, depth)) * Matrix4x4::YRotateMatrix(180) * Vertex(width, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, 0, depth)) * Matrix4x4::YRotateMatrix(180) * Vertex(width, -height, 0, color),
			
			Matrix4x4::TranslateMatrix(Vector3(-width, 0, 0)) * Matrix4x4::YRotateMatrix(90) * Vertex(-depth, -height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(-width, 0, 0)) * Matrix4x4::YRotateMatrix(90) * Vertex(-depth, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(-width, 0, 0)) * Matrix4x4::YRotateMatrix(90) * Vertex(depth, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(-width, 0, 0)) * Matrix4x4::YRotateMatrix(90) * Vertex(depth, -height, 0, color),

			Matrix4x4::TranslateMatrix(Vector3(width, 0, 0)) * Matrix4x4::YRotateMatrix(-90) * Vertex(-depth, -height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(width, 0, 0)) * Matrix4x4::YRotateMatrix(-90) * Vertex(-depth, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(width, 0, 0)) * Matrix4x4::YRotateMatrix(-90) * Vertex(depth, height, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(width, 0, 0)) * Matrix4x4::YRotateMatrix(-90) * Vertex(depth, -height, 0, color),

			Matrix4x4::TranslateMatrix(Vector3(0, -height, 0)) * Matrix4x4::XRotateMatrix(90) * Vertex(-width, -depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, -height, 0)) * Matrix4x4::XRotateMatrix(90) * Vertex(-width, depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, -height, 0)) * Matrix4x4::XRotateMatrix(90) * Vertex(width, depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, -height, 0)) * Matrix4x4::XRotateMatrix(90) * Vertex(width, -depth, 0, color),

			Matrix4x4::TranslateMatrix(Vector3(0, height, 0)) * Matrix4x4::XRotateMatrix(-90) * Vertex(-width, -depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, height, 0)) * Matrix4x4::XRotateMatrix(-90) * Vertex(-width, depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, height, 0)) * Matrix4x4::XRotateMatrix(-90) * Vertex(width, depth, 0, color),
			Matrix4x4::TranslateMatrix(Vector3(0, height, 0)) * Matrix4x4::XRotateMatrix(-90) * Vertex(width, -depth, 0, color)
		};
		vertexCount = 24;
		indices = new int[36]
		{
			0,1,2,
			0,2,3,

			4,5,6,
			4,6,7,

			8,9,10,
			8,10,11,

			12,13,14,
			12,14,15,

			16,17,18,
			16,18,19,

			20,21,22,
			20,22,23
		};
		indexCount = 36;
	}
};