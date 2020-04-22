#pragma once
#include "pch.h"
#include "CXFramework/Reflection.h"

struct Settings
{
	BOOL EnableHotFore = FALSE;
	BOOL EnableLiveIcon = TRUE;
	BOOL EnableDefaultHotkeys = TRUE;

	static Settings& Instance();
	void Load();
	void Save();

	cxprops(Settings) (
		property(EnableHotFore),
		property(EnableLiveIcon),
		property(EnableDefaultHotkeys)
		) cxprops_end;
};
