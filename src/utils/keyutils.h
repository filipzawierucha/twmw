#pragma once 
#include "../types.h"

BOOL RegisterKeybind(UINT id, UINT keybind, UINT flags, std::function<void(void)> callback);
BOOL keylistener();