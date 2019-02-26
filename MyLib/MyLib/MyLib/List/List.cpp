#include "List.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
List::List(const D3D12_COMMAND_LIST_TYPE& type) : 
	allo(nullptr), list(nullptr)
{
	Init(type);
}

// デストラクタ
List::~List()
{
	Release(list);
	Release(allo);
}

// アロケータ生成
long List::CreateAllo(const D3D12_COMMAND_LIST_TYPE& type)
{
	auto hr = Dev->CreateCommandAllocator(type, IID_PPV_ARGS(&allo));
	if (FAILED(hr))
	{
		func::DebugLog("アロケータ生成：失敗");
	}

	return hr;
}

// リスト生成
long List::CreateList(const D3D12_COMMAND_LIST_TYPE& type)
{
	auto hr = Dev->CreateCommandList(0, type, allo, nullptr, IID_PPV_ARGS(&list));
	if (FAILED(hr))
	{
		func::DebugLog("リスト生成：失敗");
		return hr;
	}

	Close();

	return hr;
}

// リセット
void List::Reset(ID3D12PipelineState* pipe) const
{
	allo->Reset();
	list->Reset(allo, pipe);
}

// ビューポートセット
void List::Viewport(const Vec2& size) const
{
	D3D12_VIEWPORT view{};
	view.Height   = float(size.y);
	view.MaxDepth = 1.0f;
	view.Width    = float(size.x);

	list->RSSetViewports(1, &view);
}

// シザーセット
void List::Scissor(const Vec2& size) const
{
	RECT scissor{};
	scissor.bottom = long(size.y);
	scissor.right  = long(size.x);

	list->RSSetScissorRects(1, &scissor);
}

// バリアセット
void List::Barrier(const D3D12_RESOURCE_STATES& befor, const D3D12_RESOURCE_STATES& affter, ID3D12Resource* rsc) const
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE::D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource   = rsc;
	barrier.Transition.StateBefore = befor;
	barrier.Transition.StateAfter  = affter;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_FLAGS::D3D12_RESOURCE_BARRIER_FLAG_NONE;

	list->ResourceBarrier(1, &barrier);
}

// 描画用ルートセット
void List::GraphicRoot(ID3D12RootSignature* root) const
{
	list->SetGraphicsRootSignature(root);
}

// 計算用ルートセット
void List::ComputeRoot(ID3D12RootSignature* root) const
{
	list->SetComputeRootSignature(root);
}

// パイプラインセット
void List::Pipeline(ID3D12PipelineState* pipe) const
{
	list->SetPipelineState(pipe);
}

// ヒープセット
void List::Heap(ID3D12DescriptorHeap** heap, const size_t& num) const
{
	list->SetDescriptorHeaps(uint(num), heap);
}

// 描画用ルートとヒープ関連付け
void List::GraphicTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index) const
{
	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	list->SetGraphicsRootDescriptorTable(id, handle);
}

// 計算用ルートとヒープ関連付け
void List::ComputeTable(const uint& id, ID3D12DescriptorHeap* heap, const uint& index) const
{
	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += Dev->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index;
	list->SetComputeRootDescriptorTable(id, handle);
}

// 頂点バッファビューセット
void List::VertexView(const D3D12_VERTEX_BUFFER_VIEW& view) const
{
	list->IASetVertexBuffers(0, 1, &view);
}

// インデックスバッファビューセット
void List::IndexView(const D3D12_INDEX_BUFFER_VIEW& view) const
{
	list->IASetIndexBuffer(&view);
}

// トポロジーセット
void List::Topology(const D3D_PRIMITIVE_TOPOLOGY& type) const
{
	list->IASetPrimitiveTopology(type);
}

// 頂点描画
void List::DrawVertex(const size_t& num, const uint& instance) const
{
	list->DrawInstanced(uint(num), instance, 0, 0);
}

// バンドル実行
void List::Bundle(ID3D12GraphicsCommandList* list) const
{
	this->list->ExecuteBundle(list);
}

// GPU計算実行
void List::Dispatch(const uint& x, const uint& y, const uint& z) const
{
	list->Dispatch(x, y, z);
}

// クローズ
void List::Close(void) const
{
	list->Close();
}

// 初期化
void List::Init(const D3D12_COMMAND_LIST_TYPE & type)
{
	CreateAllo(type);
	CreateList(type);
}

// アロケータ取得
ID3D12CommandAllocator * List::GetAllo(void) const
{
	return allo;
}

// リスト取得
ID3D12GraphicsCommandList * List::GetList(void) const
{
	return list;
}
