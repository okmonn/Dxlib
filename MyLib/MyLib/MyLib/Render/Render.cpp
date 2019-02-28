#include "Render.h"
#include "../List/List.h"
#include "../Swap/Swap.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// �N���A�F
const float color[] = {
	0.0f, 0.0f, 0.0f, 1.0f
};

// �R���X�g���N�^
Render::Render(std::weak_ptr<Swap>swap) : swap(swap),
	heap(nullptr)
{
	Init();
}

// �f�X�g���N�^
Render::~Render()
{
	for (auto& i : rsc)
	{
		Release(i);
	}
	Release(heap);
}

// ������
void Render::Init(void)
{
	DXGI_SWAP_CHAIN_DESC1 tmp{};
	swap.lock()->Get()->GetDesc1(&tmp);
	rsc.resize(tmp.BufferCount);

	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_NONE, uint(rsc.size()));

	auto hr = S_OK;
	for (uint i = 0; i < rsc.size(); ++i)
	{
		hr = swap.lock()->Get()->GetBuffer(i, IID_PPV_ARGS(&rsc[i]));
		if (FAILED(hr))
		{
			func::DebugLog("���\�[�X�����F���s");
			break;
		}

		Desc.RTV(heap, rsc[i], i);
	}
}

// �N���A
void Render::Clear(std::weak_ptr<List> list, ID3D12DescriptorHeap * depth)
{
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * swap.lock()->Get()->GetCurrentBackBufferIndex();

	auto dHandle = depth->GetCPUDescriptorHandleForHeapStart();
	list.lock()->GetList()->OMSetRenderTargets(1, &handle, false, &dHandle);

	list.lock()->GetList()->ClearRenderTargetView(handle, color, 0, nullptr);
}

// ���\�[�X�擾
ID3D12Resource * Render::Get(void) const
{
	return rsc[swap.lock()->Get()->GetCurrentBackBufferIndex()];
}
