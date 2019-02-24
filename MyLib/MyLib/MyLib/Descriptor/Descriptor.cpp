#include "Descriptor.h"
#include "../etc/Release.h"

// コンストラクタ
Descriptor::Descriptor()
{
}

// デストラクタ
Descriptor::~Descriptor()
{
}

// ヒープ生成
long Descriptor::CreateHeap(ID3D12DescriptorHeap ** heap, const D3D12_DESCRIPTOR_HEAP_TYPE & type, const D3D12_DESCRIPTOR_HEAP_FLAGS & flag, const uint num)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = flag;
	desc.NumDescriptors = num;
	desc.Type           = type;

	auto hr = Dev->CreateDescriptorHeap(&desc, IID_PPV_ARGS(*(&heap)));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nヒープ生成：失敗\n"));
	}

	return hr;
}

// リソース生成
long Descriptor::CreateRsc(ID3D12Resource ** rsc, const D3D12_HEAP_PROPERTIES & prop, const D3D12_RESOURCE_DESC & desc, const D3D12_CLEAR_VALUE * clear, 
	const D3D12_RESOURCE_STATES & state, const D3D12_HEAP_FLAGS & flag)
{
	auto hr = Dev->CreateCommittedResource(&prop, flag, &desc, state, clear, IID_PPV_ARGS(*(&rsc)));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nリソース生成：失敗\n"));
	}

	return hr;
}

// RTV生成
void Descriptor::RTV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format = rsc->GetDesc().Format;
	desc.ViewDimension = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Dev->CreateRenderTargetView(rsc, &desc, handle);
}

// DSV生成
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

// CBV生成
void Descriptor::CBV(ID3D12DescriptorHeap * heap, ID3D12Resource * rsc, const uint & index)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
	desc.BufferLocation = rsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = uint(rsc->GetDesc().Width);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart(); 
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	Dev->CreateConstantBufferView(&desc, handle);
}

// マップ
long Descriptor::Map(ID3D12Resource * rsc, void ** data)
{
	D3D12_RANGE range = { 0, 1 };
	auto hr = rsc->Map(0, &range, *(&data));
	if (FAILED(hr))
	{
		OutputDebugString(_T("\nマップ：失敗\n"));
	}

	return hr;
}

// アンマップ
void Descriptor::UnMap(ID3D12Resource * rsc)
{
	D3D12_RANGE range = { 0, 1 };
	rsc->Unmap(0, &range);
}

// インスタンス変数取得
Descriptor & Descriptor::Get(void)
{
	static Descriptor instance;
	return instance;
}
