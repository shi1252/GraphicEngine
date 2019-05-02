#pragma once
#include <Windows.h>
#include <vector>
#include "..\RenderSetting.h"
#include "..\Buffer\BitmapBuffer.h"
#include "..\Math\Vertex.h"
struct Vector2;

static void DrawDot(BitmapBuffer *bb, Vector2 pos, COLORREF color)
{
	bb->SetColor(pos.x, pos.y, color);
}

static void DrawLine(BitmapBuffer *bb, Vector2 start, Vector2 end, COLORREF color)
{
	bool isXLong = true;
	float dx = end.x - start.x;
	float dy = end.y - start.y;
	float absDx = fabsf(dx);
	float absDy = fabsf(dy);

	if (absDy > absDx)
		isXLong = false;

	if (isXLong)
	{
		float y = start.y;
		float m = (end.y - start.y) / (end.x - start.x);
		float xRatio = dx / absDx;

		for (int x = 0; x <= absDx; x++)
		{
			bb->SetColor(start.x + x * xRatio, y, color);
			y += m * xRatio;
		}
	}
	else
	{
		float x = start.x;
		float m = (end.x - start.x) / (end.y - start.y);
		float yRatio = dy / absDy;

		for (int y = 0; y <= absDy; y++)
		{
			bb->SetColor(x, start.y + y * yRatio, color);
			x += m * yRatio;
		}
	}
}

