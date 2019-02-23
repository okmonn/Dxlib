#pragma once
#include "../Vector/Vector3.h"
#include "../etc/Define.h"
#include <vector>

class Primitive
{
public:
	// �R���X�g���N�^
	Primitive();
	// �f�X�g���N�^
	~Primitive();

private:
	// �q�[�v
	ID3D12DescriptorHeap* heap;

	// �萔���\�[�X
	ID3D12Resource* cRsc;

	// ���_���\�[�X
	ID3D12Resource* vRsc;
};
