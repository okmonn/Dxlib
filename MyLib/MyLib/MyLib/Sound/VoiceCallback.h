#pragma once
#include <xaudio2.h>

#define Release(X) { if((X) != nullptr) (X)->Release(); (X) = nullptr; }
#define Destroy(X) { if((X) != nullptr) (X)->DestroyVoice(); (X) = nullptr; }

class Sound;

// �T�E���h�R�[���o�b�N
class VoiceCallback :
	public IXAudio2VoiceCallback
{
	friend Sound;
public:
	// �R���X�g���N�^
	VoiceCallback() {
		handle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
	}
	// �f�X�g���N�^
	~VoiceCallback() {
		CloseHandle(handle);
	}
	
	// �V�����o�b�t�@�̏����J�n���ɌĂяo��
	void __stdcall OnBufferStart(void* pBufferContext) {
	}
	// �o�b�t�@�̏����I�����ɌĂяo��
	void __stdcall OnBufferEnd(void* pBufferContext) {
		SetEvent(handle);
	}
	// �f�[�^�ǂݍ��ݑO�ɌĂяo��
	void __stdcall OnVoiceProcessingPassStart(unsigned int SamplesRequired) {
	}
	// �����̏����p�X�I�����ɌĂяo��
	void __stdcall OnVoiceProcessingPassEnd() {
	}
	// �A�������X�g���[���Đ��I�����ɌĂяo��
	void __stdcall OnStreamEnd() {
	}
	// ���[�v�I���ʒu���B���ɌĂяo��
	void __stdcall OnLoopEnd(void* pBufferContext) {
	}
	// �G���[�������ɌĂяo��
	void __stdcall OnVoiceError(void* pBufferContext, long Error) {
	}

private:
	// �C�x���g�n���h��
	void* handle;
};
