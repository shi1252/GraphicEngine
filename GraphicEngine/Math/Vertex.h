#pragma once
#include "Vector.h"

class Vertex
{
public:
	Vector3 position;
	DWORD color;

	Vertex()
		:position(Vector3::zero), color(0) {}
	Vertex(float x, float y, float z, DWORD color = 0)
		:position(Vector3(x, y, z)), color(color) {}
	Vertex(Vector3 v, DWORD color)
		:position(v), color(color) {}
};