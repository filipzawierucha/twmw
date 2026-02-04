// Main foundation file for window management
#include <vector>
#include "utils/winutils.h"
#include "types.h"

// Temporary function for trying if it works
// BOOL SetWindowPosition() {
//     std::vector<HWND> windows = GetAllActiveWindows();
//     int windowWidth = desktop.screen_width / windows.size();
//     int windowOffset = 0;
//     for(HWND win : windows) {
//         MoveWindow(win, windowOffset, 0, windowWidth, desktop.screen_height);
//         windowOffset += windowWidth;
//     }
//     return TRUE;
// }