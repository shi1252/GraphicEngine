#pragma once
#include "Vertex.h"
class BaseGeometry
{
public:
	Vertex *vertices = nullptr;
	int vertexCount = 0;
	int *indices = nullptr;
	int indexCount = 0;

	~BaseGeometry() { delete[] vertices; vertices = nullptr; delete[] indices; indices = nullptr; }
	void Draw() = 0;
};