#pragma once
#include <string>

namespace func
{
	// 円周率取得
	inline constexpr float PI(void);

	// ラジアン変換
	float Rad(const float& angle);

	// 文字コード変換
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);
}
