#include "window.h"
#include "Raytracer.h"

typedef struct WinState {
	HINSTANCE hInstance;
	HWND hwnd;			// Дескриптор окна
	MSG msg;
} WinState;

static WinState state;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void WinCreate(const char* ApplicationName, int x, int y, int width, int height) {
	static char szAppName[] = "Window";
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = state.hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);
	state.hwnd = CreateWindow(
		szAppName,						// Название класса окна
		ApplicationName,				// Заголовок окна
		WS_OVERLAPPEDWINDOW,			// Стиль окна
		x ? x : CW_USEDEFAULT,			// Начальная позиция окна по оси х
		y ? y : CW_USEDEFAULT,			// Начальная позиция окна по оси y
		width ? width : CW_USEDEFAULT,	// Начальная ширина окна
		height ? height : CW_USEDEFAULT,// Начальная высота окна
		NULL,							// Дескриптор родительского окна
		NULL,							// Дескриптор меню окна
		state.hInstance,				// Дескриптор экземпляра программы
		NULL
	); // Параметры создания

	int ShouldActivate = 1;  // TODO: ���� ���� �� ������ ��������� ����, ��� ������ ���� false.
	int ShowWindowCommandFlags = ShouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
	ShowWindow(state.hwnd, ShowWindowCommandFlags);
	
}

void WinDestroy()
{
	if (state.hwnd) {
		DestroyWindow(state.hwnd);
		state.hwnd = 0;
	}
}

void WinMessage()
{
	MSG message;
	if (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void PutPixel(int x, int y, COLORREF color)
{
	RECT rect;
	GetClientRect(state.hwnd, &rect);

	int nx = rect.right / 2 + x;
	int ny = rect.bottom / 2 - y - 1;

	if (nx < 0 || nx >= rect.right || ny < 0 || ny >= rect.bottom) {
		return;
	}
	HDC hdc = GetDC(state.hwnd);
	SetPixel(hdc, nx, ny, color);
	ReleaseDC(state.hwnd, hdc);
}

HWND WinGetHWND()
{
	return state.hwnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (iMsg)
	{
	case WM_CREATE:
		// PlaySound(L"hellowin.wav", NULL, SND_FILENAME | SND_ASYNC);
		return 0;
	case WM_PAINT:
		// hdc = BeginPaint(hwnd, &ps);
		GetClientRect(state.hwnd, &rect);
		for (int x = -rect.right / 2; x < rect.right / 2; x++) {
			for (int y = -rect.bottom / 2; y < rect.bottom / 2; y++) {
				Vec3 direction = CanvasToViewport(x, y);
				COLORREF color = TraceRay((Vec3) { 0, 0, 0 }, direction, 1, FLOAT_MAX);
				PutPixel(x, y, color);
			}
		}
		ValidateRect(state.hwnd, &rect);
		/*GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Hello, Windows 95!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
		// EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}