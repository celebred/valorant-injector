#include "hook.hpp"
#include <iostream>

static HHOOK g_hookHandle = nullptr;
static HMODULE g_dllModule = nullptr;

bool SetupHook(const std::wstring& dllPath, const std::wstring& functionName, DWORD threadId) {
    std::cout << "[+] loading dll..." << std::endl;
    g_dllModule = LoadLibraryExW(dllPath.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (!g_dllModule) {
        std::cout << "[-] error: failed to load dll" << std::endl;
        return false;
    }

    std::cout << "[+] resolving function address..." << std::endl;
    HOOKPROC addr = (HOOKPROC)GetProcAddress(g_dllModule, std::string(functionName.begin(), functionName.end()).c_str());
    if (!addr) {
        std::cout << "[-] error: function not found in dll" << std::endl;
        FreeLibrary(g_dllModule);
        return false;
    }

    std::cout << "[+] setting hook..." << std::endl;
    g_hookHandle = SetWindowsHookEx(WH_GETMESSAGE, addr, g_dllModule, threadId);
    if (!g_hookHandle) {
        std::cout << "[-] error: failed to set hook" << std::endl;
        FreeLibrary(g_dllModule);
        return false;
    }

    PostThreadMessage(threadId, WM_NULL, NULL, NULL);
    return true;
}

bool RemoveHook() {
    bool success = true;
    if (g_hookHandle && !UnhookWindowsHookEx(g_hookHandle)) {
        std::cout << "[-] error: failed to remove hook" << std::endl;
        success = false;
    }

    if (g_dllModule) {
        FreeLibrary(g_dllModule);
    }

    g_hookHandle = nullptr;
    g_dllModule = nullptr;
    return success;
}