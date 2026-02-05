//* SOME SHITTY HOOK FROM CGPT *// 

#include "injector.h"

HHOOK g_hook = nullptr;
HMODULE g_module = nullptr;

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        CWPSTRUCT* msg = (CWPSTRUCT*)lParam;

        if (msg->message == WM_GETMINMAXINFO && GetParent(msg->hwnd) == nullptr)
        {
            MINMAXINFO* mmi = (MINMAXINFO*)msg->lParam;

            mmi->ptMinTrackSize.x = 0;
            mmi->ptMinTrackSize.y = 0;

            mmi->ptMaxTrackSize.x = 32767;
            mmi->ptMaxTrackSize.y = 32767;
        }
    }

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

extern "C" __declspec(dllexport) void InstallHook()
{
    if (g_hook == nullptr)
    {
        g_hook = SetWindowsHookEx(
            WH_CALLWNDPROCRET,
            CallWndProc,
            g_module,
            0
        );
    }
}

extern "C" __declspec(dllexport) void UninstallHook()
{
    if (g_hook)
    {
        UnhookWindowsHookEx(g_hook);
        g_hook = nullptr;
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            g_module = (HMODULE)hinstDLL;
            InstallHook();
            break;

        case DLL_PROCESS_DETACH:
            UninstallHook();
            break;
    }
    
    return TRUE;
}
