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
	void LowPass(const snd::FilterParam& param, const snd::Info& info);

	// ハイパスフィルタ
	void HighPass(const snd::FilterParam& param, const snd::Info& info);

	// バンドパス
	void BandPass(const snd::FilterParam& param, const snd::Info& info);

	// 実行
	void Execution(void);


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
