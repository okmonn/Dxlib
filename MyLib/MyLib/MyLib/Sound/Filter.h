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
	void LowPass(const snd::FilterParam& param, const snd::Info& info);

	// �n�C�p�X�t�B���^
	void HighPass(const snd::FilterParam& param, const snd::Info& info);

	// �o���h�p�X
	void BandPass(const snd::FilterParam& param, const snd::Info& info);

	// ���s
	void Execution(void);


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
