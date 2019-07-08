#include "Func.h"
#include <vector>
#include <random>
#include <Windows.h>

// マルチバイト文字をユニコード文字に変換
std::wstring okmonn::ChangeCode(const std::string& code)
{
	std::vector<wchar_t>buf(MultiByteToWideChar(CP_ACP, 0, code.c_str(), -1, nullptr, 0));
	MultiByteToWideChar(CP_ACP, 0, code.c_str(), -1, &buf.front(), int(buf.size()));

	return std::wstring(buf.begin(), buf.end());
}

// ユニコード文字をマルチバイト文字に変換
std::string okmonn::ChangeCode(const std::wstring& code)
{
	//サイズの取得
	auto byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str;
	str.resize(byteSize);

	//変換
	byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), static_cast<int>(code.size()), &str[0], byteSize, nullptr, nullptr);

	return str;
}

// 円周率
float okmonn::PI(void)
{
	return 3.14159265f;
}

// ラジアン角度変換
template <typename T>
T okmonn::Rad(const T& angle)
{
	return T(angle * PI() / 180.0f);
}
template float okmonn::Rad(const float&);
template double okmonn::Rad(const double&);

// 弧度法角度変換
template<typename T>
T okmonn::Angle(const T& rad)
{
	return T(rad * 180.0f * PI());
}
template float okmonn::Angle(const float&);
template double okmonn::Angle(const double&);

// ランダム
int okmonn::Random(const int& min, const int& max)
{
	std::random_device dev;
#ifdef _WIN64
	std::mt19937_64 mt(dev());
#else
	std::mt19937 mt(dev());
#endif
	std::uniform_int_distribution<int>dist(min, max);

	return dist(mt);
}

// ランダム
template <typename T>
T okmonn::Random(const T& min, const T& max)
{
	std::random_device dev;
#ifdef _WIN64
	std::mt19937_64 mt(dev());
#else
	std::mt19937 mt(dev());
#endif
	std::uniform_real_distribution<T>dist(min, max);

	return dist(mt);
}
template float okmonn::Random(const float&, const float&);
template double okmonn::Random(const double&, const double&);
