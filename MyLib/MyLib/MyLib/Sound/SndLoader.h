#pragma once
#include "SndFunc.h"
#include <memory>
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
	// サウンド情報取得
	snd::Info GetInfo(const std::string& fileName);
	// 波形データ取得
	std::shared_ptr<std::vector<float>> GetWave(const std::string& fileName);

private:
	// コンストラクタ
	SndLoader();
	SndLoader(const SndLoader&) = delete;
	void operator=(const SndLoader&) = delete;


	// サウンド情報
	std::unordered_map<std::string, snd::Info>info;

	// 波形データ
	std::unordered_map<std::string, std::shared_ptr<std::vector<float>>>wave;
};
