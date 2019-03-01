#include "Compute.h"
#include "../Queue/Queue.h"
#include "../List/List.h"
#include "../Fence/Fence.h"
#include "../Root/Root.h"
#include "../Pipe/Pipe.h"
#include "../Descriptor/Descriptor.h"
#include "../etc/Release.h"

// コンストラクタ
Compute::Compute(const std::string& fileName, const uint& num) : 
	heap(nullptr)
{
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	list  = std::make_unique<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	fence = std::make_unique<Fence>(queue);
	root  = std::make_shared<Root>();
	root->Compute(fileName);
	pipe  = std::make_unique<Pipe>(root);

	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, num);
}

// コンストラクタ
Compute::Compute(const int& id, const uint& num) :
	heap(nullptr)
{
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	list = std::make_unique<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	fence = std::make_unique<Fence>(queue);
	root = std::make_shared<Root>();
	root->Compute(id);
	pipe = std::make_unique<Pipe>(root);

	Desc.CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, num);
}

// デストラクタ
Compute::~Compute()
{
	for (auto& i : rsc)
	{
		Desc.UnMap(i.second);
		Release(i.second);
	}
	Release(heap);
}

// 定数リソース生成
long Compute::CBV(const std::string& name, const size_t& size, const uint& index)
{
	if (rsc.find(name) != rsc.end())
	{
		return S_FALSE;
	}

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_UNKNOWN;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_NONE;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (size + 0xff) &~0xff;

	if (FAILED(Desc.CreateRsc(&rsc[name], prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ)))
	{
		return S_FALSE;
	}

	Desc.CBV(heap, rsc[name], index);

	Desc.Map(rsc[name], &data[name]);

	return S_OK;
}

// UAVリソース生成
long Compute::UAV(const std::string & name, const size_t& stride, const size_t& num, const uint& index)
{
	if (rsc.find(name) != rsc.end())
	{
		return S_FALSE;
	}

	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_L0;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	desc.Format           = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = uint64(stride * num);

	if (FAILED(Desc.CreateRsc(&rsc[name], prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_UNORDERED_ACCESS)))
	{
		return S_FALSE;
	}

	Desc.UAV(heap, rsc[name], stride, num, index);

	Desc.Map(rsc[name], &data[name]);

	return S_OK;
}

// 実行
void Compute::Execution(const uint& x, const uint& y, const uint& z)
{
	list->Reset();

	list->ComputeRoot(root->Get());
	list->Pipeline(pipe->Get());

	list->Heap(&heap, 1);
	uint index = 0;
	for (auto& i : rsc)
	{
		list->ComputeTable(index, heap, index);
		++index;
	}

	list->Dispatch(x, y, z);

	list->Close();

	ID3D12CommandList* com[] = {
		list->GetList()
	};

	queue->Execution(com, _countof(com));

	fence->Wait();
}

// 反映
template<typename T>
void Compute::UpData(const std::string& name, std::vector<T>& output)
{
	if (rsc.find(name) == rsc.end())
	{
		return;
	}

	uint size = uint(rsc[name]->GetDesc().Width / sizeof(T));
	output.assign((T*)data[name], (T*)data[name] + size);
}
template void Compute::UpData<float>(const std::string&name, std::vector<float>& output);
