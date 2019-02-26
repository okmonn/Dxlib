#pragma once
#include "../etc/Define.h"
#include <string>
#include <vector>
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
	// �T���v�����O���g���擾
	uint GetSample(const std::string& fileName);
	// �ʎq���r�b�g���擾
	uint GetBit(const std::string& fileName);
	// �`�����l�����擾
	uint GetChannel(const std::string& fileName);
	// �g�`�f�[�^�擾
	std::vector<float> GetWave(const std::string& fileName);

private:
	// �R���X�g���N�^
	SndLoader();
	SndLoader(const SndLoader&) = delete;
	void operator=(const SndLoader&) = delete;


	// �T���v�����O���g��
	std::unordered_map<std::string, uint>sample;

	// �ʎq���r�b�g��
	std::unordered_map<std::string, uint>bit;

	// �`�����l��
	std::unordered_map<std::string, uint>channel;

	// �g�`�f�[�^
	std::unordered_map<std::string, std::vector<float>>wave;
};
