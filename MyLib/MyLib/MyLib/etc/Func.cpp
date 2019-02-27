#include "Func.h"
#include <Windows.h>

// デバッグログ出力
void func::DebugLog(const std::string & log)
{
#ifdef _DEBUG
	std::string tmp = "\n" + log + "\n";
	OutputDebugStringA(tmp.c_str());
#endif
}

// 円周率取得
inline constexpr float func::PI(void)
{
	return 3.14159265358979323846f;
}

// ラジアン変換
inline constexpr float func::Rad(const float & angle)
{
	return angle * PI() / 180.0f;
}

// メインディスプレイ解像度取得
inline Vec2 func::GetDisplayResolution(void)
{
	return Vec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

// 文字コード変換
std::wstring func::ChangeCode(const std::string& code)
{
	//サイズの取得
	auto byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, nullptr, 0);

	std::wstring wstr;
	wstr.resize(byteSize);

	//変換
	byteSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, code.c_str(), -1, &wstr[0], byteSize);

	return wstr;
}

// 文字コード変換
std::string func::ChangeCode(const std::wstring& code)
{
	//サイズの取得
	auto byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), -1, nullptr, 0, nullptr, nullptr);

	std::string str;
	str.resize(byteSize);

	//変換
	byteSize = WideCharToMultiByte(CP_ACP, 0, code.c_str(), static_cast<int>(code.size()), &str[0], byteSize, nullptr, nullptr);

	return str;
}

// 文字列検索
bool func::FindChara(const char* input, const std::string& find)
{
	if (input == nullptr)
	{
		return false;
	}

	std::string tmp = input;
	if (tmp.find(find) == std::string::npos)
	{
		return false;
	}

	return true;
}

// 文字列検索
bool func::FindChara(const unsigned char* input, const std::string& find)
{
	if (input == nullptr)
	{
		return false;
	}

	std::string tmp = (char*)(input);
	if (tmp.find(find) == std::string::npos)
	{
		return false;
	}

	return true;
}

// 任意の桁から切り上げ
float func::Ceil(const float& i, const int& num)
{
	float tmp = i;
	tmp *= std::pow(10.0f, -num - 1);
	tmp  = std::ceil(tmp);
	tmp *= std::pow(10.0f, num + 1);

	return tmp;
}

// 任意の桁から切り捨て
float func::Floor(const float& i, const int& num)
{
	float tmp = i;
	tmp *= std::pow(10.0f, -num - 1);
	tmp  = std::floor(tmp);
	tmp *= std::pow(10.0f, num + 1);

	return tmp;
}

// 任意の桁から四捨五入
float func::Round(const float& i, const int& num)
{
	float tmp = i;
	tmp *= std::pow(10.0f, -num - 1);
	tmp  = std::floor(tmp + 0.5f);
	tmp *= std::pow(10.0f, num + 1);

	return tmp;
}

// ハニング窓
inline constexpr float func::Haninng(const unsigned int& index, const size_t& num)
{
	return (num % 2 == 0)
		? 0.5f - 0.5f * std::cos(2.0f * func::PI() * index / num)
		: 0.5f - 0.5f * std::cos(2.0f * func::PI() * (index + 0.5f) / num);
}

// 離散フーリエ変換
void func::DFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag)
{
	real.assign(input.size(), 0.0f);
	imag.assign(input.size(), 0.0f);
	for (unsigned int i = 0; i < input.size(); ++i)
	{
		for (unsigned int n = 0; n < input.size(); ++n)
		{
			auto re =  std::cos(2.0f * func::PI() * i * n / input.size());
			auto im = -std::sin(2.0f * func::PI() * i * n / input.size());

			real[i] += re * input[n];
			imag[i] += im * input[n];
		}
	}
}

// 逆離散フーリエ変換
std::vector<float> func::IDFT(const std::vector<float>& real, const std::vector<float>& imag)
{
	std::vector<float>adap(real.size(), 0.0f);
	for (unsigned int i = 0; i < adap.size(); ++i)
	{
		for (unsigned int n = 0; n < adap.size(); ++n)
		{
			auto re = std::cos(2.0f * func::PI() * i * n / real.size());
			auto im = std::sin(2.0f * func::PI() * i * n / imag.size());

			adap[i] += re * real[n] - im * imag[n];
		}
		adap[i] /= real.size();
	}

	return adap;
}

