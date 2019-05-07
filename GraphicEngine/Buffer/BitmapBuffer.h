#pragma once
#include <Windows.h>

static const unsigned int BYTES_PER_PIXEL = 3;
static const unsigned int BITS_PER_PIXEL = 8 * BYTES_PER_PIXEL;

class BitmapBuffer
{
private:
	HWND hWnd;
	UINT width;
	UINT height;
	DWORD bgColor;
	DWORD scanlineCount;

	HDC hdc;
	HDC memDC;
	HBITMAP frontBitmap;
	HBITMAP backBitmap;

	float depthDefault;
	BYTE *bits;
	float *depthBuffer;
public:
	BitmapBuffer(HWND hWnd, UINT width, UINT height, DWORD bgColor = 0xff000000);
	~BitmapBuffer();

	void Draw();
	void Clear();

	void SetColor(int x, int y, DWORD color);
	void SetDepth(int x, int y, float depth);
	float GetDepth(int x, int y);
	void SetDepthDefault(float v);

	UINT GetWidth() { return width; }
	UINT GetHeight() { return height; }
};