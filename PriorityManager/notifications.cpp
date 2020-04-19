// tray.cpp : Defines hotkeys-related functions
//

#include "pch.h"
#include "framework.h"
#include "PriorityManager.h"


VOID NotifyPriorityChanged(LPCWSTR target, DWORD dwPriorityClass)
{
	TCHAR buf[1024];
	swprintf_s(buf, L"%s priority for %s", GetPriorityText(dwPriorityClass), target);
	ShowTrayBalloon(buf, L"Priority changed", 1500);
}

VOID NotifyPriorityChangeFailed(LPCWSTR target, DWORD dwPriorityClass, LPCWSTR szErrorMessage, BOOL bGetLastError)
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
		swprintf_s(buf, L"%s %s (code: %d).", buf, errorBuf, lastError);
	}

	if (szErrorMessage)
	{
		swprintf_s(buf, L"%s %s", buf, szErrorMessage);
	}

	ShowTrayBalloon(buf, L"Failed to set priority", 1500);
}
