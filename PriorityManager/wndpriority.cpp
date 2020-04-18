// wndpriority.cpp : Defines priority functions for windows
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"

VOID GetForegroundWindowProcessId(HWND* hwndptr, LPDWORD processid)
{
	HWND hwnd = GetForegroundWindow();
	*hwndptr = hwnd;

	if (!hwnd) return;

	GetWindowThreadProcessId(hwnd, processid);
}

VOID GetForegroundWindowOpenProcess(HWND* hwndptr, HANDLE* hProcess)
{
	DWORD pid;
	GetForegroundWindowProcessId(hwndptr, &pid);

	if (!pid) return;

	*hProcess = OpenProcess(
		PROCESS_VM_READ | PROCESS_QUERY_INFORMATION | PROCESS_SET_INFORMATION,
		FALSE, pid);
}

BOOL ForegroundSetPriority(DWORD dwPriorityClass)
{
	HWND hwnd;
	HANDLE hProcess;
	BOOL result;

	GetForegroundWindowOpenProcess(&hwnd, &hProcess);

	if (!hProcess) return FALSE;

	result = SetPriorityClass(hProcess, dwPriorityClass);
	// TODO: notify about changing

	CloseHandle(hProcess);

	return result;
}
