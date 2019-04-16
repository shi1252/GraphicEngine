#include "BaseGeometry.h"
#include "..\Math\Transform.h"
#include "..\Math\Matrix4x4.h"

void BaseGeometry::Draw(BitmapBuffer *bb, Matrix4x4 &worldViewProj)
{
	if (indexCount % 3 > 0 || indexCount == 0) return;

	for (int i = 0; i < indexCount; i += 3)
	{
		DrawTriangleV2(bb, worldViewProj * transform->GetMatrix() * vertices[indices[i]], worldViewProj * transform->GetMatrix() * vertices[indices[i+1]], worldViewProj * transform->GetMatrix() * vertices[indices[i + 2]]);
	}
}