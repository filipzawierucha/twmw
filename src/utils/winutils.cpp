#include <vector>
#include "../types.h"
#include <iostream>

BOOL MoveWindow(HWND &activeWindow, int wx, int wy, int sx, int sy) {
    RECT activeWindowSize;
    GetWindowRect(activeWindow, &activeWindowSize);
    int borderX = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    UINT flags = SWP_NOZORDER;
    if(sx == 0 || sy == 0) flags |= SWP_NOSIZE;
    SetWindowPos(
        activeWindow,
        nullptr,
        wx-borderX,
        wy,
        sx, sy,
        flags
    );

    return true; 
}

std::vector<HWND> GetAllActiveWindows() {
    std::vector<HWND> windows;

    EnumWindows(
        [](HWND hwnd, LPARAM lParam) -> BOOL {
            auto vec = reinterpret_cast<std::vector<HWND>*>(lParam);
            vec->push_back(hwnd);
            return TRUE; 
        },
        reinterpret_cast<LPARAM>(&windows)
    );

    return windows;
}