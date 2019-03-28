#pragma once
#include <Windows.h>
struct Vector2;

void DrawDot(HDC hdc, Vector2 pos, COLORREF color)
{
	SetPixel(hdc, pos.x, pos.y, color);
}

void DrawLine(HDC hdc, Vector2 start, Vector2 end, COLORREF color)
{
	float y = start.y;
	float m = (end.y - start.y) / (end.x - start.x);

	for (int x = start.x; x <= end.x; x++)
	{
		SetPixel(hdc, x, y, color);
		y += m;
	}
}

void DrawTriangle(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{

}