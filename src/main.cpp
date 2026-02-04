#include "utils/keyutils.h"
#include "utils/winutils.h"
#include "windowManager.h"
#include <thread>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    Sleep(3000);
    HWND activeWindow = GetForegroundWindow();
    MoveWindow(activeWindow, 0, 0);

    //Temporary hard settet keybinds
    RegisterKeybind(1, MOD_CONTROL | MOD_ALT, 'H', []{
      PostQuitMessage(0);
    });
    //     RegisterKeybind(2, MOD_CONTROL, 'Q', []{
    //   SetWindowPosition();
    // });

    std::thread keybindThread(keylistener); // key listener in other thread 
    keybindThread.join();

    return 0; 
};
