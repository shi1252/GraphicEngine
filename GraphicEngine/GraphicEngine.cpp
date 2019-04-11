#include <Windows.h>
#include "RenderSetting.h"
#include "GraphicEngine.h"
#include "Draw\Draw.h"
#include ".\Geometry\PlaneGeometry.h"

static Matrix4x4 worldMatrix(1, 0, 0, WIN_WIDTH * 0.5f, 0, 1, 0, WIN_HEIGHT * 0.5f, 0, 0, 1, 0, 0, 0, 0, 1);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LPCTSTR szWndAppName = TEXT("GraphicEngine");

	WNDCLASSEX wc = {sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, szWndAppName, NULL};
	RegisterClassEx(&wc);

	HWND hWnd;
	hWnd = CreateWindow(szWndAppName, szWndAppName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, 0, WIN_WIDTH, WIN_HEIGHT, GetDesktopWindow(), NULL, wc.hInstance, NULL);

	LONG x, y;
	RECT client, window;
	GetClientRect(hWnd, &client);
	GetWindowRect(hWnd, &window);
	x = (window.right - window.left) - client.right;
	y = (window.bottom - window.top) - client.bottom;
	MoveWindow(hWnd, window.left, window.top, WIN_WIDTH + x, WIN_HEIGHT + y, true);
	GetClientRect(hWnd, &client);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}
	}

	UnregisterClass(szWndAppName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PlaneGeometry p(100, 100), *p2;
	Vertex v1(300, 400, 0, RGB(255, 0, 0)), v2(500, 400, 0, RGB(0,255,0)), v3(200,300,0,RGB(0,0,255));
	switch (message)
	{
	case WM_KEYDOWN:
		return 0;
	case WM_KEYUP:
		return 0;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		SetPixel(hdc, WIN_WIDTH / 2, WIN_HEIGHT / 2, RGB(0, 0, 0));
		DrawLine(hdc, Vector2(0, 0), Vector2(WIN_WIDTH, WIN_HEIGHT), RGB(255, 0, 0));
		SetPixel(hdc, WIN_WIDTH - 10, WIN_HEIGHT - 10, RGB(0, 0, 0));
		//DrawTriangleV2(hdc, Vector2(300, 400), Vector2(500, 400), Vector2(200, 300), RGB(0, 255, 0));
		//DrawTriangleV2(hdc, Vector2(200, 300), Vector2(300, 600), Vector2(175, 500), RGB(0, 255, 0));
		//DrawTriangleV2(hdc, Vector2(300, 600), Vector2(300, 400), Vector2(500, 575), RGB(0, 255, 0));
		DrawLine(hdc, Vector2(100, 200), Vector2(200, 100), RGB(255, 0, 0));
		p2 = (PlaneGeometry*)&(worldMatrix * Matrix4x4::TRSMatrix(Vector3::zero * 150.0f, Vector3(0, 0, 0), Vector3::one * 0.5f) * p);
		p2->Draw(hdc);
		DrawTriangleV2(hdc, v1, v2, v3);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}