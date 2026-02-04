#pragma once
#include <Windows.h>
#include <functional>
#include <vector>

BOOL MoveWindow(HWND &activeWindow, int wx, int wy, int sx = 0, int sy = 0);
std::vector<HWND> GetAllActiveWindows();