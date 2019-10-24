#include "Descriptor.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>

// ヒープ生成
void okmonn::CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const size_t& num)
{
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Flags          = flag;
	desc.NumDescriptors = unsigned int(num);
	desc.Type           = type;

	auto hr = Device::Get().Dev()->CreateDescriptorHeap(&desc,IID_PPV_ARGS(&(*heap)));
	_ASSERT(hr == S_OK);
}

// リソース生成
void okmonn::CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_CLEAR_VALUE* clear, 
	const D3D12_RESOURCE_STATES& state, const D3D12_HEAP_FLAGS& flag)
{
	auto hr = Device::Get().Dev()->CreateCommittedResource(&prop, flag, &desc, state, clear, IID_PPV_ARGS(&(*rsc)));
	_ASSERT(hr == S_OK);
}

// RTV生成
void okmonn::RTV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_RENDER_TARGET_VIEW_DESC desc{};
	desc.Format             = rsc->GetDesc().Format;
	desc.ViewDimension      = D3D12_RTV_DIMENSION::D3D12_RTV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipSlice = 0;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Device::Get().Dev()->CreateRenderTargetView(rsc, &desc, handle);
}

// CBV生成
void okmonn::CBV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_CONSTANT_BUFFER_VIEW_DESC desc{};
	desc.BufferLocation = rsc->GetGPUVirtualAddress();
	desc.SizeInBytes    = unsigned int(rsc->GetDesc().Width);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Device::Get().Dev()->CreateConstantBufferView(&desc, handle);
}

// SRV生成
void okmonn::SRV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index)
{
	D3D12_SHADER_RESOURCE_VIEW_DESC desc{};
	desc.Format                  = rsc->GetDesc().Format;
	desc.ViewDimension           = D3D12_SRV_DIMENSION::D3D12_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels     = 1;
	desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;

	Device::Get().Dev()->CreateShaderResourceView(rsc, &desc, handle);
}

// UAV生成
void okmonn::UAV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& stride, const size_t& num, const size_t& index)
{
	D3D12_UNORDERED_ACCESS_VIEW_DESC desc{};
	desc.ViewDimension              = D3D12_UAV_DIMENSION::D3D12_UAV_DIMENSION_BUFFER;
	desc.Format                     = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Buffer.NumElements         = unsigned int(num);
	desc.Buffer.StructureByteStride = unsigned int(stride);

	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	Device::Get().Dev()->CreateUnorderedAccessView(rsc, nullptr, &desc, handle);
}

// マップ
void okmonn::Map(ID3D12Resource* rsc, void** data)
{
	D3D12_RANGE range{ 0, 1 };
	auto hr = rsc->Map(0, &range, *(&data));
	_ASSERT(hr == S_OK);
}

// アンマップ
void okmonn::UnMap(ID3D12Resource* rsc)
{
	D3D12_RANGE range{ 0, 1 };
	rsc->Unmap(0, &range);
}
