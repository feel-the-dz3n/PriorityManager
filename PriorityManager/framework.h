#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_NOTIFYICONMSG (WM_USER + 2)

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>
#include <psapi.h>
#include <shlwapi.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <iostream>
#include <memory>
#include <algorithm>
#include <string>

extern HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL MakeDialogVisible(HWND, BOOL);
BOOL InitializeTrayIcon(HWND);
BOOL DestroyTrayIcon();
VOID HandlePopupMenu(HWND hWnd, POINT point);
VOID RegisterHotkeys(HWND hWnd);
VOID UnregisterHotkeys(HWND hWnd);
VOID HandleHotkeys(HWND hWnd, int id);
BOOL ForegroundSetPriority(DWORD dwPriorityClass);
VOID NotifyPriorityChanged(LPCWSTR target, DWORD dwPriorityClass);

void string_to_wstring(const std::string& src, std::wstring& dest);
void wstring_to_string(const std::wstring& src, std::string& dest);

#define ID_HOTKEY_RAISEPRIORITY  1
#define ID_HOTKEY_REDUCEPRIORITY 2
