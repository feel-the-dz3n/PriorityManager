// tray.cpp : Defines hotkeys-related functions
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"


LPCWSTR GetPriorityText(DWORD dwPriorityClass)
{
	switch (dwPriorityClass)
	{
		// TODO: add more types
	default: return L"Unknown";
	}
}

VOID NotifyPriorityChanged(LPCWSTR target, DWORD dwPriorityClass)
{
	TCHAR buf[1024];
	swprintf_s(buf, L"%s priority for %s", GetPriorityText(dwPriorityClass), target);
	ShowTrayBalloon(buf, L"Priority changed", 1500);
}

VOID NotifyPriorityChangeFailed(LPCWSTR target, DWORD dwPriorityClass, BOOL bGetLastError)
{
	TCHAR buf[1024];
	swprintf_s(buf, L"Unable to set priority for %s.", target);

	if (bGetLastError) 
	{
		DWORD lastError = GetLastError();
		swprintf_s(buf, L"%s (%d).", buf, lastError); // Get error string here
	}

	ShowTrayBalloon(buf, L"Failed to set priority", 1500);
}
