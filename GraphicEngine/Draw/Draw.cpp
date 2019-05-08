#include "Draw.h"
#include "..\RenderSetting.h"
#include "..\Buffer\BitmapBuffer.h"
#include "..\Math\Vertex.h"
#include "..\Framework\Image.h"
#include "..\Camera\Camera.h"

extern Camera *mainCam;

Vector4 NDCtoScreen(Vector4 v)
{
	Vector4 temp = ((v / fabs(v.w)) + 1.f) / 2.f;
	temp = Vector4(roundf(temp.x * WIN_WIDTH), roundf(temp.y * WIN_HEIGHT), temp.z, v.w);
	return temp;
}

void DrawDot(BitmapBuffer * bb, Vector2 pos, COLORREF color)
{
	bb->SetColor(pos.x, pos.y, color);
}

void DrawLine(BitmapBuffer * bb, Vector2 start, Vector2 end, COLORREF color)
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

void DrawTriangle(BitmapBuffer * bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
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

void DrawTriangleV2(BitmapBuffer * bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
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

void DrawTriangleV2(BitmapBuffer * bb, Vertex v1, Vertex v2, Vertex v3)
{
	Vector3 bc1 = v2.position - v1.position;
	Vector3 bc2 = v3.position - v1.position;
	if (bc1.Cross(bc2).Dot(Vector3::forward) > 0) return;
	v1.position = NDCtoScreen(v1.position); //v1.position / v1.position.w;
	v2.position = NDCtoScreen(v2.position); //v2.position / v2.position.w;
	v3.position = NDCtoScreen(v3.position); //v3.position / v3.position.w;
	std::vector<Vector4> list;
	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);

	int index = Vector4::MinXIndex(list);
	Vector4 minX = list[index];
	list.erase(list.begin() + index);
	index = Vector4::MinXIndex(list);
	Vector4 midX = list[index];
	list.erase(list.begin() + index);
	Vector4 maxX = list[0];
	list.clear();

	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);
	index = Vector4::MinYIndex(list);
	Vector4 minY = list[index];
	list.erase(list.begin() + index);
	index = Vector4::MinYIndex(list);
	Vector4 midY = list[index];
	list.erase(list.begin() + index);
	Vector4 maxY = list[0];
	list.clear();

	Vector4 m1 = (midX - minX) / (midX.x - minX.x);
	if ((midX.x - minX.x) == 0)
		m1 = 0;
	Vector4 m2 = (maxX - midX) / (maxX.x - midX.x);
	if ((maxX.x - midX.x) == 0)
		m2 = 0;
	Vector4 m3 = (maxX - minX) / (maxX.x - minX.x);
	if ((maxX.x - minX.x) == 0)
		m3 = 0;

	Vector4 y1 = midX - m1 * midX.x;
	Vector4 y2 = midX - m2 * midX.x;
	Vector4 y3 = minX - m3 * minX.x;

	int countX = 0;
	for (int x = minX.x; x <= maxX.x; x++)
	{
		float f1 = 0;
		float w1 = 0;
		float z1 = 0;
		if (x < midX.x)
		{
			f1 = m1.y * x + y1.y;
			z1 = m1.z * countX + y1.z;
			w1 = m1.w * countX + y1.w;
		}
		else
		{
			f1 = m2.y * x + y2.y;
			z1 = m2.z * countX + y2.z;
			w1 = m2.w * countX + y2.w;
		}
		float f2 = m3.y * x + y3.y;
		float z2 = m3.z * countX + y3.z;
		float w2 = m3.w * countX + y3.w;

		float mz = (z2 - z1) / (f2 - f1);
		float mw = (w2 - w1) / (f2 - f1);

		int startY = BaseMath::Clamp(f1, minY.y, maxY.y), endY = BaseMath::Clamp(f2, minY.y, maxY.y);
		int increase = 1;
		if (f1 > f2)
			increase = -1;

		int countY = 0;
		while (startY != endY)
		{
			Vector3 out = Vector3::zero;
			Vector3::BarycentricCoordinate(v1.position, v2.position, v3.position, Vector3(x, startY, z1 + countY * mz), out);
			float z = 1.f / (out.x / v1.position.w + out.y / v2.position.w + out.z / v3.position.w);
			z = ((-z) - mainCam->near_Plane) / mainCam->far_Plane;
			float curDepth = bb->GetDepth(x, startY);
			float depth = z;// (z1 + countY * mz);
			if (depth <= bb->maxDepth && depth >= bb->minDepth)
			{
				if (curDepth > depth)
				{
					bb->SetColor(x, startY, Vertex::InterpColor(v1, v2, v3, Vector3(x, startY, z1 + countY * mz)));
					bb->SetDepth(x, startY, depth);
				}
			}
			startY += increase;
			countY++;
		}
		countX++;
	}
}

