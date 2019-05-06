#pragma once
#include <Windows.h>
#include "..\Math\Vector.h"

class Image
{
private:
	int width;
	int height;
	HBITMAP hBitmap;

	BYTE *pixel;
public:
	Image(const char *path)
	{
		hBitmap = (HBITMAP)LoadImageA(NULL, path, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

		if (!hBitmap) return;

		BITMAP bm;
		GetObject(hBitmap, sizeof(BITMAP), &bm);

		width = bm.bmWidth;
		height = bm.bmHeight;

		BITMAPINFOHEADER bmih;
		ZeroMemory(&bmih, sizeof(BITMAPINFOHEADER));
		bmih.biSize = sizeof(BITMAPINFOHEADER);
		bmih.biWidth = bm.bmWidth;
		bmih.biHeight = bm.bmHeight;
		bmih.biPlanes = 1;
		bmih.biBitCount = 32;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = bm.bmWidth * 4 * bm.bmHeight;
		
		pixel = new BYTE[bmih.biSizeImage];
		if (!GetDIBits(CreateCompatibleDC(0), hBitmap, 0, bm.bmHeight, pixel, (BITMAPINFO*)&bmih, DIB_RGB_COLORS))
		{
			delete[] pixel;
		}
	}
	Image(const Image &copy)
	{
		width = copy.width;
		height = copy.height;
		pixel = new BYTE[width * height * 4];
		memcpy(pixel, copy.pixel, sizeof(BYTE) * width * height * 4);
	}
	~Image()
	{
		DeleteObject(hBitmap);
		delete[] pixel;
	}

	DWORD GetColorByUV(float x, float y);
	DWORD GetColorByUV(Vector2 v)
	{
		return GetColorByUV(v.x, v.y);
	}
};