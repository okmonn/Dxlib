#include "SndLoader.h"
#include "SndFunc.h"
#include "../etc/Func.h"

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
		func::DebugLog("サウンド読み込み：失敗");
		return -1;
	}

	snd::RIFF riff{};
	snd::LoadRIFF(riff, file);

	snd::FMT fmt{};
	snd::LoadFMT(fmt, file);

	snd::DATA data{};
	snd::LoadDATA(data, file);

	info[fileName].sample  = fmt.sample;
	info[fileName].bit     = fmt.bit;
	info[fileName].channel = fmt.channel;

	wave[fileName] = std::make_shared<std::vector<float>>(data.size / (fmt.bit / 8));
	switch (fmt.bit)
	{
	case 8:
		snd::LoadWave8(*wave[fileName], file);
		break;
	case 16:
		snd::LoadWave16(*wave[fileName], file);
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
		info.erase(info.find(fileName));
		wave.erase(wave.find(fileName));
	}
}

// インスタンス変数取得
SndLoader & SndLoader::Get(void)
{
	static SndLoader instance;
	return instance;
}

// サウンド情報取得
snd::Info SndLoader::GetInfo(const std::string & fileName)
{
	if (info.find(fileName) == info.end())
	{
		return snd::Info();
	}

	return info[fileName];
}

// 波形データ取得
std::shared_ptr<std::vector<float>> SndLoader::GetWave(const std::string & fileName)
{
	if (wave.find(fileName) == wave.end())
	{
		return nullptr;
	}

	return wave[fileName];
}
