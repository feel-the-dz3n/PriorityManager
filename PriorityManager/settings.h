#pragma once
#include "pch.h"
#include "CXFramework/Reflection.h"

struct Settings
{
	BOOL EnableHotFore = FALSE;
	BOOL EnableLiveIcon = TRUE;
	BOOL EnableDefaultHotkeys = TRUE;
	BOOL NotifyAboutChangingPriority = FALSE;
	UINT NotifyAboutChangingPriorityTimeout = 1000;

	static Settings& Instance();
	void Load();
	void Save();

	cxprops(Settings) (
		property(EnableHotFore),
		property(EnableLiveIcon),
		property(EnableDefaultHotkeys),
		property(NotifyAboutChangingPriority),
		property(NotifyAboutChangingPriorityTimeout)
		) cxprops_end;
};
