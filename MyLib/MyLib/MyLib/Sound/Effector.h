#pragma once
#include "SndFunc.h"
#include <memory>

class Compute;
class Sound;

// �T�E���h�G�t�F�N�^�[
class Effector
{
	// �G�t�F�N�g�p�����[�^
	struct Param {
		// �f�B�X�g�[�V����
		float distortion;
		//�R���v���b�T
		snd::Compressor comp;
		//�p��
		float pan;
		//����
		float volume;
	};

public:
	// �R���X�g���N�^
	Effector(Sound* sound);
	// �f�X�g���N�^
	~Effector();

	// ���s
	void Execution(std::vector<float>& input);

private:
	Effector(const Effector&) = delete;
	void operator=(const Effector&) = delete;

	// ������
	void Init(void);


	// �T�E���h
	Sound* sound;

	// �R���s���[�g
	std::unique_ptr<Compute>compute;

	// �G�t�F�N�g�p�����[�^
	Param param;
};
