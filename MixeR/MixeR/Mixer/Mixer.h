#pragma once
#include <vector>
#include <memory>
#include <thread>

class MyLib;
class Sound;
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

	// 波形描画
	void DrawWaves(void);

	// 振幅
	void DrawAmp(void);


	// ライブラリ
	std::shared_ptr<MyLib>lib;

	// サウンド
	std::shared_ptr<Sound>sound;

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
