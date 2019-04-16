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

	BYTE *bits;
public:
	BitmapBuffer(HWND hWnd, UINT width, UINT height, DWORD bgColor = 0xff000000);
	~BitmapBuffer();

	void Draw();
	void Clear();

	void SetColor(int x, int y, DWORD color);

	UINT GetWidth() { return width; }
	UINT GetHeight() { return height; }
};