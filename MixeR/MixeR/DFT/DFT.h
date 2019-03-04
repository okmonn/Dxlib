#pragma once
#include <vector>
#include <memory>

class MyLib;
class Sound;
class Primitive;

// GPU�ŗ��U�t�[���G�ϊ�
class DFT
{
public:
	// �R���X�g���N�^
	DFT(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound);
	// �f�X�g���N�^
	~DFT();

	// ����
	void Run(void);

private:
	// ���C�u����
	std::unique_ptr<MyLib>lib;

	// �T�E���h
	std::weak_ptr<Sound>sound;

	// �v���~�e�B�u
	std::unique_ptr< Primitive>prim;

	// ����
	std::vector<float>real;

	// ����
	std::vector<float>imag;
};
