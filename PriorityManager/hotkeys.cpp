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
        BOOL bResult = ForegroundSetPriority(HIGH_PRIORITY_CLASS);
        if (bResult) MessageBox(hWnd, L"Good", L"PM Raise Priority", 0);
        else MessageBox(hWnd, L"Failed", L"PM Raise Priority", 0);
    }
    else if (id == ID_HOTKEY_REDUCEPRIORITY)
    {
        BOOL bResult = ForegroundSetPriority(NORMAL_PRIORITY_CLASS);
        if (bResult) MessageBox(hWnd, L"Good", L"PM Reduce Priority", 0);
        else MessageBox(hWnd, L"Failed", L"PM Reduce Priority", 0);
    }
}
