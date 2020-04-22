#pragma once

#if defined(WIN32)
#include <Windows.h>

static class _UnicodeEnabler {
public:
	_UnicodeEnabler() {
		SetConsoleOutputCP(65001);
	}
} _gUnicodeEnabler;
#endif