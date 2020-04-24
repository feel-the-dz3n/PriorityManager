#pragma once
#include "pch.h"
#include <algorithm>
#include "CXFramework/Reflection.h"

namespace Registry
{
#ifdef UNICODE
	using _StringType = std::wstring;

	inline std::wstring STConvert(const std::string& src)
	{
		std::wstring tmp;
		tmp.resize(src.size());
		std::transform(src.begin(), src.end(), tmp.begin(), btowc);
		return tmp;
	}
#else
	using _StringType = std::string;
	inline std::string STConvert(const std::string& src)
	{
		return src;
	}
#endif

	using Dword = uint32_t;
	using Qword = uint64_t;
	using Bool = Dword;
	using String = _StringType;
	using MultiString = std::vector<_StringType>;

	void Write(HKEY hRootKey, const String& path, CX::Reflection::Reflected& val);
	void Read(HKEY hRootKey, const String& path, CX::Reflection::Reflected& val);
}