#pragma once
#include "SndFunc.h"
#include <memory>
#include <thread>

class VoiceCallback;
class Effector;
class Delay;
class Filter;

// サウンド
class Sound
{
public:
	// サウンド情報
	snd::Info info;

	// ディストーション（ハードクリッピング）
	float distortion;

	// コンプレッサパラメータ
	snd::Compressor compressor;

	// パン
	float pan;

	// ボリューム
	float volume;

	// ディレイパラメータ
	snd::Delay delayParam;

	// フィルタパラメータ
	snd::FilterParam filterParam;


	// コンストラクタ
	Sound();
	Sound(const std::string& fileName);
	// コピーコンストラクタ
	Sound(const Sound& sound);
	// デストラクタ
	~Sound();

	// 読み込み
	int Load(const std::string& fileName);

	// ローパスフィルタ
	void LowPass(void);

	// ハイパスフィルタ
	void HighPass(void);

	// バンドパス
	void BandPass(void);

	// 再生
	long Play(const bool& loop = false);

	// 停止
	long Stop(void) const;

	// 1回処理するデータ用オフセット
	inline constexpr uint Offset(void) const;

	// 現在の波形データ取得
	inline std::vector<float> GetWave(void) const;

	// 演算子オーバーロード
	void operator=(const Sound& sound);

private:
	// ソースボイス生成
	long CreateVoice(void);

	// ファイル読み込みデータ非同期
	void StreamFile(void);


	// ボイスコールバック
	std::unique_ptr<VoiceCallback>back;

	// エフェクター
	std::unique_ptr<Effector>effe;

	// ディレイ
	std::unique_ptr<Delay>delay;

	// フィルタ
	std::unique_ptr<Filter>filter;

	// ソースボイス
	IXAudio2SourceVoice* voice;

	// 配列用インデックス
	uint index;

	// 読み込み位置
	uint read;

	// ループフラグ
	bool loop;

	// スレッドフラグ
	bool threadFlag;

	// ファイル名
	std::string fileName;

	// スレッド
	std::thread th;

	// 波形データ
	std::vector<std::vector<float>>wave;
};
