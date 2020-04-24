#include "pch.h"
#include "Registry.h"

namespace Registry {
	void SetRegValue_Simple(HKEY hk, String name, uint32_t type, CX::Reflection::PVAccessor& acc)
	{
		RegSetValueEx(hk, name.c_str(), 0, type, (BYTE*)acc.data(), (DWORD)acc.size());
	}

	void Write(HKEY hRootKey, const String& path, CX::Reflection::Reflected& val)
	{
		HKEY hk;
		RegCreateKeyEx(hRootKey, path.c_str(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hk, nullptr);
		for (auto& p : val.properties())
		{
			if (p.is<Dword>())
				SetRegValue_Simple(hk, STConvert(p.name()), REG_DWORD, p);
			else if (p.is<Qword>())
				SetRegValue_Simple(hk, STConvert(p.name()), REG_QWORD, p);
			else if (p.is<String>())
			{
				auto s = p.as<String>();
				RegSetValueEx(hk, STConvert(p.name()).c_str(), 0, REG_SZ, (BYTE*)s.c_str(), (DWORD)s.length() * sizeof(String::value_type));
			}
			else if (p.is<MultiString>())
			{
				throw std::invalid_argument("MultiStrings not implemented");
			}
			else
			{
				SetRegValue_Simple(hk, STConvert(p.name()), REG_BINARY, p);
			}
		}
		RegCloseKey(hk);
	}

	void Read(HKEY hRootKey, const String& path, CX::Reflection::Reflected& val)
	{
		HKEY hk;
		RegCreateKeyEx(hRootKey, path.c_str(), 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &hk, nullptr);
		for (auto& p : val.properties())
		{
			if (p.is<String>())
			{
				DWORD readSize;
				RegQueryValueEx(hk, STConvert(p.name()).c_str(), nullptr, nullptr, nullptr, &readSize);

				if (!readSize)
					continue;

				String s;
				s.reserve(readSize);
				RegQueryValueEx(hk, STConvert(p.name()).c_str(), nullptr, nullptr, (BYTE*)s.data(), &readSize);

				p.as<String>() = std::move(s);
			}
			else
			{
				size_t expectedSize = p.size();
				DWORD readSize;
				RegQueryValueEx(hk, STConvert(p.name()).c_str(), nullptr, nullptr, nullptr, &readSize);
				if (expectedSize != readSize)
					continue; // wrong value

				RegQueryValueEx(hk, STConvert(p.name()).c_str(), nullptr, nullptr, (BYTE*)p.data(), &readSize);
			}
		}
		RegCloseKey(hk);
	}
}