#include "dll.hpp"
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

std::wstring GetExportedFunctionName(const std::wstring& dllPath) {
    HMODULE hModule = LoadLibraryExW(dllPath.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);
    if (!hModule) return L"";

    ULONG size;
    PIMAGE_EXPORT_DIRECTORY exportDir = (PIMAGE_EXPORT_DIRECTORY)ImageDirectoryEntryToData(
        hModule, TRUE, IMAGE_DIRECTORY_ENTRY_EXPORT, &size);

    if (!exportDir) {
        FreeLibrary(hModule);
        return L"";
    }

    DWORD* functions = (DWORD*)((BYTE*)hModule + exportDir->AddressOfFunctions);
    DWORD* names = (DWORD*)((BYTE*)hModule + exportDir->AddressOfNames);
    WORD* ordinals = (WORD*)((BYTE*)hModule + exportDir->AddressOfNameOrdinals);

    for (DWORD i = 0; i < exportDir->NumberOfNames; i++) {
        char* functionName = (char*)((BYTE*)hModule + names[i]);
        if (strcmp(functionName, "DllMain") != 0) {
            std::wstring wName(functionName, functionName + strlen(functionName));
            FreeLibrary(hModule);
            return wName;
        }
    }

    FreeLibrary(hModule);
    return L"";
}