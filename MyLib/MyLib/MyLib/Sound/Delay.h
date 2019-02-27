#pragma once
#include "SndFunc.h"

class Sound;

// �f�B���C
class Delay
{
public:
	// �R���X�g���N�^
	Delay(Sound* sound);
	// �f�X�g���N�^
	~Delay();

	// ���s
	void Execution(std::vector<float>& input, const uint& offset);

	// �ߋ��f�[�^�N���A
	void Clear(void);

private:
	Delay(const Delay&) = delete;
	void operator=(const Delay&) = delete;


	// �T�E���h
	Sound* sound;

	// �ߋ��f�[�^
	std::vector<float>old;
};
