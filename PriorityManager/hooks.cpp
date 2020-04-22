#include "pch.h"

HWINEVENTHOOK hWndChangeHook, objectCreateHook;

void CALLBACK windowChangeHookCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild,
    DWORD dwEventThread, DWORD dwmsEventTime)
{
    HotForeWindowChangedCallback(hwnd);
    HandleLiveIcon(hwnd);
}

void CALLBACK objectCreateHookCallback(HWINEVENTHOOK hook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild,
    DWORD dwEventThread, DWORD dwmsEventTime)
{
    // TODO: PriorityOnStartCallback()
}

VOID InitializeHooks()
{
    hWndChangeHook = SetWinEventHook(
        EVENT_OBJECT_FOCUS, EVENT_OBJECT_FOCUS,
        NULL, 
        &windowChangeHookCallback, 0, 0,
        WINEVENT_OUTOFCONTEXT);

    objectCreateHook = SetWinEventHook(
        EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE,
        NULL,
        objectCreateHookCallback,
        0, 0, WINEVENT_OUTOFCONTEXT);
}

VOID DestroyHooks()
{
    UnhookWinEvent(hWndChangeHook);
    UnhookWinEvent(objectCreateHook);
}
