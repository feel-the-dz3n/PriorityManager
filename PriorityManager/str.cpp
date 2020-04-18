// str.cpp : Contains string-related functions

#include "pch.h"

void string_to_wstring(const std::string& src, std::wstring& dest)
{
    std::wstring tmp;
    tmp.resize(src.size());
    std::transform(src.begin(), src.end(), tmp.begin(), btowc);
    tmp.swap(dest);
}

void wstring_to_string(const std::wstring& src, std::string& dest)
{
    std::string tmp;
    tmp.resize(src.size());
    std::transform(src.begin(), src.end(), tmp.begin(), wctob);
    tmp.swap(dest);
}
