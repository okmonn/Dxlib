#include "XAudio2.h"
#include "VoiceCallback.h"
#include "../etc/Func.h"

// �R���X�g���N�^
XAudio2::XAudio2() : 
	audio(nullptr), mastering(nullptr)
{
	Init();
}

// �f�X�g���N�^
XAudio2::~XAudio2()
{
	Destroy(mastering);
	Release(audio);
	CoUninitialize();
}

// COM������
long XAudio2::InitCom(void)
{
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
		func::DebugLog("COM�������F���s");
	}

	return hr;
}

// �I�[�f�B�I����
long XAudio2::CreateAudio(void)
{
	auto hr = XAudio2Create(&audio);
	if (FAILED(hr))
	{
		func::DebugLog("�I�[�f�B�I�����F���s");
	}

	return hr;
}

// �}�X�^�����O����
long XAudio2::CreateMastering(void)
{
	auto hr = audio->CreateMasteringVoice(&mastering);
	if (FAILED(hr))
	{
		func::DebugLog("�}�X�^�����O�����F���s");
	}

	return hr;
}

// ������
void XAudio2::Init(void)
{
	InitCom();
	CreateAudio();
	CreateMastering();
}

// �C���X�^���X�ϐ��擾
XAudio2 & XAudio2::Get(void)
{
	static XAudio2 instance;
	return instance;
}

// �I�[�f�B�I�擾
IXAudio2 * XAudio2::GetAudio(void) const
{
	return audio;
}
