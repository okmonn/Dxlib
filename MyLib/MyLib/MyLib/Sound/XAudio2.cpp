#include "XAudio2.h"
#include "VoiceCallback.h"

// コンストラクタ
XAudio2::XAudio2() : 
	audio(nullptr), mastering(nullptr)
{
	Init();
}

// デストラクタ
XAudio2::~XAudio2()
{
	Destroy(mastering);
	Release(audio);
	CoUninitialize();
}

// COM初期化
long XAudio2::InitCom(void)
{
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nCOM初期化：失敗\n"));
	}

	return hr;
}

// オーディオ生成
long XAudio2::CreateAudio(void)
{
	auto hr = XAudio2Create(&audio);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nオーディオ生成：失敗\n"));
	}

	return hr;
}

// マスタリング生成
long XAudio2::CreateMastering(void)
{
	auto hr = audio->CreateMasteringVoice(&mastering);
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nマスタリング生成：失敗\n"));
	}

	return hr;
}

// 初期化
void XAudio2::Init(void)
{
	InitCom();
	CreateAudio();
	CreateMastering();
}

// インスタンス変数取得
XAudio2 & XAudio2::Get(void)
{
	static XAudio2 instance;
	return instance;
}

// オーディオ取得
IXAudio2 * XAudio2::GetAudio(void) const
{
	return audio;
}
