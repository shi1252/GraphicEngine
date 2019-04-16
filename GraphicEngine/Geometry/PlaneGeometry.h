#pragma once
#include "BaseGeometry.h"
#include "..\Draw\Draw.h"
#include "..\Math\Transform.h"

class PlaneGeometry : public BaseGeometry
{
public:
	PlaneGeometry(float width = 1, float height = 1, DWORD color = 0)
	{
		transform = new Transform();

		vertices = new Vertex[4]
		{
			Vertex(-width, -height, 0, color),
			Vertex(-width, height, 0, color),
			Vertex(width, height, 0, color),
			Vertex(width, -height, 0, color)
		};
		vertexCount = 4;
		indices = new int[6]
		{
			0,1,2,
			0,2,3
		};
		indexCount = 6;
	}
};