#include "pch.h"
#include "CXFramework/Reflection.h"

Settings& Settings::Instance()
{
	static Settings _inst;
	return _inst;
}

void Settings::Load()
{
	HKEY hk;
	if (RegOpenKey(HKEY_CURRENT_USER, L"Software\\PriorityManager", &hk) != ERROR_SUCCESS) return;

	cxenum(Settings, *this)
	{
		DWORD dummy;
		std::wstring wname;
		string_to_wstring(name.c_str(), wname);
		RegQueryValueEx(hk, wname.c_str(), nullptr, nullptr, (BYTE*)&value, &dummy);
		if (dummy != sizeof value) throw std::exception();
	} cxenum_end;

	RegCloseKey(hk);
}

void Settings::Save()
{
	HKEY hk;
	RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\PriorityManager", 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hk, nullptr);

	cxenum(Settings, *this)
	{
		std::wstring wname;
		string_to_wstring(name.c_str(), wname);
		RegSetKeyValue(hk, nullptr, wname.c_str(), REG_BINARY, &value, sizeof value);
	} cxenum_end;

	RegCloseKey(hk);
}