// 高速フーリエ変換
void func::FFT(const std::vector<float>& input, std::vector<float>& real, std::vector<float>& imag)
{
	unsigned int stage = unsigned int(std::ceil(log2(input.size())));
	unsigned int num   = unsigned int(std::pow(2, stage));

	real = input;
	real.resize(num, 0.0f);
	imag.resize(num, 0.0f);

	std::vector<unsigned int>index(num, 0);

	for (unsigned int st = 1; st <= stage; ++st)
	{
		for (unsigned int i = 0; i < unsigned int(std::pow(2, st - 1)); ++i)
		{
			for (unsigned int n = 0; n < unsigned int(std::pow(2, stage - st)); ++n)
			{
				unsigned int index1 = unsigned int(std::pow(2, stage - st + 1)) * i + n;
				unsigned int index2 = unsigned int(std::pow(2, stage - st)) + index1;

				auto p = std::pow(2.0f, float(st - 1)) * n;

				auto re0 =  real[index1];
				auto im0 =  imag[index1];
				auto re1 =  real[index2];
				auto im1 =  imag[index2];
				auto re2 =  std::cos(2.0f * func::PI() * p / num);
				auto im2 = -std::sin(2.0f * func::PI() * p / num);

				real[index1] = re0 + re1;
				imag[index1] = im0 + im1;
				if (st < stage)
				{
					real[index2] = (re0 - re1) * re2 - (im0 - im1) * im2;
					imag[index2] = (im0 - im1) * re2 + (re0 - re1) * im2;
				}
				else
				{
					real[index2] = re0 - re1;
					imag[index2] = im0 - im1;
				}
			}

			unsigned int m = unsigned int(std::pow(2, st - 1) + i);
			index[m] = index[i] + unsigned int(std::pow(2, stage - st));
		}
	}

	for (unsigned int i = 0; i < index.size(); ++i)
	{
		if (index[i] > i)
		{
			std::swap(real[index[i]], real[i]);
			std::swap(imag[index[i]], imag[i]);
		}
	}
}

// 逆高速フーリエ変換
std::vector<float> func::IFFT(const std::vector<float>& real, const std::vector<float>& imag, const unsigned int& outNum)
{
	unsigned int stage = unsigned int(std::log2(real.size()));
	unsigned int num   = unsigned int(std::pow(2, stage));

	std::vector<float>re = real;
	std::vector<float>im = imag;
	std::vector<unsigned int>index(num, 0);

	for (unsigned int st = 1; st <= stage; ++st)
	{
		for (unsigned int i = 0; i < unsigned int(std::pow(2, st - 1)); ++i)
		{
			for (unsigned int n = 0; n < unsigned int(std::pow(2, stage - st)); ++n)
			{
				unsigned int index1 = unsigned int(std::pow(2, stage - st + 1)) * i + n;
				unsigned int index2 = unsigned int(std::pow(2, stage - st)) + index1;

				auto p = pow(2.0f, float(st - 1)) * n;

				auto re0 = re[index1];
				auto im0 = im[index1];
				auto re1 = re[index2];
				auto im1 = im[index2];
				auto re2 = std::cos(2.0f * func::PI() * p / num);
				auto im2 = std::sin(2.0f * func::PI() * p / num);

				re[index1] = re0 + re1;
				im[index1] = im0 + im1;
				if (st < stage)
				{
					re[index2] = (re0 - re1) * re2 - (im0 - im1) * im2;
					im[index2] = (im0 - im1) * re2 + (re0 - re1) * im2;
				}
				else
				{
					re[index2] = re0 - re1;
					im[index2] = im0 - im1;
				}
			}

			unsigned int m = unsigned int(std::pow(2, st - 1) + i);
			index[m] = index[i] + unsigned int(std::pow(2, stage - st));
		}
	}

	for (unsigned int n = 0; n < index.size(); ++n)
	{
		if (index[n] > n)
		{
			std::swap(re[index[n]], re[n]);
			std::swap(im[index[n]], im[n]);
		}
		re[n] /= num;
		im[n] /= num;
	}

	return std::vector<float>(&re[0], &re[outNum]);
}

// 振幅取得
inline float func::Amplitude(const float & real, const float & imag)
{
	return std::sqrt(real * real + imag * imag);
}

// 位相取得
inline float func::Phase(const float & real, const float & imag)
{
	return std::atan2(imag, real);
}
