#pragma once

#include "pch.h"

LPCWSTR GetPriorityText(DWORD dwPriorityClass);
DWORD GetNextPriority(DWORD dwPriorityClass, BOOL bRepeat);
DWORD GetPrevPriority(DWORD dwPriorityClass, BOOL bRepeat);
