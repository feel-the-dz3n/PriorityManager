// tray.cpp : Defines hotkeys-related functions
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"


LPCWSTR GetPriorityText(DWORD dwPriorityClass)
{
	switch (dwPriorityClass)
	{
	case ABOVE_NORMAL_PRIORITY_CLASS: return L"Above normal";
	case BELOW_NORMAL_PRIORITY_CLASS: return L"Below normal";
	case IDLE_PRIORITY_CLASS: return L"Idle";
	case HIGH_PRIORITY_CLASS: return L"High";
	case NORMAL_PRIORITY_CLASS: return L"Normal (default)";
	case REALTIME_PRIORITY_CLASS: return L"Realtime (unsafe)";
	default:
	{
		TCHAR buf[50];
		swprintf_s(buf, L"Unknown (%d)", dwPriorityClass);
		return buf;
	}
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
		wchar_t errorBuf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, lastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			errorBuf, (sizeof(errorBuf) / sizeof(wchar_t)), NULL);
		swprintf_s(buf, L"%s %s (code: %d).", buf, errorBuf, lastError); // Get error string here
	}

	ShowTrayBalloon(buf, L"Failed to set priority", 1500);
}
