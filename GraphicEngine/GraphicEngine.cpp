#include "RenderSetting.h"
#include "GraphicEngine.h"
#include <time.h>

Camera *mainCam;

static Matrix4x4 worldMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
static std::vector<BaseGeometry*> renderList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Init();
void Render(BitmapBuffer *bb);
void Update();
void Clear();

float oldTime = clock();

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

	Init();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Update();
		Render(&buffer);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	Clear();
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

void Init()
{
	mainCam = new Camera(WIN_WIDTH, WIN_HEIGHT);

	PlaneGeometry *p = new PlaneGeometry(10, 10);
	renderList.push_back(p);

	const float p4 = 0.0625f;
	const float p8 = 0.125f;
	const float p12 = 0.1875f;
	const float p16 = 0.25f;

	p->vertices[1].uv = Vector2(p8, 1.f - p16);
	p->vertices[0].uv = Vector2(p8, 1.f - p8);
	p->vertices[3].uv = Vector2(p16, 1.f - p8);
	p->vertices[2].uv = Vector2(p16, 1.f - p16);
	p->texture = new Image(".\\Textures\\Steve.bmp");

	mainCam->transform.position = Vector3(0, 0, -100);
}

void Update()
{
	float curTime = clock();
	float deltaTime = (oldTime - curTime)/CLOCKS_PER_SEC;

	if (GetAsyncKeyState('W'))
		mainCam->transform.Translate(Vector3::up, 1.0f * deltaTime);
	if (GetAsyncKeyState('S'))
		mainCam->transform.Translate(Vector3::down, 1.0f * deltaTime);
	if (GetAsyncKeyState('A'))
		mainCam->transform.Translate(Vector3::left, 1.0f * deltaTime);
	if (GetAsyncKeyState('D'))
		mainCam->transform.Translate(Vector3::right, 1.0f * deltaTime);

	renderList[0]->transform->Rotate(Vector3(0, 2.5f, 0));

	oldTime = curTime;
}

void Clear()
{
	for (int i = 0; i < renderList.size(); i++)
		renderList[i]->~BaseGeometry();
	renderList.clear();

	delete mainCam;
	mainCam = nullptr;
}

void Render(BitmapBuffer *bb)
{
	bb->Clear();

	// Call DrawFunction
	//Vertex v1(-0.1.f, 0.1.f, 0, RGB(255, 0, 0)), v2(-0.1.f, -0.1.f, 0, RGB(0, 255, 0)), v3(0, 0, 0, RGB(0, 0, 255));
	//DrawTriangleV2(bb, v1, v2, v3);
	
	Matrix4x4 mvp = mainCam->GetProjectionMatrix() * mainCam->GetViewMatrix() * worldMatrix;

	for (int i = 0; i < renderList.size(); i++)
	{
		renderList[i]->Draw(bb, mvp);
	}

	bb->Draw();
}