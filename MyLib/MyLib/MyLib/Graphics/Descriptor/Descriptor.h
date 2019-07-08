#pragma once

enum D3D12_DESCRIPTOR_HEAP_TYPE : int;
enum D3D12_RESOURCE_STATES : int;
enum D3D12_HEAP_FLAGS : int;
enum D3D12_DESCRIPTOR_HEAP_FLAGS : int;
struct D3D12_HEAP_PROPERTIES;
struct D3D12_RESOURCE_DESC;
struct D3D12_CLEAR_VALUE;
struct ID3D12DescriptorHeap;
struct ID3D12Resource;

namespace okmonn
{
	// ヒープ生成
	void CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const size_t& num = 1);

	// リソース生成
	void CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_CLEAR_VALUE* clear, 
		const D3D12_RESOURCE_STATES& state, const D3D12_HEAP_FLAGS& flag = D3D12_HEAP_FLAGS(0));

	// RTV生成
	void RTV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// CBV生成
	void CBV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// SRV生成
	void SRV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& index = 0);

	// UAV生成
	void UAV(ID3D12Resource* rsc, ID3D12DescriptorHeap* heap, const size_t& stride, const size_t& num, const size_t& index = 0);

	// マップ
	void Map(ID3D12Resource* rsc, void** data);

	// アンマップ
	void UnMap(ID3D12Resource* rsc);
}