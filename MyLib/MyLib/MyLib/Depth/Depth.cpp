#include "Depth.h"
#include "../List/List.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Depth::Depth(const Vec2& size) : 
	heap(nullptr), rsc(nullptr)
{
	Init(size);
}

// �f�X�g���N�^
Depth::~Depth()
{
	Release(rsc);
	Release(heap);
}

// ������
void Depth::Init(const Vec2& size)
{
	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_DSV, D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 1);

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_DEFAULT;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_R32_TYPELESS;
	desc.Height           = uint(size.y);
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_UNKNOWN;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = uint64(size.x);

	D3D12_CLEAR_VALUE clear{};
	clear.DepthStencil = { 1.0f, 0 };
	clear.Format       = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;

	Desc.CreateRsc(&rsc, prop, desc, &clear, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_DEPTH_WRITE);

	Desc.DSV(heap, rsc);
}

// �N���A
void Depth::Clear(std::weak_ptr<List>list)
{
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	list.lock()->GetList()->ClearDepthStencilView(handle, D3D12_CLEAR_FLAGS::D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

// �q�[�v�擾
ID3D12DescriptorHeap * Depth::Get(void) const
{
	return heap;
}