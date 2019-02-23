#pragma once
#include "../etc/Define.h"

class Descriptor
{
public:
	// デストラクタ
	~Descriptor();

	// ヒープ生成
	long CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const uint num = 1);

	// リソース生成
	long CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_CLEAR_VALUE* clear, 
		const D3D12_RESOURCE_STATES& state, const D3D12_HEAP_FLAGS& flag = D3D12_HEAP_FLAGS(0));

	// RTV生成
	void RTV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// DSV生成
	void DSV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// インスタンス変数取得
	static Descriptor& Get(void);

private:
	// コンストラクタ
	Descriptor();
	Descriptor(const Descriptor&) = delete;
	void operator=(const Descriptor&) = delete;
};
