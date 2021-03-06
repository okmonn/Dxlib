#include "Allocator.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>

// コンストラクタ
Allocator::Allocator(const D3D12_COMMAND_LIST_TYPE& type) :
	allo(nullptr)
{
	CreateAllo(type);
}

// デストラクタ
Allocator::~Allocator()
{
}

// コマンドアロケータ生成
void Allocator::CreateAllo(const D3D12_COMMAND_LIST_TYPE& type)
{
	auto hr = Device::Get().Dev()->CreateCommandAllocator(type, IID_PPV_ARGS(&allo));
	_ASSERT(hr == S_OK);
}

// コマンドアロケータ取得
ID3D12CommandAllocator* Allocator::Get(void) const
{
	return allo.Get();
}