static void DrawTriangle(BitmapBuffer *bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{
	std::vector<Vector2> list;
	list.push_back(v1);
	list.push_back(v2);
	list.push_back(v3);

	int index = Vector2::MinXIndex(list);
	Vector2 minX = list[index];
	list.erase(list.begin() + index);
	index = Vector2::MinXIndex(list);
	Vector2 midX = list[index];
	list.erase(list.begin() + index);
	Vector2 maxX = list[0];
	list.clear();

	if (midX.x == maxX.x)
	{
		if (Vector2::Distance(minX, midX) < Vector2::Distance(minX, maxX))
		{
			Vector2 temp = maxX;
			maxX = midX;
			midX = temp;
		}
	}

	float m1 = (maxX.y - midX.y) / (maxX.x - midX.x);
	if ((maxX.x - midX.x) == 0)
		m1 = 0;
	float m2 = (maxX.y - minX.y) / (maxX.x - minX.x);

	float xRatio = (maxX.x - midX.x) / (maxX.x - minX.x);
	if ((maxX.x - minX.x) == 0)
	{
		m2 = 0;
		xRatio = 0;
	}
	if (xRatio < 1)
	{
		for (int dx = 0; dx <= fabsf(maxX.x - minX.x); dx++)
		{
			Vector2 start = Vector2(minX.x + dx, minX.y + m2 * dx);
			Vector2 end = Vector2(midX.x + dx * xRatio, midX.y + m1 * dx * xRatio);
			DrawLine(bb, start, end, color);
		}
	}
	else
	{
		for (int dx = 0; dx <= fabsf(maxX.x - midX.x); dx++)
		{
			Vector2 start = Vector2(midX.x + dx, midX.y + m1 * dx);
			Vector2 end = Vector2(minX.x + dx * xRatio, minX.y + m2 * dx * xRatio);
			DrawLine(bb, start, end, color);
		}
	}
}

static void DrawTriangleV2(BitmapBuffer *bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{
	std::vector<Vector2> list;
	list.push_back(v1);
	list.push_back(v2);
	list.push_back(v3);

	int index = Vector2::MinXIndex(list);
	Vector2 minX = list[index];
	list.erase(list.begin() + index);
	index = Vector2::MinXIndex(list);
	Vector2 midX = list[index];
	list.erase(list.begin() + index);
	Vector2 maxX = list[0];
	list.clear();

	list.push_back(v1);
	list.push_back(v2);
	list.push_back(v3);
	index = Vector2::MinYIndex(list);
	Vector2 minY = list[index];
	list.erase(list.begin() + index);
	index = Vector2::MinYIndex(list);
	Vector2 midY = list[index];
	list.erase(list.begin() + index);
	Vector2 maxY = list[0];
	list.clear();

	float m1 = (midX.y - minX.y) / (midX.x - minX.x);
	if ((midX.x - minX.x) == 0)
		m1 = 0;
	float m2 = (maxX.y - midX.y) / (maxX.x - midX.x);
	if ((maxX.x - midX.x) == 0)
		m2 = 0;
	float m3 = (maxX.y - minX.y) / (maxX.x - minX.x);
	if ((maxX.x - minX.x) == 0)
		m3 = 0;

	float y1 = midX.y - m1 * midX.x;
	float y2 = midX.y - m2 * midX.x;
	float y3 = minX.y - m3 * minX.x;

	for (int x = minX.x; x <= maxX.x; x++)
	{
		float f1 = 0;
		if (x < midX.x)
			f1 = m1 * x + y1;
		else
			f1 = m2 * x + y2;
		float f2 = m3 * x + y3;

		int startY = f1, endY = f2;
		int increase = 1;
		if (f1 > f2)
			increase = -1;

		while (startY != endY)
		{
			bb->SetColor(x, startY, color);
			startY += increase;
		}

		//for (int y = minY.y; y <= maxY.y; y++)
		//{
		//	if (midX.y >= maxX.y)
		//	{
		//		if (y >= f2 && y <= f1)
		//			SetPixel(hdc, x, y, color);
		//	}
		//	else
		//	{
		//		if (y <= f2 && y >= f1)
		//			SetPixel(hdc, x, y, color);
		//	}
		//}
	}
}

static void DrawTriangleV2(BitmapBuffer *bb, Vertex v1, Vertex v2, Vertex v3)
{
	v1.position = Vector4::NDCtoScreen(v1.position); //v1.position / v1.position.w;
	v2.position = Vector4::NDCtoScreen(v2.position); //v2.position / v2.position.w;
	v3.position = Vector4::NDCtoScreen(v3.position); //v3.position / v3.position.w;
	std::vector<Vector2> list;
	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);

	int index = Vector2::MinXIndex(list);
	Vector2 minX = list[index];
	list.erase(list.begin() + index);
	index = Vector2::MinXIndex(list);
	Vector2 midX = list[index];
	list.erase(list.begin() + index);
	Vector2 maxX = list[0];
	list.clear();

	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);
	index = Vector2::MinYIndex(list);
	Vector2 minY = list[index];
	list.erase(list.begin() + index);
	index = Vector2::MinYIndex(list);
	Vector2 midY = list[index];
	list.erase(list.begin() + index);
	Vector2 maxY = list[0];
	list.clear();

	float m1 = (midX.y - minX.y) / (midX.x - minX.x);
	if ((midX.x - minX.x) == 0)
		m1 = 0;
	float m2 = (maxX.y - midX.y) / (maxX.x - midX.x);
	if ((maxX.x - midX.x) == 0)
		m2 = 0;
	float m3 = (maxX.y - minX.y) / (maxX.x - minX.x);
	if ((maxX.x - minX.x) == 0)
		m3 = 0;

	float y1 = midX.y - m1 * midX.x;
	float y2 = midX.y - m2 * midX.x;
	float y3 = minX.y - m3 * minX.x;

	for (int x = minX.x; x <= maxX.x; x++)
	{
		float f1 = 0;
		if (x < midX.x)
			f1 = m1 * x + y1;
		else
			f1 = m2 * x + y2;
		float f2 = m3 * x + y3;

		int startY = BaseMath::Clamp(f1, minY.y, maxY.y), endY = BaseMath::Clamp(f2, minY.y, maxY.y);
		int increase = 1;
		if (f1 > f2)
			increase = -1;

		while (startY != endY)
		{
			bb->SetColor(x, startY, Vertex::InterpColor(v1, v2, v3, Vector3(x, startY)));
			startY += increase;
		}
	}
}

static void DrawTriangleByCross(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{

}

static void DrawTriangleByCom(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{

}