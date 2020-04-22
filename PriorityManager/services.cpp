#include "pch.h"

VOID InitializeServices(HWND hWnd)
{
    Settings::Instance().Load();
    InitializeTrayIcon(hWnd);
    RegisterHotkeys(hWnd);
    InitializeHooks();
}

VOID DestroyServices(HWND hWnd)
{
    Settings::Instance().Save();
    DestroyTrayIcon();
    UnregisterHotkeys(hWnd);
    DestroyHooks();
}
