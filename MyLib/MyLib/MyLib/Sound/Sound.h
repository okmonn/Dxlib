#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
#include <memory>
#include <thread>

class VoiceCallback;

class Sound
{
public:
	// �T���v�����O���g��
	uint sample;

	// �ʎq���r�b�g��
	uint bit;

	// �`�����l����
	uint channel;


	// �R���X�g���N�^
	Sound();
	// �f�X�g���N�^
	~Sound();

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �Đ�
	long Play(const bool& loop = false);

	// ��~
	long Stop(void);

private:
	// �\�[�X�{�C�X����
	long CreateVoice(void);

	// �t�@�C���ǂݍ��݃f�[�^�񓯊�
	void StreamFile(void);


	// �{�C�X�R�[���o�b�N
	std::unique_ptr<VoiceCallback>back;

	// �\�[�X�{�C�X
	IXAudio2SourceVoice* voice;

	// �z��؂�ւ��C���f�b�N�X
	uint index;

	// �ǂݍ��݈ʒu
	uint read;

	// ���[�v�t���O
	bool loop;

	// �X���b�h�t���O
	bool threadFlag;

	// �t�@�C����
	std::string fileName;

	// �X���b�h
	std::thread th;

	// �g�`�f�[�^
	std::vector<std::vector<float>>wave;
};
