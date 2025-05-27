#include "ui.hpp"

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE 20
#endif

void CustomizeConsoleWindow() {
    HWND consoleWindow = GetConsoleWindow();
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = { 60, 40 };
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize = { 0, 0, 70, 30 };
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
    style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_THICKFRAME);
    SetWindowLongPtr(consoleWindow, GWL_STYLE, style);

    HMODULE dwmapi = LoadLibrary(TEXT("dwmapi.dll"));
    if (dwmapi) {
        typedef HRESULT(WINAPI* DwmSetWindowAttributePtr)(HWND, DWORD, LPCVOID, DWORD);
        DwmSetWindowAttributePtr DwmSetWindowAttributeFn = (DwmSetWindowAttributePtr)GetProcAddress(dwmapi, "DwmSetWindowAttribute");

        if (DwmSetWindowAttributeFn) {
            BOOL darkMode = TRUE;
            DwmSetWindowAttributeFn(consoleWindow, DWMWA_USE_IMMERSIVE_DARK_MODE, &darkMode, sizeof(darkMode));
        }
        FreeLibrary(dwmapi);
    }

    SetConsoleTitle(L"(chi-njector)");
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}