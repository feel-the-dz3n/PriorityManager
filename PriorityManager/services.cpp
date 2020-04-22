#include "pch.h"

VOID InitializeServices(HWND hWnd)
{
    InitializeTrayIcon(hWnd);
    RegisterHotkeys(hWnd);
    InitializeHooks();
}

VOID DestroyServices(HWND hWnd)
{
    DestroyTrayIcon();
    UnregisterHotkeys(hWnd);
    DestroyHooks();
}
