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
	void Execution(std::vector<float>& input, const uint& offset);

private:
	Delay(const Delay&) = delete;
	void operator=(const Delay&) = delete;


	// サウンド
	Sound* sound;

	// 遅延時間
	float time;

	// フェードインデックス
	uint index;

	// フェード範囲
	uint fade;
};
