#pragma once
#include <windows.h>

#define FLOAT_MAX 3.402823466E+38

typedef struct Color { unsigned char r, g, b, a; } Color;

void WinCreate(const char* ApplicationName, int x, int y, int width, int height);

void WinDestroy(void);

void WinMessage(void);
// The PutPixel() function.
void PutPixel(int x, int y, Color color);

HWND WinGetHWND(void);