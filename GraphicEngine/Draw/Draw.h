#pragma once
#include <Windows.h>
#include <vector>
class BitmapBuffer;
class Vertex;
class Image;
struct Vector2;

extern void DrawDot(BitmapBuffer *bb, Vector2 pos, COLORREF color);
extern void DrawLine(BitmapBuffer *bb, Vector2 start, Vector2 end, COLORREF color);
extern void DrawTriangle(BitmapBuffer *bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color);
extern void DrawTriangleV2(BitmapBuffer *bb, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color);
extern void DrawTriangleV2(BitmapBuffer *bb, Vertex v1, Vertex v2, Vertex v3);
extern void DrawTriangleV2(BitmapBuffer *bb, Vertex v1, Vertex v2, Vertex v3, Image *texture);
extern void DrawTriangleByCross(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color);
extern void DrawTriangleByCom(HDC hdc, Vector2 v1, Vector2 v2, Vector2 v3, COLORREF color);