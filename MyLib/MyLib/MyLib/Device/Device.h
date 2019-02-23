#pragma once
#include "../etc/Define.h"

class Device
{
public:
	// �f�X�g���N�^
	~Device();

	// �C���X�^���X�ϐ��擾
	static Device& Get(void);

	// �f�o�C�X�擾
	ID3D12Device* GetDev(void) const;
	// �t�@�N�g���[�擾
	IDXGIFactory4* GetFactory(void) const;

private:
	// �R���X�g���N�^
	Device();
	Device(const Device&) = delete;
	void operator=(const Device&) = delete;

	// �t�@�N�g���[����
	long CreateFactory(void);

	// �f�o�C�X����
	long CreateDev(void);

	// ������
	void Init(void);


	// �f�o�C�X
	ID3D12Device* dev;

	// �t�@�N�g���[
	IDXGIFactory4* factory;
};
