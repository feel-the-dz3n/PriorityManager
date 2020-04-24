#pragma once
#include "pch.h"
#include "CXFramework/Reflection.h"
#include "Registry.h"

struct Settings : CX::Reflection::Reflected
{
	Settings() {
		EnableHotFore = false;
		EnableLiveIcon = true;
		EnableDefaultHotkeys = true;
		NotifyAboutChangingPriority = false;
		NotifyAboutChangingPriorityTimeout = 1000;
	}

	Registry::Bool cxprop(EnableHotFore);
	Registry::Bool cxprop(EnableLiveIcon);
	Registry::Bool cxprop(EnableDefaultHotkeys);
	Registry::Bool cxprop(NotifyAboutChangingPriority);
	Registry::Dword cxprop(NotifyAboutChangingPriorityTimeout);

	static Settings& Instance();
	void Load();
	void Save();
};
