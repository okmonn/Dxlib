#pragma once
#include <memory>

class MyLib;

// �S������
class Mixer
{
public:
	// �R���X�g���N�^
	Mixer();
	// �f�X�g���N�^
	~Mixer();

	// ����
	void Run(void);

private:
	Mixer(const Mixer&) = delete;
	void operator=(const Mixer&) = delete;


	// ���C�u����
	std::shared_ptr<MyLib>lib;
};
