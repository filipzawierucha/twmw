#include <vector>
#include "../types.h"
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