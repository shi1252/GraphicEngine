#include "RenderSetting.h"
#include "GraphicEngine.h"
#include <time.h>

BitmapBuffer *buffer;

Camera *mainCam;

static Matrix4x4 worldMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
static std::vector<BaseGeometry*> renderList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Init();
void Render();
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

	buffer = new BitmapBuffer(hWnd, WIN_WIDTH, WIN_HEIGHT, 0xff888888);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	Init();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		Update();
		Render();
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
	mainCam = new Camera();
	buffer->SetDepthDefault(mainCam->near_Plane, mainCam->far_Plane);

	PlaneGeometry *p = new PlaneGeometry(1, 1);
	CubeGeometry *c = new CubeGeometry(1, 1, 1);
	//renderList.push_back(p);
	renderList.push_back(c);

	const float p4 = 0.0625f;
	const float p8 = 0.125f;
	const float p12 = 0.1875f;
	const float p16 = 0.25f;

	p->vertices[0].uv = Vector2(p8, 1.f - p16);
	p->vertices[1].uv = Vector2(p8, 1.f - p8);
	p->vertices[2].uv = Vector2(p16, 1.f - p8);
	p->vertices[3].uv = Vector2(p16, 1.f - p16);
	p->texture = new Image(".\\Textures\\Steve.bmp");

	c->vertices[0].uv = Vector2(p8, 1.f - p16);
	c->vertices[1].uv = Vector2(p8, 1.f - p8);
	c->vertices[2].uv = Vector2(p16, 1.f - p8);
	c->vertices[3].uv = Vector2(p16, 1.f - p16);
	c->vertices[4].uv = Vector2(p8 + p16, 1.f - p16);
	c->vertices[5].uv = Vector2(p8 + p16, 1.f - p8);
	c->vertices[6].uv = Vector2(0.5f, 1.f - p8);
	c->vertices[7].uv = Vector2(0.5f, 1.f - p16);
	c->vertices[8].uv = Vector2(0.f, 1.f - p16);
	c->vertices[9].uv = Vector2(0.f, 1.f - p8);
	c->vertices[10].uv = Vector2(p8, 1.f - p8);
	c->vertices[11].uv = Vector2(p8, 1.f - p16);
	c->vertices[12].uv = Vector2(p16, 1.f - p16);
	c->vertices[13].uv = Vector2(p16, 1.f - p8);
	c->vertices[14].uv = Vector2(p8 + p16, 1.f - p8);
	c->vertices[15].uv = Vector2(p8 + p16, 1.f - p16);
	c->vertices[20].uv = Vector2(p8, 1.f - p8);
	c->vertices[21].uv = Vector2(p8, 1.f);
	c->vertices[22].uv = Vector2(p16, 1.f);
	c->vertices[23].uv = Vector2(p16, 1.f - p8);
	c->vertices[16].uv = Vector2(p16, 1.f - p8); 
	c->vertices[17].uv = Vector2(p16, 1.f);
	c->vertices[18].uv = Vector2(p8 + p16, 1.f);
	c->vertices[19].uv = Vector2(p8 + p16, 1.f - p8);
	c->texture = new Image(".\\Textures\\Steve.bmp");

	mainCam->transform.position = Vector3(0, 0, -10);
}

void Update()
{
	float curTime = clock();
	float deltaTime = (curTime - oldTime)/CLOCKS_PER_SEC;

	if (GetAsyncKeyState('W'))
		mainCam->transform.Translate(Vector3::up, 1.0f);// *deltaTime);
	if (GetAsyncKeyState('S'))
		mainCam->transform.Translate(Vector3::down, 1.0f);// *deltaTime);
	if (GetAsyncKeyState('A'))
		mainCam->transform.Translate(Vector3::left, 1.0f);// *deltaTime);
	if (GetAsyncKeyState('D'))
		mainCam->transform.Translate(Vector3::right, 1.0f);// *deltaTime);
	if (GetAsyncKeyState('Q'))
		mainCam->transform.Translate(Vector3::forward, 1.0f);// *deltaTime);
	if (GetAsyncKeyState('E'))
		mainCam->transform.Translate(Vector3::backward, 1.0f);// *deltaTime);

	renderList[0]->transform->Rotate(Vector3(1.f, 0.f, 0));
	//renderList[0]->transform->Translate(Vector3(1.f, 0.f, 0), 1.0f);

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

void Render()
{
	buffer->Clear();

	// Call DrawFunction
	//Vertex v1(-0.1.f, 0.1.f, 0, RGB(255, 0, 0)), v2(-0.1.f, -0.1.f, 0, RGB(0, 255, 0)), v3(0, 0, 0, RGB(0, 0, 255));
	//DrawTriangleV2(bb, v1, v2, v3);
	
	Matrix4x4 mvp = mainCam->GetProjectionMatrix() * mainCam->GetViewMatrix() * worldMatrix;

	for (int i = 0; i < renderList.size(); i++)
	{
		renderList[i]->Draw(buffer, mvp);
	}

	buffer->Draw();
}