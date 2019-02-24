#include "Descriptor.h"
#include "../etc/Release.h"

// �R���X�g���N�^
Descriptor::Descriptor()
{
}

// �f�X�g���N�^
Descriptor::~Descriptor()
{
}

// �q�[�v����
long Descriptor::CreateHeap(ID3D12DescriptorHeap ** heap, const D3D12_DESCRIPTOR_HEAP_TYPE & type, const D3D12_DESCRIPTOR_HEAP_FLAGS & flag, const uint num)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = flag;
	desc.NumDescriptors = num;
	desc.Type           = type;

	auto hr = Dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(*(&heap)));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�q�[�v�����F���s\n"));
	}

	return hr;
}

// ���\�[�X����
long Descriptor::CreateRsc(ID3D12Resource ** rsc, const D3D12_HEAP_PROPERTIES & prop, const D3D12_RESOURCE_DESC & desc, const D3D12_CLEAR_VALUE * clear, 
	const D3D12_RESOURCE_STATES & state, const D3D12_HEAP_FLAGS & flag)
{
	auto hr = Dev->CreateCommittedResource(&prop, flag, &desc, state, clear, IID_PPV_ARGS(*(&rsc)));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n���\�[�X�����F���s\n"));
	}

	return hr;
}

// RTV����
void Descriptor::RTV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format = rsc->GetDesc().Format;
	desc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Dev->CreateRenderTargetView(rsc, &desc, handle);
}

// DSV����
void Descriptor::DSV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index)
{
	D3D12_DEPTH_STENCIL_VIEW_DESC desc{};
	desc.Flags         = D3D12_DSV_FLAGS::D3D12_DSV_FLAG_NONE;
	desc.Format        = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
	desc.ViewDimension = D3D12_DSV_DIMENSION::D3D12_DSV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	Dev->CreateDepthStencilView(rsc, &desc, handle);
}

// CBV����
void Descriptor::CBV(ID3D12DescriptorHeap * heap, ID3D12Resource * rsc, const uint & index)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
	desc.BufferLocation = rsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = uint(rsc->GetDesc().Width);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart(); 
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	Dev->CreateConstantBufferView(&desc, handle);
}

// �}�b�v
long Descriptor::Map(ID3D12Resource * rsc, void ** data)
{
	D3D12_RANGE range = { 0, 1 };
	auto hr = rsc->Map(0, &range, *(&data));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\n�}�b�v�F���s\n"));
	}

	return hr;
}

// �A���}�b�v
void Descriptor::UnMap(ID3D12Resource * rsc)
{
	D3D12_RANGE range = { 0, 1 };
	rsc->Unmap(0, &range);
}

// �C���X�^���X�ϐ��擾
Descriptor & Descriptor::Get(void)
{
	static Descriptor instance;
	return instance;
}
