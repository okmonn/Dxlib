#pragma once
#include <vector>
#include <memory>

class MyLib;
class Compute;
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
	// ������
	void Init(void);


	// ���C�u����
	std::unique_ptr<MyLib>lib;

	// �T�E���h
	std::weak_ptr<Sound>sound;

	// �R���s���[�g
	std::unique_ptr<Compute>compute;

	// �v���~�e�B�u
	std::unique_ptr< Primitive>prim;

	// ����
	std::vector<float>real;

	// ����
	std::vector<float>imag;
};
