#include "Image.h"

DWORD Image::GetColorByUV(float x, float y)
{
	if (!hBitmap) return 0;

	DWORD color = 0;
	int px = x * width, py = y * height;

	BYTE r = pixel[(width * py + px) * 4 + 2];
	BYTE g = pixel[(width * py + px) * 4 + 1];
	BYTE b = pixel[(width * py + px) * 4 + 0];

	color = (r << 16) | (g << 8) | (b);

	return color;
}