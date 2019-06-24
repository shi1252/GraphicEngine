#pragma once
#include "Vector.h"

class Vertex
{
public:
	Vector4 position;
	Vector2 uv;
	DWORD color;

	Vertex()
		:position(Vector4::zero), uv(Vector2::zero), color(0) {}
	Vertex(float x, float y, float z, DWORD color = 0)
		:position(Vector4(x, y, z)), uv(Vector2::zero), color(color) {}
	Vertex(Vector4 v, DWORD color)
		:position(v), color(color) {}
	Vertex(float x, float y, float z, float uvx, float uvy)
		:position(Vector4(x, y, z)), uv(Vector2(uvx, uvy)), color(0) {}
	Vertex(Vector4 v, Vector2 uv)
		:position(v), uv(uv), color(0) {}
	Vertex(Vector4 v, Vector2 uv, DWORD color)
		:position(v), uv(uv), color(color) {}

	static DWORD InterpColor(Vertex v1, Vertex v2, Vertex v3, Vector3 p);
	static Vector2 InterpUV(Vertex v1, Vertex v2, Vertex v3, Vector4 p);
	static bool BackfaceCulling(Vertex v1, Vertex v2, Vertex v3);
};