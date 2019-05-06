#pragma once
#include "..\Math\Vertex.h"
#include "..\Draw\Draw.h"
#include "..\Buffer\BitmapBuffer.h"

class Transform;
class Matrix4x4;
class Image;

class BaseGeometry
{
public:
	Transform *transform = nullptr;
	Vertex *vertices = nullptr;
	int vertexCount = 0;
	int *indices = nullptr;
	int indexCount = 0;
	Image *texture = nullptr;

	BaseGeometry() {};
	BaseGeometry(const BaseGeometry &copy);
	~BaseGeometry() { delete transform; transform = nullptr; delete[] vertices; vertices = nullptr; delete[] indices; indices = nullptr; delete texture; texture = nullptr; }
	void Draw(BitmapBuffer *bb, Matrix4x4 &worldViewProj);
};