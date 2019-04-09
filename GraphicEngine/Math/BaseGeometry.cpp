#include "BaseGeometry.h"

void BaseGeometry::Draw(HDC hdc)
{
	if (indexCount % 3 > 0 || indexCount == 0)
		return;

	for (int i = 0; i < indexCount; i += 3)
	{
		DrawTriangleV2(hdc, vertices[indices[i]].position, vertices[indices[i+1]].position, vertices[indices[i + 2]].position, RGB(255, 0, 0));
	}
}