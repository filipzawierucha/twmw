#pragma once
#include <Windows.h>
#include <functional>

BOOL MoveCurrWindow(HWND& activeWindow, int wx, int wy);
BOOL RegisterKeybind(UINT id, UINT keybind, UINT flags, std::function<void(void)> callback);
BOOL keylistener();
