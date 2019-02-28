#pragma once
#include "SndFunc.h"

class Sound;

// デジタルフィルタ
class Filter
{
	friend Sound;
public:
	// コンストラクタ
	Filter(Sound* sound);
	// デストラクタ
	~Filter();

private:
	Filter(const Filter&) = delete;
	void operator=(const Filter&) = delete;

	// ローパスフィルタ
	void LowPass(void);

	// ハイパスフィルタ
	void HighPass(void);

	// バンドパスフィルタ
	void BandPass(void);

	// ノッチフィルタ
	void Notch(void);

	// オールパスフィルタ
	void AllPass(void);

	// 実行
	void Execution(std::vector<float>& input);


	// サウンド
	Sound* sound;

	// 入力値
	float input[2];

	// 出力
	float out[2];

	// フィルタ係数A
	float a[3];

	// フィルタ係数B
	float b[3];
};
