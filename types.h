#pragma once
#include "winutils.h"
#include <functional>
#include <vector>

struct keybind {
    UINT id, keycode, flags;
    std::function<void(void)>& callback;
};

struct {
  UINT screen_width = ::GetSystemMetrics(SM_CXSCREEN);
  UINT screen_height = ::GetSystemMetrics(SM_CYSCREEN);
  UINT apps_number; 
} desktop;

extern std::vector<keybind> keybinds;