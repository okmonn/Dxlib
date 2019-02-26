#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <unordered_map>

// サウンドローダー
class SndLoader
{
public:
	// デストラクタ
	~SndLoader();

	// 読み込み
	int Load(const std::string& fileName);

	// データ削除
	void Delete(const std::string& fileName);

	// インスタンス変数取得
	static SndLoader& Get(void);
	// サンプリング周波数取得
	uint GetSample(const std::string& fileName);
	// 量子化ビット数取得
	uint GetBit(const std::string& fileName);
	// チャンネル数取得
	uint GetChannel(const std::string& fileName);
	// 波形データ取得
	std::vector<float> GetWave(const std::string& fileName);

private:
	// コンストラクタ
	SndLoader();
	SndLoader(const SndLoader&) = delete;
	void operator=(const SndLoader&) = delete;


	// サンプリング周波数
	std::unordered_map<std::string, uint>sample;

	// 量子化ビット数
	std::unordered_map<std::string, uint>bit;

	// チャンネル
	std::unordered_map<std::string, uint>channel;

	// 波形データ
	std::unordered_map<std::string, std::vector<float>>wave;
};
