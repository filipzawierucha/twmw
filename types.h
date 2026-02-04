#pragma once
#include <functional>
#include "winutils.h"
#include <vector>

struct keybind {
    UINT id, keycode, flags;
    std::function<void(void)>& callback;
};

std::vector<keybind> keybinds{};
