#include "pch.h"
#include "CXFramework/Reflection.h"

Settings& Settings::Instance()
{
	static Settings _inst;
	return _inst;
}

void Settings::Load()
{
	Registry::Read(HKEY_CURRENT_USER, Registry::STConvert("Software\\PriorityManager"), *this);
}

void Settings::Save()
{
	Registry::Write(HKEY_CURRENT_USER, Registry::STConvert("Software\\PriorityManager"), *this);
}
