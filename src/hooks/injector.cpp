#include <windows.h>
#include <string>

bool DllInject(HWND &hwnd, const std::string &dllPath)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid == 0) return false;

    HANDLE hProcess = OpenProcess(
        PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
        PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ,
        FALSE, pid);

    if (!hProcess) return false;

    void* remoteMem = VirtualAllocEx(hProcess, nullptr, dllPath.size() + 1,
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (!remoteMem) {
        CloseHandle(hProcess);
        return false;
    }

    SIZE_T written;
    if (!WriteProcessMemory(hProcess, remoteMem, dllPath.c_str(), dllPath.size() + 1, &written)) {
        VirtualFreeEx(hProcess, remoteMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    HANDLE hThread = CreateRemoteThread(
        hProcess, nullptr, 0,
        (LPTHREAD_START_ROUTINE)LoadLibraryA,
        remoteMem, 0, nullptr);

    if (!hThread) {
        VirtualFreeEx(hProcess, remoteMem, 0, MEM_RELEASE);
        CloseHandle(hProcess);
        return false;
    }

    WaitForSingleObject(hThread, INFINITE);
    VirtualFreeEx(hProcess, remoteMem, 0, MEM_RELEASE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return true;
}