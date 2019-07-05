#include "stdafx.h"

std::wstring a2w(const std::string &str, unsigned int codePage /*= CP_ACP*/)
{
	const int nSize = MultiByteToWideChar(codePage, 0, str.c_str(), str.size(), nullptr, 0);
	if (nSize <= 0) return L"";

	std::wstring wstr(nSize, L'\0');
	MultiByteToWideChar(codePage, 0, str.c_str(), str.size(), &wstr[0], wstr.size());
	if (wstr[0] == 0xFEFF)
	{
		wstr.erase();
	}

	return wstr;
}

std::string w2a(const std::wstring &wstr, unsigned int codePage /*= CP_ACP*/)
{
	const int nSize = WideCharToMultiByte(codePage, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
	if (nSize <= 0) return "";

	std::string str(nSize, '\0');
	WideCharToMultiByte(codePage, 0, wstr.c_str(), wstr.size(), &str[0], str.size(), nullptr, nullptr);

	return str;
}

std::string i2s(int num)
{
	return std::to_string( (long long)num );
}

void showErrorMsg(TICModule module, int code, const char* desc)
{
	CString str;
	str.Format(_T("Ä£¿é: %d ´íÎóÂë: %d ´íÎóÐÅÏ¢: %s"), module, code, a2w(desc).c_str());
	AfxMessageBox(str, MB_OK);
}
