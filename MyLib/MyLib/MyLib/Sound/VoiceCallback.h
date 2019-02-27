#pragma once
#include <xaudio2.h>

#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }
#define Destroy(X) { if((X) != nullptr) (X)->DestroyVoice(); (X) = nullptr; }

class Sound;

// サウンドコールバック
class VoiceCallback :
	public IXAudio2VoiceCallback
{
	friend Sound;
public:
	// コンストラクタ
	VoiceCallback() {
		for (auto& i : handle)
		{
			i = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
		}
	}
	// デストラクタ
	~VoiceCallback() {
		for (auto& i : handle)
		{
			CloseHandle(i);
		}
	}
	
	// 新しいバッファの処理開始時に呼び出し
	void __stdcall OnBufferStart(void* pBufferContext) {
		SetEvent(handle[0]);
	}
	// バッファの処理終了時に呼び出し
	void __stdcall OnBufferEnd(void* pBufferContext) {
		SetEvent(handle[1]);
	}
	// データ読み込み前に呼び出し
	void __stdcall OnVoiceProcessingPassStart(unsigned int SamplesRequired) {
		SetEvent(handle[2]);
	}
	// 音声の処理パス終了時に呼び出し
	void __stdcall OnVoiceProcessingPassEnd() {
		SetEvent(handle[3]);
	}
	// 連続したストリーム再生終了時に呼び出し
	void __stdcall OnStreamEnd() {
		SetEvent(handle[4]);
	}
	// ループ終了位置到達時に呼び出し
	void __stdcall OnLoopEnd(void* pBufferContext) {
		SetEvent(handle[5]);
	}
	// エラー発生時に呼び出し
	void __stdcall OnVoiceError(void* pBufferContext, long Error) {
		SetEvent(handle[6]);
	}

private:
	// 終了
	void End(void) {
		for (auto& i : handle)
		{
			SetEvent(i);
		}
	}


	// イベントハンドル
	void* handle[7];
};
