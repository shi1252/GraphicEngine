#include "Vertex.h"

DWORD Vertex::InterpColor(Vertex v1, Vertex v2, Vertex v3, Vector3 p)
{
	Vector3 out = Vector3::zero;
	Vector3::BarycentricCoordinate(v1.position, v2.position, v3.position, p, out);

	BYTE r1 = (BYTE)255 & v1.color, r2 = (BYTE)255 & v2.color, r3 = (BYTE)255 & v3.color;
	WORD g1 = ((WORD)65280 & v1.color) >> 8, g2 = ((WORD)65280 & v2.color) >> 8, g3 = ((WORD)65280 & v3.color) >> 8;
	DWORD b1 = ((DWORD)16711680 & v1.color) >> 16, b2 = ((DWORD)16711680 & v2.color) >> 16, b3 = ((DWORD)16711680 & v3.color) >> 16;
	r1 *= out.x; g1 *= out.x; b1 *= out.x;
	r2 *= out.y; g2 *= out.y; b2 *= out.y;
	r3 *= out.z; g3 *= out.z; b3 *= out.z;

	return ((r1 | r2 | r3) | (g1 | g2 | g3) << 8 | (b1 | b2 | b3) << 16);
}