#include "BitmapBuffer.h"
#include "..\RenderSetting.h"

// i % 2^n => i & (2&(n-1))

BitmapBuffer::BitmapBuffer(HWND hWnd, UINT width, UINT height, DWORD bgColor):
	hWnd(hWnd), width(width), height(height), bgColor(bgColor & 0x00ffffff), scanlineCount(width * 3 + ((width * 3) & 3))
{
	minDepth = 0.1f;
	maxDepth = 1000.f;
	depthBuffer = new float[width * height];

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
	delete[] depthBuffer;
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

	for (int i = 0; i < width; i++)
		depthBuffer[i] = maxDepth;

	for (int i = 1; i < height; i++)
		memcpy(depthBuffer + (i * width), depthBuffer, sizeof(float) * width);
}

void BitmapBuffer::SetColor(int x, int y, DWORD color)
{
	if (x < 0 || x > width || y < 0 || y >= height) return;
	*(DWORD*)(bits + x * BYTES_PER_PIXEL + y * scanlineCount) = color;
}

void BitmapBuffer::SetDepth(int x, int y, float depth)
{
	if (x < 0 || x > width || y < 0 || y >= height) return;
	depthBuffer[y * width + x] = depth;
}

float BitmapBuffer::GetDepth(int x, int y)
{
	if (x < 0 || x > width || y < 0 || y >= height) return 0;
	return depthBuffer[y * width + x];
}

void BitmapBuffer::SetDepthDefault(float min, float max)
{
	minDepth = min;
	maxDepth = max;
}
