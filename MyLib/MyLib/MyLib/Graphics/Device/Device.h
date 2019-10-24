#pragma once
#include "../../etc/Single.h"
#include <wrl.h>

struct ID3D12Device5;
struct IDXGIFactory1;

class Device :
	public Single<Device>
{
	friend Single<Device>;
public:
	// �f�o�C�X�擾
	ID3D12Device5* Dev(void) const;

private:
	// �R���X�g���N�^
	Device();
	// �f�X�g���N�^
	~Device();

	// �f�o�C�X����
	void CreateDev(void);


	// �f�o�C�X
	Microsoft::WRL::ComPtr<ID3D12Device5>dev;
};
