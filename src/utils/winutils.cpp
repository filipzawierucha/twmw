#include <vector>
#include "../types.h"

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

BOOL MoveWindow(HWND &activeWindow, int wx, int wy, int sx, int sy) { // fucking wrong math calculations - I need to fix this shitty borders
    RECT activeWindowSize;
    GetWindowRect(activeWindow, &activeWindowSize);
    int borderX = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER);

    UINT flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS;
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

std::vector<HWND> GetAllActiveWindows()
{
    std::vector<HWND> windows;

    EnumWindows(
        [](HWND hwnd, LPARAM lParam) -> BOOL
        {
            LONG_PTR exStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);

            if (!IsWindowVisible(hwnd) || (exStyle & WS_EX_TOOLWINDOW))
                return TRUE;

            if (GetWindow(hwnd, GW_OWNER) != nullptr)
                return TRUE;

            BOOL cloaked = FALSE;
            if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) && cloaked)
                return TRUE;

            wchar_t title[2048]{};
            if (GetWindowTextW(hwnd, title, _countof(title)) == 0)
                return TRUE;

            auto* vec = reinterpret_cast<std::vector<HWND>*>(lParam);
            vec->push_back(hwnd);

            return TRUE;
        },
        reinterpret_cast<LPARAM>(&windows)
    );

    return windows;
}
