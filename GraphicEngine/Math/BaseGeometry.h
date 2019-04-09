#pragma once
#include "Vertex.h"
#include "..\Draw\Draw.h"
#include "Transform.h"

class BaseGeometry
{
public:
	Transform transform;
	Vertex *vertices = nullptr;
	int vertexCount = 0;
	int *indices = nullptr;
	int indexCount = 0;

	~BaseGeometry() { delete[] vertices; vertices = nullptr; delete[] indices; indices = nullptr; }
	void Draw(HDC hdc);
};