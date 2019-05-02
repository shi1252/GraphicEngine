#include "BaseGeometry.h"
#include "..\Math\Transform.h"
#include "..\Math\Matrix4x4.h"

void BaseGeometry::Draw(BitmapBuffer *bb, Matrix4x4 &worldViewProj)
{
	if (indexCount % 3 > 0 || indexCount == 0) return;
	Matrix4x4 mat = worldViewProj * transform->GetMatrix();
	for (int i = 0; i < indexCount; i += 3)
	{
		DrawTriangleV2(bb, mat * vertices[indices[i]], mat * vertices[indices[i+1]], mat * vertices[indices[i + 2]]);
	}
}