// tray.cpp : Defines hotkeys-related functions
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"

VOID RegisterHotkeys(HWND hWnd)
{
    RegisterHotKey(hWnd, ID_HOTKEY_RAISEPRIORITY, MOD_ALT | MOD_CONTROL, VK_PRIOR);
    RegisterHotKey(hWnd, ID_HOTKEY_REDUCEPRIORITY, MOD_ALT | MOD_CONTROL, VK_NEXT);
}

VOID UnregisterHotkeys(HWND hWnd)
{
    UnregisterHotKey(hWnd, ID_HOTKEY_RAISEPRIORITY);
    UnregisterHotKey(hWnd, ID_HOTKEY_REDUCEPRIORITY);
}

VOID HandleHotkeys(HWND hWnd, int id) 
{
    if (id == ID_HOTKEY_RAISEPRIORITY)
    {
        ForegroundIncreasePriority();
    }
    else if (id == ID_HOTKEY_REDUCEPRIORITY)
    {
        ForegroundDecreasePriority();
    }
}
