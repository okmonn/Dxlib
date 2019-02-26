#pragma once
#include <xaudio2.h>
#include <tchar.h>

#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }
#define Destroy(X) { if((X) != nullptr) (X)->DestroyVoice(); (X) = nullptr; }

class Sound;

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

	void STDMETHODCALLTYPE OnStreamEnd() {
	}
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() {
	}
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(unsigned int SamplesRequired) {
	}
	void STDMETHODCALLTYPE OnBufferEnd(void * pBufferContext) {
		SetEvent(handle);
	}
	void STDMETHODCALLTYPE OnBufferStart(void * pBufferContext) {
	}
	void STDMETHODCALLTYPE OnLoopEnd(void * pBufferContext) {
	}
	void STDMETHODCALLTYPE OnVoiceError(void * pBufferContext, long Error) {
	}


private:
	// イベントハンドル
	void* handle;
};
