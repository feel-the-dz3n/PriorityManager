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
	swprintf_s(buf, L"Setting priority %s for %s.", GetPriorityText(dwPriorityClass), target);
	MessageBox(NULL, buf, L"Priority Manager Test Notification", 0);
}
