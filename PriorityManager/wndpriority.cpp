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

	if (!hProcess)
	{
		TCHAR sWndText[1024];
		GetWindowText(hwnd, sWndText, 1024);
		NotifyPriorityChangeFailed(sWndText, dwPriorityClass, NULL, TRUE);

		return FALSE;
	}

	result = SetPriorityClass(hProcess, dwPriorityClass);

	// get main module name to notify
	TCHAR sMainModule[1024];
	if (GetModuleFileNameEx(hProcess, NULL, sMainModule, 1024))
	{
		PathStripPath(sMainModule);

		if (result) 
		{
			NotifyPriorityChanged(sMainModule, dwPriorityClass);
			HandleLiveIcon(hwnd);
		}
		else NotifyPriorityChangeFailed(sMainModule, dwPriorityClass, NULL, TRUE);
	}

	CloseHandle(hProcess);

	return result;
}

BOOL ForegroundIncreasePriority()
{
	DWORD dwCurrentPriority = ForegroundGetPriority();
	DWORD dwNewPriority = GetNextPriority(dwCurrentPriority, TRUE);

	return ForegroundSetPriority(dwNewPriority);
}

BOOL ForegroundDecreasePriority()
{
	DWORD dwCurrentPriority = ForegroundGetPriority();
	DWORD dwNewPriority = GetPrevPriority(dwCurrentPriority, TRUE);

	return ForegroundSetPriority(dwNewPriority);
}

DWORD ForegroundGetPriority()
{
	HWND hwnd;
	HANDLE hProcess;
	DWORD result;

	GetForegroundWindowOpenProcess(&hwnd, &hProcess);

	if (!hProcess)
	{
		return NULL;
	}

	result = GetPriorityClass(hProcess);

	CloseHandle(hProcess);

	return result;
}
