#pragma once
#include "SndFunc.h"
#include <memory>
#include <unordered_map>

// �T�E���h���[�_�[
class SndLoader
{
public:
	// �f�X�g���N�^
	~SndLoader();

	// �ǂݍ���
	int Load(const std::string& fileName);

	// �f�[�^�폜
	void Delete(const std::string& fileName);

	// �C���X�^���X�ϐ��擾
	static SndLoader& Get(void);
	// �T�E���h���擾
	snd::Info GetInfo(const std::string& fileName);
	// �g�`�f�[�^�擾
	std::shared_ptr<std::vector<float>> GetWave(const std::string& fileName);

private:
	// �R���X�g���N�^
	SndLoader();
	SndLoader(const SndLoader&) = delete;
	void operator=(const SndLoader&) = delete;


	// �T�E���h���
	std::unordered_map<std::string, snd::Info>info;

	// �g�`�f�[�^
	std::unordered_map<std::string, std::shared_ptr<std::vector<float>>>wave;
};
