#pragma once
#include <vector>
#include <memory>

class MyLib;
class Sound;
class Primitive;

// �g�`
class Waves
{
public:
	// �R���X�g���N�^
	Waves(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound);
	// �f�X�g���N�^
	~Waves();

	// ����
	void Run(void);

private:
	Waves(const Waves&) = delete;
	void operator=(const Waves&) = delete;


	// ���C�u����
	std::unique_ptr<MyLib>lib;

	// �T�E���h
	std::weak_ptr<Sound>sound;

	// �v���~�e�B�u
	std::unique_ptr<Primitive>prim;

	// �t���[��
	unsigned char flam;
};
