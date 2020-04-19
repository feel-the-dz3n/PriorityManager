#pragma once
#include "pch.h"

BOOL InitializeTrayIcon(HWND);
BOOL DestroyTrayIcon();
BOOL ShowTrayBalloon(LPCWSTR info, LPCWSTR title, UINT timeout);
VOID HandleTrayPopupMenu(HWND hWnd, POINT point);
