#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WM_NOTIFYICONMSG (WM_USER + 2)

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

extern HINSTANCE hInst;
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL MakeDialogVisible(HWND, BOOL);
BOOL InitializeTrayIcon(HWND);
BOOL DestroyTrayIcon();
VOID HandlePopupMenu(HWND hWnd, POINT point);
