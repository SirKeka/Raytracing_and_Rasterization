#pragma once
#include <windows.h>
#include "structs.h"

#define FLOAT_MAX 3.402823466E+38F

void WinCreate(LPCWSTR ApplicationName, int x, int y, int width, int height);

void WinDestroy(void);

unsigned WinMessage(void);
// The PutPixel() function.
void PutPixel(int x, int y, Color color);

HWND WinGetHWND(void);