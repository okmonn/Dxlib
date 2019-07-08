#pragma once
#include <string>

namespace okmonn
{
	// マルチバイト文字をユニコード文字に変換
	std::wstring ChangeCode(const std::string& code);

	// ユニコード文字をマルチバイト文字に変換
	std::string ChangeCode(const std::wstring& code);

	// 円周率
	float PI(void);

	// ラジアン角度変換
	template <typename T>
	T Rad(const T& angle);

	// 弧度法角度変換
	template <typename T>
	T Angle(const T& rad);

	// ランダム
	int Random(const int& min, const int& max);

	// ランダム
	template <typename T>
	T Random(const T& min, const T& max);
}
