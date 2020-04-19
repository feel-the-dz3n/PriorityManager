#include "pch.h"

LPCWSTR GetPriorityText(DWORD dwPriorityClass)
{
	switch (dwPriorityClass)
	{
	case IDLE_PRIORITY_CLASS: return L"Idle";
	case BELOW_NORMAL_PRIORITY_CLASS: return L"Below normal";
	case NORMAL_PRIORITY_CLASS: return L"Normal (default)";
	case ABOVE_NORMAL_PRIORITY_CLASS: return L"Above normal";
	case HIGH_PRIORITY_CLASS: return L"High";
	case REALTIME_PRIORITY_CLASS: return L"Realtime (unsafe)";
	default: return L"Unknown";
	}
}

DWORD GetNextPriority(DWORD dwPriorityClass, BOOL bRepeat)
{
	switch (dwPriorityClass)
	{
	case IDLE_PRIORITY_CLASS: return BELOW_NORMAL_PRIORITY_CLASS;
	case BELOW_NORMAL_PRIORITY_CLASS: return NORMAL_PRIORITY_CLASS;
	case NORMAL_PRIORITY_CLASS: return ABOVE_NORMAL_PRIORITY_CLASS;
	case ABOVE_NORMAL_PRIORITY_CLASS: return HIGH_PRIORITY_CLASS;
	case HIGH_PRIORITY_CLASS: return REALTIME_PRIORITY_CLASS;
	case REALTIME_PRIORITY_CLASS: return bRepeat ? IDLE_PRIORITY_CLASS : REALTIME_PRIORITY_CLASS;
	default: return NORMAL_PRIORITY_CLASS;
	}
}

DWORD GetPrevPriority(DWORD dwPriorityClass, BOOL bRepeat)
{
	switch (dwPriorityClass)
	{
	case IDLE_PRIORITY_CLASS: return bRepeat ? REALTIME_PRIORITY_CLASS : IDLE_PRIORITY_CLASS;
	case BELOW_NORMAL_PRIORITY_CLASS: return IDLE_PRIORITY_CLASS;
	case NORMAL_PRIORITY_CLASS: return BELOW_NORMAL_PRIORITY_CLASS;
	case ABOVE_NORMAL_PRIORITY_CLASS: return NORMAL_PRIORITY_CLASS;
	case HIGH_PRIORITY_CLASS: return ABOVE_NORMAL_PRIORITY_CLASS;
	case REALTIME_PRIORITY_CLASS: return HIGH_PRIORITY_CLASS;
	default: return NORMAL_PRIORITY_CLASS;
	}
}
