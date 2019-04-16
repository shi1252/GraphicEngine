#pragma once
#include "..\Math\Vertex.h"
#include "..\Draw\Draw.h"
#include "..\Buffer\BitmapBuffer.h"

class Transform;
class Matrix4x4;

class BaseGeometry
{
public:
	Transform *transform = nullptr;
	Vertex *vertices = nullptr;
	int vertexCount = 0;
	int *indices = nullptr;
	int indexCount = 0;

	~BaseGeometry() { delete transform; transform = nullptr; delete[] vertices; vertices = nullptr; delete[] indices; indices = nullptr; }
	void Draw(BitmapBuffer *bb, Matrix4x4 &worldViewProj);
};