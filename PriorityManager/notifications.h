#pragma once
#include "pch.h"

VOID NotifyPriorityChanged(LPCWSTR target, DWORD dwPriorityClass);
VOID NotifyPriorityChangeFailed(LPCWSTR target, DWORD dwPriorityClass, LPCWSTR szErrorMessage, BOOL bGetLastError);
LPWSTR GetPriorityClassIconId(DWORD dwPriorityClass);
