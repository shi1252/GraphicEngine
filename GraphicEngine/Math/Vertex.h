#pragma once
#include "Vector.h"

class Vertex
{
public:
	Vector3 position;
	Vector2 uv;
	DWORD color;

	Vertex()
		:position(Vector3::zero), uv(Vector2::zero), color(0) {}
	Vertex(float x, float y, float z, DWORD color = 0)
		:position(Vector3(x, y, z)), uv(Vector2::zero), color(color) {}
	Vertex(Vector3 v, DWORD color)
		:position(v), color(color) {}
	Vertex(float x, float y, float z, float uvx, float uvy)
		:position(Vector3(x, y, z)), uv(Vector2(uvx, uvy)), color(0) {}
	Vertex(Vector3 v, Vector2 uv)
		:position(v), uv(uv), color(0) {}
};