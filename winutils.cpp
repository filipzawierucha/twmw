#include <vector>
#include "types.h"
#include <iostream>

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

BOOL GetAllActiveWindows() {
    return 0;
}