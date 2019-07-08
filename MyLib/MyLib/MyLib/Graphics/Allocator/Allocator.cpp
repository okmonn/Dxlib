#include "Allocator.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>

// �R���X�g���N�^
Allocator::Allocator(const D3D12_COMMAND_LIST_TYPE& type) :
	allo(nullptr)
{
	CreateAllo(type);
}

// �f�X�g���N�^
Allocator::~Allocator()
{
}

// �R�}���h�A���P�[�^����
void Allocator::CreateAllo(const D3D12_COMMAND_LIST_TYPE& type)
{
	auto hr = Device::Get().Dev()->CreateCommandAllocator(type, IID_PPV_ARGS(&allo));
	_ASSERT(hr == S_OK);
}

// �R�}���h�A���P�[�^�擾
ID3D12CommandAllocator* Allocator::Get(void) const
{
	return allo.Get();
}
