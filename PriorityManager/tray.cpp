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

BOOL ShowTrayBalloon(LPCWSTR info, LPCWSTR title, UINT timeout)
{
	tnd.uFlags = NIF_INFO;
	tnd.uTimeout = timeout;
	lstrcpyn(tnd.szInfo, info, sizeof(tnd.szInfo));
	lstrcpyn(tnd.szInfoTitle, title, sizeof(tnd.szInfo));

	return Shell_NotifyIcon(NIM_MODIFY, &tnd);
}

BOOL DestroyTrayIcon()
{
	return Shell_NotifyIcon(NIM_DELETE, &tnd);
}

VOID HandleTrayPopupMenu(HWND hWnd, POINT point)
{
	HMENU hMenu;
	HMENU hMenuTrackPopup;
	LPWSTR pszIDMenu;

	pszIDMenu = MAKEINTRESOURCE(IDR_TRAYMENU);
	hMenu = LoadMenu(hInst, pszIDMenu);
	if (!hMenu)  return;
	hMenuTrackPopup = GetSubMenu(hMenu, 0);
	TrackPopupMenu(hMenuTrackPopup, 0, point.x, point.y, 0, hWnd, NULL);
	DestroyMenu(hMenu);
}
