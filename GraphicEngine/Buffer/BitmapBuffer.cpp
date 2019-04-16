#include "BitmapBuffer.h"

// i % 2^n => i & (2&(n-1))

BitmapBuffer::BitmapBuffer(HWND hWnd, UINT width, UINT height, DWORD bgColor):
	hWnd(hWnd), width(width), height(height), bgColor(bgColor & 0x00ffffff), scanlineCount(width * 3 + ((width * 3) & 3))
{
	hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);

	//bytes = new BYTE[width * height * BYTES_PER_PIXEL];

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = BITS_PER_PIXEL;
	bmi.bmiHeader.biCompression = BI_RGB;

	frontBitmap = CreateDIBSection(memDC, &bmi, DIB_RGB_COLORS, (LPVOID*)&bits, NULL, NULL);
	backBitmap = (HBITMAP)SelectObject(memDC, frontBitmap);
}

BitmapBuffer::~BitmapBuffer()
{
	DeleteObject(SelectObject(memDC, backBitmap));
	DeleteObject(frontBitmap);
	ReleaseDC(hWnd, memDC);
}

void BitmapBuffer::Draw()
{
	BitBlt(hdc, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
}

void BitmapBuffer::Clear()
{
	for (int i = 0; i < scanlineCount; i += BYTES_PER_PIXEL)
		*(DWORD*)(bits + i) = bgColor;

	for (int i = 1; i < height; i++)
		memcpy(bits + (i * scanlineCount), bits, scanlineCount);
}

void BitmapBuffer::SetColor(int x, int y, DWORD color)
{
	if (x < 0 || x > width || y < 0 || y > height) return;
	*(DWORD*)(bits + x * BYTES_PER_PIXEL + y * scanlineCount) = color;
}