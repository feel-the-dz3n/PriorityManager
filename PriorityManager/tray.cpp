// tray.cpp : Defines tray-related functions
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"

NOTIFYICONDATA tnd;

BOOL InitializeTrayIcon(HWND hWnd) 
{
	HICON hStatusIcon;
	LPWSTR pszIDStatusIcon;

	pszIDStatusIcon = MAKEINTRESOURCE(IDI_PRIORITYMANAGER);

	hStatusIcon = LoadIcon(hInst, pszIDStatusIcon);
	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = hWnd;
	tnd.uID = 1;
	tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnd.uCallbackMessage = WM_NOTIFYICONMSG;
	tnd.hIcon = hStatusIcon;
	lstrcpyn(tnd.szTip, L"Priority Manager", sizeof(tnd.szTip));

	return Shell_NotifyIcon(NIM_ADD, &tnd);
}

BOOL DestroyTrayIcon()
{
	return Shell_NotifyIcon(NIM_DELETE, &tnd);
}
