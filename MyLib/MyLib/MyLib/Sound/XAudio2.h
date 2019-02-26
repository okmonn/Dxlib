#pragma once
#include "../etc/Define.h"

class XAudio2
{
public:
	// デストラクタ
	~XAudio2();

	// インスタンス変数取得
	static XAudio2& Get(void);
	// オーディオ取得
	IXAudio2* GetAudio(void) const;

private:
	// コンストラクタ
	XAudio2();
	XAudio2(const XAudio2&) = delete;
	void operator=(const XAudio2&) = delete;

	// COM初期化
	long InitCom(void);

	// オーディオ生成
	long CreateAudio(void);

	// マスタリング生成
	long CreateMastering(void);

	// 初期化
	void Init(void);


	// オーディオ
	IXAudio2* audio;

	// マスタリング
	IXAudio2MasteringVoice* mastering;
};
