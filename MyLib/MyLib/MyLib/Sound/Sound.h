#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <memory>
#include <thread>

class VoiceCallback;

class Sound
{
public:
	// サンプリング周波数
	uint sample;

	// 量子化ビット数
	uint bit;

	// チャンネル数
	uint channel;


	// コンストラクタ
	Sound();
	// デストラクタ
	~Sound();

	// 読み込み
	int Load(const std::string& fileName);

	// 再生
	long Play(const bool& loop = false);

	// 停止
	long Stop(void);

private:
	// ソースボイス生成
	long CreateVoice(void);

	// ファイル読み込みデータ非同期
	void StreamFile(void);


	// ボイスコールバック
	std::unique_ptr<VoiceCallback>back;

	// ソースボイス
	IXAudio2SourceVoice* voice;

	// 配列切り替えインデックス
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
