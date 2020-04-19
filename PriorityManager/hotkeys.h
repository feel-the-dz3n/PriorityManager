#pragma once
#include "pch.h"

#define ID_HOTKEY_RAISEPRIORITY  1
#define ID_HOTKEY_REDUCEPRIORITY 2

VOID RegisterHotkeys(HWND hWnd);
VOID UnregisterHotkeys(HWND hWnd);
VOID HandleHotkeys(HWND hWnd, int id);
