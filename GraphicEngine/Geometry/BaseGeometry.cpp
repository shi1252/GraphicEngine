#include "BaseGeometry.h"

void BaseGeometry::Draw(HDC hdc)
{
	if (indexCount % 3 > 0 || indexCount == 0)
		return;

	for (int i = 0; i < indexCount; i += 3)
	{
		DrawTriangleV2(hdc, vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i + 2]]);
	}
}