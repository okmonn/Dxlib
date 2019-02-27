#pragma once
#include "SndFunc.h"

class Sound;

// ディレイ
class Delay
{
public:
	// コンストラクタ
	Delay(Sound* sound);
	// デストラクタ
	~Delay();

	// 実行
	void Execution(const uint& offset);

	// 過去データクリア
	void Clear(void);

private:
	Delay(const Delay&) = delete;
	void operator=(const Delay&) = delete;


	// サウンド
	Sound* sound;

	// 過去データ
	//std::vector<float>old;
	std::vector<std::vector<float>>old;
};
