#include "winutils.h"
#include <iostream>
#include <thread>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    Sleep(3000);
    HWND activeWindow = GetForegroundWindow();
    MoveCurrWindow(activeWindow, 0, 0);

    RegisterKeybind(1, MOD_CONTROL | MOD_ALT, 'H', []{
      PostQuitMessage(0);
    });

    std::thread keybindThread(keylistener); // key listener in other thread 
    keybindThread.join();

    return 0; 
};
