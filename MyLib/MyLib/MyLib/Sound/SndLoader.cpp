#include "SndLoader.h"
#include "SndFunc.h"
#include <Windows.h>
#include <tchar.h>

// コンストラクタ
SndLoader::SndLoader()
{
}

// デストラクタ
SndLoader::~SndLoader()
{
}

// 読み込み
int SndLoader::Load(const std::string & fileName)
{
	if (wave.find(fileName) != wave.end())
	{
		return 0;
	}

	FILE* file = nullptr;
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		OutputDebugString(_T("\nサウンド読み込み：失敗\n"));
		return -1;
	}

	snd::RIFF riff{};
	snd::LoadRIFF(riff, file);

	snd::FMT fmt{};
	snd::LoadFMT(fmt, file);

	snd::DATA data{};
	snd::LoadDATA(data, file);

	sample[fileName]  = fmt.sample;
	bit[fileName]     = fmt.bit;
	channel[fileName] = fmt.channel;

	wave[fileName].resize(data.size / 8);
	switch (fmt.bit)
	{
	case 8:
		snd::LoadWave8(wave[fileName], file);
		break;
	case 16:
		snd::LoadWave16(wave[fileName], file);
		break;
	default:
		break;
	}

	fclose(file);

	return 0;
}

// データ削除
void SndLoader::Delete(const std::string & fileName)
{
	if (wave.find(fileName) != wave.end())
	{
		sample.erase(sample.find(fileName));
		bit.erase(bit.find(fileName));
		channel.erase(channel.find(fileName));
		wave.erase(wave.find(fileName));
	}
}

// インスタンス変数取得
SndLoader & SndLoader::Get(void)
{
	static SndLoader instance;
	return instance;
}

// サンプリング周波数取得
uint SndLoader::GetSample(const std::string & fileName)
{
	if (sample.find(fileName) == sample.end())
	{
		return uint();
	}

	return  sample[fileName];
}

// 量子化ビット数取得
uint SndLoader::GetBit(const std::string & fileName)
{
	if (bit.find(fileName) == bit.end())
	{
		return uint();
	}

	return bit[fileName];
}

// チャンネル数取得
uint SndLoader::GetChannel(const std::string & fileName)
{
	if (channel.find(fileName) == channel.end())
	{
		return uint();
	}

	return channel[fileName];
}

// 波形データ取得
std::vector<float> SndLoader::GetWave(const std::string & fileName)
{
	if (wave.find(fileName) == wave.end())
	{
		return std::vector<float>();
	}

	return wave[fileName];
}
