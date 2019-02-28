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
		handle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
	}
	// デストラクタ
	~VoiceCallback() {
		CloseHandle(handle);
	}
	
	// 新しいバッファの処理開始時に呼び出し
	void __stdcall OnBufferStart(void* pBufferContext) {
	}
	// バッファの処理終了時に呼び出し
	void __stdcall OnBufferEnd(void* pBufferContext) {
		SetEvent(handle);
	}
	// データ読み込み前に呼び出し
	void __stdcall OnVoiceProcessingPassStart(unsigned int SamplesRequired) {
	}
	// 音声の処理パス終了時に呼び出し
	void __stdcall OnVoiceProcessingPassEnd() {
	}
	// 連続したストリーム再生終了時に呼び出し
	void __stdcall OnStreamEnd() {
	}
	// ループ終了位置到達時に呼び出し
	void __stdcall OnLoopEnd(void* pBufferContext) {
	}
	// エラー発生時に呼び出し
	void __stdcall OnVoiceError(void* pBufferContext, long Error) {
	}

private:
	// イベントハンドル
	void* handle;
};
