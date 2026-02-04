#include "winutils.h"
#include <vector>
#include "types.h"

BOOL MoveCurrWindow(HWND &activeWindow, int wx, int wy) {
    RECT activeWindowSize;
    GetWindowRect(activeWindow, &activeWindowSize);
    int borderX = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    SetWindowPos(
        activeWindow,
        nullptr,
        wx-borderX,
        wy,
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER
    );

    return true; 
}

BOOL RegisterKeybind(UINT id, UINT keybind, UINT flags, std::function<void(void)> callback) {
    keybinds.push_back({ id, keybind, flags, callback });
    return 0;
}

BOOL RegisterAllKeybinds() {
    for (const auto& kb : keybinds) {
        if (!RegisterHotKey(NULL, kb.id, kb.keycode, kb.flags)) {
            MessageBoxW(NULL, L"Failed to register hotkey", L"Hotkey Error", MB_OK);
            return FALSE;
        }
    }
    return TRUE;
}

BOOL keylistener() {
    if (!RegisterAllKeybinds()) {
        return FALSE;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            for (const auto& kb : keybinds) {
                if (msg.wParam == kb.id) {
                    if (kb.callback)
                      kb.callback();

                    break;
                }
            }
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    for (const auto& kb : keybinds) {
        UnregisterHotKey(NULL, kb.id);
    }

    return TRUE;
}