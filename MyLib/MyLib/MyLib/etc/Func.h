#pragma once
#include <string>

namespace func
{
	// デバッグログ出力
	void DebugLog(const std::string& log);

	// 円周率取得
	inline constexpr float PI(void);

	// ラジアン変換
	float Rad(const float& angle);

	// 文字コード変換
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);

	// 文字列検索
	bool FindChara(const char* input, const std::string& find);
	bool FindChara(const unsigned char* input, const std::string& find);
}
