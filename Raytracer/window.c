#include "window.h"
#include "Raytracer.h"

typedef struct {
	unsigned short width;
	unsigned short height;
	unsigned char* buffer;
} Canvas;

typedef struct WinState {
	HINSTANCE hInstance;
	HWND hwnd;			// Дескриптор окна
	MSG msg;
	Canvas canvas;
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

	RECT rect;
	GetClientRect(state.hwnd, &rect);
	state.canvas.width = rect.right;
	state.canvas.height = rect.bottom;
	state.canvas.buffer = malloc(rect.right * rect.bottom * 4);
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

static DrawPixels(HDC hdc)
{
	if (!hdc) {
		hdc = GetDC(state.hwnd);
	}
	BITMAPINFO BitMapInfo;
	ZeroMemory(&BitMapInfo, sizeof(BitMapInfo));
	BitMapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitMapInfo.bmiHeader.biWidth = state.canvas.width;
	BitMapInfo.bmiHeader.biHeight = -state.canvas.height;
	BitMapInfo.bmiHeader.biPlanes = 1;
	BitMapInfo.bmiHeader.biBitCount = 32; // 32 бита на пиксель (RGBA)
	BitMapInfo.bmiHeader.biCompression = BI_RGB;

	StretchDIBits(hdc, 0, 0, state.canvas.width, state.canvas.height,
		0, 0, state.canvas.width, state.canvas.height,
		state.canvas.buffer, &BitMapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void PutPixel(int x, int y, Color color)
{
	x = state.canvas.width / 2 + x;
	y = state.canvas.height / 2 - y - 1;

	if (x < 0 || x >= state.canvas.width || y < 0 || y >= state.canvas.height) {
		return;
	}
	
	Canvas canvas = state.canvas;
	int offset = 4 * (x + canvas.width * y);
	canvas.buffer[offset++] = color.b;
	canvas.buffer[offset++] = color.g;
	canvas.buffer[offset++] = color.r;
	canvas.buffer[offset++] = color.a;
}

HWND WinGetHWND()
{
	return state.hwnd;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	// RECT rect;
	switch (iMsg)
	{
	case WM_CREATE:
		// PlaySound(L"hellowin.wav", NULL, SND_FILENAME | SND_ASYNC);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		DrawPixels(hdc);
		
		//ValidateRect(state.hwnd, &rect);
		/*GetClientRect(hwnd, &rect);
		DrawText(hdc, L"Hello, Windows 95!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);*/
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		free(state.canvas.buffer);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}