#pragma once
#include "../etc/Define.h"

// �f�B�X�N���v�^�[
class Descriptor
{
public:
	// �f�X�g���N�^
	~Descriptor();

	// �q�[�v����
	long CreateHeap(ID3D12DescriptorHeap** heap, const D3D12_DESCRIPTOR_HEAP_TYPE& type, const D3D12_DESCRIPTOR_HEAP_FLAGS& flag, const uint num = 1);

	// ���\�[�X����
	long CreateRsc(ID3D12Resource** rsc, const D3D12_HEAP_PROPERTIES& prop, const D3D12_RESOURCE_DESC& desc, const D3D12_CLEAR_VALUE* clear, 
		const D3D12_RESOURCE_STATES& state, const D3D12_HEAP_FLAGS& flag = D3D12_HEAP_FLAGS(0));

	// RTV����
	void RTV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// DSV����
	void DSV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// CBV����
	void CBV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// SRV����
	void SRV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const uint& index = 0);

	// UAV����
	void UAV(ID3D12DescriptorHeap* heap, ID3D12Resource* rsc, const size_t& stride, const size_t& num, const uint& index = 0);

	// �}�b�v
	long Map(ID3D12Resource* rsc, void** data);

	// �A���}�b�v
	void UnMap(ID3D12Resource* rsc);

	// �C���X�^���X�ϐ��擾
	static Descriptor& Get(void);

private:
	Descriptor();
	Descriptor(const Descriptor&) = delete;
	void operator=(const Descriptor&) = delete;
};
