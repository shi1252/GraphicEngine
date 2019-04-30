#include "RenderSetting.h"
#include "GraphicEngine.h"

Camera mainCam(WIN_WIDTH, WIN_HEIGHT);

static Matrix4x4 worldMatrix(1, 0, 0, WIN_WIDTH * 0.5f, 0, 1, 0, WIN_HEIGHT * 0.5f, 0, 0, 1, 0, 0, 0, 0, 1);
static std::vector<BaseGeometry*> renderList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Render(BitmapBuffer *bb);
void Update();

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

	BitmapBuffer buffer(hWnd, WIN_WIDTH, WIN_HEIGHT, 0xff888888);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	PlaneGeometry p(100, 100);
	renderList.push_back(&p);

	mainCam.transform.position = Vector3(0, 0, -10);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Update();
		Render(&buffer);
	}

	UnregisterClass(szWndAppName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		return 0;
	case WM_KEYUP:
		return 0;
	case WM_PAINT:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Update()
{
	//p.transform->position += Vector3(1, 0, 0);
	renderList[0]->transform->Rotate(Vector3(0, 2.5f, 0));
}

void Render(BitmapBuffer *bb)
{
	bb->Clear();

	// Call DrawFunction
	//Vertex v1(300, 400, 0, RGB(255, 0, 0)), v2(500, 400, 0, RGB(0, 255, 0)), v3(200, 300, 0, RGB(0, 0, 255));

	//DrawTriangleV2(bb, v1, v2, v3);
	Matrix4x4 mvp = mainCam.GetProjectionMatrix() * mainCam.GetViewMatrix() * worldMatrix;

	for (int i = 0; i < renderList.size(); i++)
	{
		renderList[i]->Draw(bb, mvp);
	}

	bb->Draw();
}