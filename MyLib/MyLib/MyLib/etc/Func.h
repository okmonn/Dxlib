#pragma once
#include "../Math/Vector3.h"
#include <string>
#include <vector>

namespace func
{
	// デバッグログ出力
	void DebugLog(const std::string& log);

	// 円周率取得
	inline constexpr float PI(void);

	// ラジアン変換
	inline constexpr float Rad(const float& angle);

	// メインディスプレイ解像度取得
	inline Vec2 GetDisplayResolution(void);

	// 文字コード変換
	std::wstring ChangeCode(const std::string& code);
	std::string ChangeCode(const std::wstring& code);

	// 文字列検索
	bool FindChara(const char* input, const std::string& find);
	bool FindChara(const unsigned char* input, const std::string& find);

	// 任意の桁から切り上げ
	float Ceil(const float& i, const int& num);

	// 任意の桁から切り捨て
	float Floor(const float& i, const int& num);

	// 任意の桁から四捨五入
	float Round(const float& i, const int& num);

	// ハニング窓
	inline constexpr float Haninng(const unsigned int& index, const size_t& num);

	// 離散フーリエ変換
	void DFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag);

	// 逆離散フーリエ変換
	std::vector<float> IDFT(const std::vector<float>& real, const std::vector<float>& imag);

	// 高速フーリエ変換
	void FFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag);

	// 逆高速フーリエ変換
	std::vector<float> IFFT(const std::vector<float>& real, const std::vector<float>& imag, const unsigned int& outNum);

	// 振幅取得
	inline float Amplitude(const float& real, const float& imag);

	// 位相取得
	inline float Phase(const float& real, const float& imag);
}
