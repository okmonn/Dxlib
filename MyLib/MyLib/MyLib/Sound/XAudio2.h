#pragma once
#include "../etc/Define.h"

class XAudio2
{
public:
	// �f�X�g���N�^
	~XAudio2();

	// �C���X�^���X�ϐ��擾
	static XAudio2& Get(void);
	// �I�[�f�B�I�擾
	IXAudio2* GetAudio(void) const;

private:
	// �R���X�g���N�^
	XAudio2();
	XAudio2(const XAudio2&) = delete;
	void operator=(const XAudio2&) = delete;

	// COM������
	long InitCom(void);

	// �I�[�f�B�I����
	long CreateAudio(void);

	// �}�X�^�����O����
	long CreateMastering(void);

	// ������
	void Init(void);


	// �I�[�f�B�I
	IXAudio2* audio;

	// �}�X�^�����O
	IXAudio2MasteringVoice* mastering;
};