void DrawTriangleV2(BitmapBuffer * bb, Vertex v1, Vertex v2, Vertex v3, Image * texture)
{
	Vector3 bc1 = v2.position - v1.position;
	Vector3 bc2 = v3.position - v1.position;
	if (bc1.Cross(bc2).Dot(Vector3::forward) > 0) return;
	v1.position = NDCtoScreen(v1.position); //v1.position / v1.position.w;
	v2.position = NDCtoScreen(v2.position); //v2.position / v2.position.w;
	v3.position = NDCtoScreen(v3.position); //v3.position / v3.position.w;
	std::vector<Vector4> list;
	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);

	int index = Vector4::MinXIndex(list);
	Vector4 minX = list[index];
	list.erase(list.begin() + index);
	index = Vector4::MinXIndex(list);
	Vector4 midX = list[index];
	list.erase(list.begin() + index);
	Vector4 maxX = list[0];
	list.clear();

	list.push_back(v1.position);
	list.push_back(v2.position);
	list.push_back(v3.position);
	index = Vector4::MinYIndex(list);
	Vector4 minY = list[index];
	list.erase(list.begin() + index);
	index = Vector4::MinYIndex(list);
	Vector4 midY = list[index];
	list.erase(list.begin() + index);
	Vector4 maxY = list[0];
	list.clear();

	Vector4 m1 = (midX - minX) / (midX.x - minX.x);
	if ((midX.x - minX.x) == 0)
		m1 = 0;
	Vector4 m2 = (maxX - midX) / (maxX.x - midX.x);
	if ((maxX.x - midX.x) == 0)
		m2 = 0;
	Vector4 m3 = (maxX - minX) / (maxX.x - minX.x);
	if ((maxX.x - minX.x) == 0)
		m3 = 0;

	Vector4 y1 = midX - m1 * midX.x;
	Vector4 y2 = midX - m2 * midX.x;
	Vector4 y3 = minX - m3 * minX.x;

	int countX = 0;
	for (int x = minX.x; x <= maxX.x; x++)
	{
		float f1 = 0;
		float w1 = 0;
		float z1 = 0;
		if (x < midX.x)
		{
			f1 = m1.y * x + y1.y;
			z1 = m1.z * countX + y1.z;
			w1 = m1.w * countX + y1.w;
		}
		else
		{
			f1 = m2.y * x + y2.y;
			z1 = m2.z * countX + y2.z;
			w1 = m2.w * countX + y2.w;
		}
		float f2 = m3.y * x + y3.y;
		float z2 = m3.z * countX + y3.z;
		float w2 = m3.w * countX + y3.w;

		float mz = (z2 - z1) / (f2 - f1);
		float mw = (w2 - w1) / (f2 - f1);

		int startY = BaseMath::Clamp(f1, minY.y, maxY.y), endY = BaseMath::Clamp(f2, minY.y, maxY.y);
		int increase = 1;
		if (f1 > f2)
			increase = -1;

		int countY = 0;
		while (startY != endY)
		{
			Vector3 out = Vector3::zero;
			Vector3::BarycentricCoordinate(v1.position, v2.position, v3.position, Vector3(x, startY, z1 + countY * mz), out);
			float z = 1.f / (out.x / v1.position.w + out.y / v2.position.w + out.z / v3.position.w);
			z = ((-z) - mainCam->near_Plane) / mainCam->far_Plane;
			float curDepth = bb->GetDepth(x, startY);
			float depth = z;// (z1 + countY * mz);
			if (depth <= bb->maxDepth && depth >= bb->minDepth)
			{
				if (curDepth > depth)
				{
					bb->SetColor(x, startY, texture->GetColorByUV(Vertex::InterpUV(v1, v2, v3, Vector4(x, startY, z1 + countY * mz, w1 + countY * mw))));
					bb->SetDepth(x, startY, depth);
				}
			}
			startY += increase;
			countY++;
		}
		countX++;
	}
}

void DrawTriangleByCross(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{
}

void DrawTriangleByCom(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color)
{
}
