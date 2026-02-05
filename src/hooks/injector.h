#pragma once 
#include <windows.h>
#include <string>

bool DllInject(HWND &hwnd, const std::string &dll);