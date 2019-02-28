#pragma once
#include "SndFunc.h"

class Sound;

// �f�W�^���t�B���^
class Filter
{
	friend Sound;
public:
	// �R���X�g���N�^
	Filter(Sound* sound);
	// �f�X�g���N�^
	~Filter();

private:
	Filter(const Filter&) = delete;
	void operator=(const Filter&) = delete;

	// ���[�p�X�t�B���^
	void LowPass(void);

	// �n�C�p�X�t�B���^
	void HighPass(void);

	// �o���h�p�X�t�B���^
	void BandPass(void);

	// �m�b�`�t�B���^
	void Notch(void);

	// �I�[���p�X�t�B���^
	void AllPass(void);

	// ���s
	void Execution(std::vector<float>& input);


	// �T�E���h
	Sound* sound;

	// ���͒l
	float input[2];

	// �o��
	float out[2];

	// �t�B���^�W��A
	float a[3];

	// �t�B���^�W��B
	float b[3];
};
