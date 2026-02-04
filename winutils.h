#pragma once
#include <Windows.h>
#include <functional>

BOOL MoveCurrWindow(HWND& activeWindow, int wx, int wy);
BOOL GetAllActiveWindows();