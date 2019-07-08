#include "Compute.h"
#include "../Graphics/Queue/Queue.h"
#include "../Graphics/Allocator/Allocator.h"
#include "../Graphics/List/List.h"
#include "../Graphics/Fence/Fence.h"
#include "../Graphics/Root/Root.h"
#include "../Graphics/Pipe/Pipe.h"
#include "../Graphics/Descriptor/Descriptor.h"
#include <d3d12.h>

// コンストラクタ
Compute::Compute() : 
	heap(nullptr), index(0)
{
	queue = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	allo  = std::make_shared<Allocator>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	list  = std::make_shared<List>(allo, D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_COMPUTE);
	fence = std::make_shared<Fence>(queue);
}

// デストラクタ
Compute::~Compute()
{
}

// シェーダーファイル読み込み
void Compute::Compile(const std::string& fileName, const std::string& func, const std::string& ver)
{
	root = std::make_shared<Root>();
	root->Compute(fileName, func, ver);
	pipe = std::make_shared<Pipe>(root);
}

// .cso読み込み
void Compute::Load(const std::string& fileName)
{
	root = std::make_shared<Root>();
	root->Compute(fileName);
	pipe = std::make_shared<Pipe>(root);
}

// リソース読み込み
void Compute::Read(const int& id)
{
	root = std::make_shared<Root>();
	root->Compute(id);
	pipe = std::make_shared<Pipe>(root);
}

// ヒープ生成
void Compute::CreateHeap(const size_t& num)
{
	okmonn::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE, num);

	rsc.resize(num);
}

// 定数リソース生成
int Compute::CreateCRsc(const size_t& size)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = (size + 0xff) & ~0xff;

	okmonn::CreateRsc(&rsc[index].rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	okmonn::CBV(rsc[index].rsc.Get(), heap.Get(), index);
	okmonn::Map(rsc[index].rsc.Get(), &rsc[index].data);

	return index++;
}

// 非順序リソース生成
int Compute::CreateURsc(const size_t& stride, const size_t& num)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY::D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	prop.MemoryPoolPreference = D3D12_MEMORY_POOL::D3D12_MEMORY_POOL_L0;
	prop.Type                 = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_CUSTOM;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension        = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Flags            = D3D12_RESOURCE_FLAGS::D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
	desc.Height           = 1;
	desc.Layout           = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels        = 1;
	desc.SampleDesc       = { 1, 0 };
	desc.Width            = unsigned __int64(stride * num);

	okmonn::CreateRsc(&rsc[index].rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);

	okmonn::UAV(rsc[index].rsc.Get(), heap.Get(), stride, num, index);
	okmonn::Map(rsc[index].rsc.Get(), &rsc[index].data);

	return index++;
}

// GPUメモリにコピー
void Compute::Copy(const int& id, void* data, const size_t& size)
{
	memcpy(rsc[id].data, data, size);
}

// 実行
void Compute::Execution(const unsigned int& x, const unsigned int& y, const unsigned int& z)
{
	allo->Get()->Reset();
	list->Get()->Reset(allo->Get(), nullptr);

	list->Get()->SetComputeRootSignature(root->Get());
	list->Get()->SetPipelineState(pipe->Get());

	list->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());
	for (unsigned int i = 0; i < rsc.size(); ++i)
	{
		list->SetComputeTable(i, heap.Get(), i);
	}

	list->Get()->Dispatch(x, y, z);

	list->Get()->Close();

	ID3D12CommandList* com[] = {
		list->Get()
	};

	queue->Get()->ExecuteCommandLists(_countof(com), com);

	fence->Wait();
}

// GPUメモリデータ取得
template <typename T>
std::vector<T> Compute::GetData(const int& id)
{
	auto size = rsc[id].rsc->GetDesc().Width / sizeof(T);
	return std::vector<T>((T*)rsc[id].data, (T*)rsc[id].data + size);
}
template std::vector<int> Compute::GetData(const int&);
template std::vector<float> Compute::GetData(const int&);

// 終了
void Compute::Finish(void)
{
	for (Resource& i : rsc)
	{
		okmonn::UnMap(i.rsc.Get());
	}
}
