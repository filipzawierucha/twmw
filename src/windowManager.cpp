// Main foundation file for window management
#include "utils/winutils.h"
#include "hooks/injector.h"
// #include <unordered_set>
#include "types.h"

// std::unordered_set<DWORD> injectedPIDs;

BOOL SetWindowPosition() {
    std::vector<HWND> windows = GetAllActiveWindows();
    int windowWidth = desktop.screen_width / windows.size();

    int windowOffset = 0;
    for(HWND& win : windows) {
        // DWORD pid = 0;
        // GetWindowThreadProcessId(win, &pid);

        // if (pid && injectedPIDs.find(pid) == injectedPIDs.end()) {
        //     if (DllInject(win, "wsHook.dll")) {
        //         injectedPIDs.insert(pid);
        //     }
        // }

        if (IsZoomed(win))
            ShowWindow(win, SW_RESTORE);

        MoveWindow(win, windowOffset, 0, windowWidth, desktop.screen_height);
        windowOffset += windowWidth;
    }

    return TRUE;
}