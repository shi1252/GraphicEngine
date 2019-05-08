#include "BaseGeometry.h"
#include "..\Math\Transform.h"
#include "..\Math\Matrix4x4.h"
#include "..\Framework\Image.h"
#include "..\Draw\Draw.h"

BaseGeometry::BaseGeometry(const BaseGeometry & copy)
{
	transform = new Transform(*copy.transform);
	vertices = new Vertex[copy.vertexCount];
	vertexCount = copy.vertexCount;
	memcpy(vertices, copy.vertices, sizeof(Vertex)*copy.vertexCount);
	//for (int i = 0; i < vertexCount; i++)
	//	vertices[i] = copy.vertices[i];
	indices = new int[copy.indexCount];
	indexCount = copy.indexCount;
	//for (int i=0;i<indexCount;i++)
	//	indices[i] = 
	memcpy(indices, copy.indices, sizeof(int)*copy.indexCount);
	texture = new Image(*copy.texture);
}

void BaseGeometry::Draw(BitmapBuffer *bb, Matrix4x4 &worldViewProj)
{
	if (indexCount % 3 > 0 || indexCount == 0) return;
	Matrix4x4 mat = worldViewProj * transform->GetMatrix();
	
	if (!texture)
	{
		for (int i = 0; i < indexCount; i += 3)
			DrawTriangleV2(bb, mat * vertices[indices[i]], mat * vertices[indices[i + 1]], mat * vertices[indices[i + 2]]);
	}
	else
	{
		for (int i = 0; i < indexCount; i += 3)
			DrawTriangleV2(bb, mat * vertices[indices[i]], mat * vertices[indices[i + 1]], mat * vertices[indices[i + 2]], texture);
	}
}