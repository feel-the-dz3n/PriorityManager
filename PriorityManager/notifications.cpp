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
	ShowTrayBalloon(buf, L"Priority Changed", 1500);
}
