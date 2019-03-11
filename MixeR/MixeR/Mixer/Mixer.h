#pragma once
#include <vector>
#include <memory>
#include <thread>

class MyLib;
class Texture;
class Sound;
class Mouse;
class ParamMane;
class Waves;
class DFT;

// 心臓部分
class Mixer
{
public:
	// コンストラクタ
	Mixer();
	// デストラクタ
	~Mixer();

	// 処理
	void Run(void);

private:
	Mixer(const Mixer&) = delete;
	void operator=(const Mixer&) = delete;

	// リセット
	void Reset(void);

	// 処理
	void UpData(void);

	// 再生・停止
	void PlayAndStop(void);

	// 波形描画
	void DrawWaves(void);

	// 振幅
	void DrawAmp(void);


	// ライブラリ
	std::shared_ptr<MyLib>lib;

	// サウンド
	std::shared_ptr<Sound>sound;

	// マウス
	std::shared_ptr<Mouse>mouse;

	// パラメータ
	std::unique_ptr<ParamMane>param;

	// ウェーブ
	std::unique_ptr<Waves>wave;

	// フーリエ変換
	std::unique_ptr<DFT>dft;

	// 再生フラグ
	bool play;

	// スレッドフラグ
	bool threadFlag;

	// スレッド
	std::vector<std::thread>th;
};
