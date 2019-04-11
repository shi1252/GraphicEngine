#pragma once
#define PI 3.141592f
#define DegToRad 0.01745329252f
#define RadToDeg 57.295779513f
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

struct Vector3;
struct Vertex;

static class BaseMath
{
public:
	template <typename T>
	static T Lerp(T &val1, T &val2, float ratio)
	{
		if (ratio > 1.f)
			ratio = 1.f;
		else if (ratio < 0.f)
			ratio = 0.f;
		return (val1 + (val2 - val1) * ratio);
	}
	//static DWORD InterpColor(DWORD &color1, DWORD &color2, float ratio)
	//{
	//	if (ratio > 1.f)
	//		ratio = 1.f;
	//	else if (ratio < 0.f)
	//		ratio = 0.f;

	//	BYTE r1 = (BYTE)255 & color1, r2 = (BYTE)255 & color2;
	//	WORD g1 = ((WORD)65280 & color1) >> 8, g2 = ((WORD)65280 & color2) >> 8;
	//	DWORD b1 = ((DWORD)16711680 & color1) >> 16, b2 = ((DWORD)16711680 & color2) >> 16;
	//	return (Lerp(r1, r2, ratio) | Lerp(g1, g2, ratio) << 8 | Lerp(b1, b2, ratio) << 16);
	//}
	static DWORD InterpColor(Vertex v1, Vertex v2, Vertex v3, Vector3 p);
	static void BarycentricCoordinate(Vector3 &v1, Vector3 &v2, Vector3 &v3, Vector3 &p, Vector3 &out);
};