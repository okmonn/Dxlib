#pragma once
#include "SndFunc.h"
#include <memory>
#include <thread>

class VoiceCallback;
class Effector;
class Delay;
class Filter;

// �T�E���h
class Sound
{
public:
	// �T�E���h���
	snd::Info info;

	// �f�B�X�g�[�V�����i�n�[�h�N���b�s���O�j
	float distortion;

	// �{�����[��
	float volume;

	// �f�B���C�p�����[�^
	snd::Delay delayParam;

	// �R���v���b�T�p�����[�^
	snd::Compressor compressor;

	// �t�B���^�p�����[�^
	snd::FilterParam filterParam;

	// �g�`�f�[�^
	std::vector<float>wave;


	// �R���X�g���N�^
	Sound();
	Sound(const std::string& fileName);
	// �R�s�[�R���X�g���N�^
	Sound(const Sound& sound);
	// �f�X�g���N�^
	~Sound();

	// �ǂݍ���
	int Load(const std::string& fileName);

	// ���[�p�X�t�B���^
	void LowPass(void);

	// �n�C�p�X�t�B���^
	void HighPass(void);

	// �o���h�p�X
	void BandPass(void);

	// �Đ�
	long Play(const bool& loop = false);

	// ��~
	long Stop(void) const;

	// 1�񏈗�����f�[�^�p�I�t�Z�b�g
	inline constexpr uint Offset(void) const;

	// ���Z�q�I�[�o�[���[�h
	void operator=(const Sound& sound);

private:
	// �\�[�X�{�C�X����
	long CreateVoice(void);

	// �t�@�C���ǂݍ��݃f�[�^�񓯊�
	void StreamFile(void);


	// �{�C�X�R�[���o�b�N
	std::unique_ptr<VoiceCallback>back;

	// �G�t�F�N�^�[
	std::unique_ptr<Effector>effe;

	// �f�B���C
	std::unique_ptr<Delay>delay;

	// �t�B���^
	std::unique_ptr<Filter>filter;

	// �\�[�X�{�C�X
	IXAudio2SourceVoice* voice;

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
};
