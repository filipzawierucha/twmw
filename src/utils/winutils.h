#pragma once
#include <Windows.h>
#include <functional>
#include <vector>

BOOL MoveCurrWindow(HWND& activeWindow, int wx, int wy);
std::vector<HWND> GetAllActiveWindows();