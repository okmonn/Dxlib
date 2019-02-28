#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>

namespace snd
{
	// RIFF
	struct RIFF {
		//ID
		unsigned char id[4];
		//サイズ
		long size;
		//タイプ
		unsigned char type[4];
	};

	// FMT
	struct FMT {
		//ID
		unsigned char id[4];
		//サイズ
		long size;
		//タイプ
		short type;
		//チャンネル
		short channel;
		//サンプリング周波数
		long sample;
		//バイト
		long byte;
		//ブロックサイズ
		short block;
		//量子化ビット数
		short bit;
	};

	// DATA
	struct DATA {
		//ID
		std::string id;
		//サイズ
		long size;
	};

	// サウンド情報
	struct Info {
		//サンプリング周波数
		uint sample;
		//量子化ビット数
		uint bit;
		//チャンネル数
		uint channel;
	};
	
	// コンプレッサパラメータ
	struct Compressor {
		//閾値
		float threshold;
		//レシオ
		float ratio;
	};

	// ディレイパラメータ
	struct Delay {
		//減衰率
		float decay;
		//遅延時間
		float time;
		//ループ回数
		uint loop;
	};

	// フィルタパラメータ
	struct FilterParam {
		//カットオフ周波数
		float cutoff;
		//クオリティファクタ・帯域幅
		float bw;
	};


	// RIFFの読み込み
	int LoadRIFF(RIFF& riff, FILE* file);

	// FMTの読み込み
	int LoadFMT(FMT& fmt, FILE* file);

	// DATAの読み込み
	int LoadDATA(DATA& data, FILE* file);

	// 8ビット波形の読み込み
	int LoadWave8(std::vector<float>& data, FILE* file);

	// 16ビット波形の読み込み
	int LoadWave16(std::vector<float>& data, FILE* file);
}
