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
		for (auto& i : handle)
		{
			i = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);
		}
	}
	// �f�X�g���N�^
	~VoiceCallback() {
		for (auto& i : handle)
		{
			CloseHandle(i);
		}
	}
	
	// �V�����o�b�t�@�̏����J�n���ɌĂяo��
	void __stdcall OnBufferStart(void* pBufferContext) {
		SetEvent(handle[0]);
	}
	// �o�b�t�@�̏����I�����ɌĂяo��
	void __stdcall OnBufferEnd(void* pBufferContext) {
		SetEvent(handle[1]);
	}
	// �f�[�^�ǂݍ��ݑO�ɌĂяo��
	void __stdcall OnVoiceProcessingPassStart(unsigned int SamplesRequired) {
		SetEvent(handle[2]);
	}
	// �����̏����p�X�I�����ɌĂяo��
	void __stdcall OnVoiceProcessingPassEnd() {
		SetEvent(handle[3]);
	}
	// �A�������X�g���[���Đ��I�����ɌĂяo��
	void __stdcall OnStreamEnd() {
		SetEvent(handle[4]);
	}
	// ���[�v�I���ʒu���B���ɌĂяo��
	void __stdcall OnLoopEnd(void* pBufferContext) {
		SetEvent(handle[5]);
	}
	// �G���[�������ɌĂяo��
	void __stdcall OnVoiceError(void* pBufferContext, long Error) {
		SetEvent(handle[6]);
	}

private:
	// �I��
	void End(void) {
		for (auto& i : handle)
		{
			SetEvent(i);
		}
	}


	// �C�x���g�n���h��
	void* handle[7];
};
