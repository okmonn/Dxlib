#pragma once
#include <string>

namespace func
{
	// 文字コード変換
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);
}
