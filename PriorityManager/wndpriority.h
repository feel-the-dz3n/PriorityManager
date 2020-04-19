#pragma once

#include "pch.h"

VOID GetForegroundWindowProcessId(HWND* hwndptr, LPDWORD processid);
VOID GetForegroundWindowOpenProcess(HWND* hwndptr, HANDLE* hProcess);
BOOL ForegroundSetPriority(DWORD dwPriorityClass);
BOOL ForegroundIncreasePriority();
BOOL ForegroundDecreasePriority();
DWORD ForegroundGetPriority();
