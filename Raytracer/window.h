#pragma once
#include <windows.h>

#define FLOAT_MAX 3.402823466E+38

void WinCreate(const char* ApplicationName, int x, int y, int width, int height);

void WinDestroy();

void WinMessage();
// The PutPixel() function.
void PutPixel(int x, int y, COLORREF color);

HWND WinGetHWND();