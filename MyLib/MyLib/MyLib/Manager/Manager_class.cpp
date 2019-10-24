#include "Manager.h"
#include "../Window/Window.h"
#include "../Graphics/Device/Device.h"
#include "../Graphics/Queue/Queue.h"
#include "../Graphics/Allocator/Allocator.h"
#include "../Graphics/List/List.h"
#include "../Graphics/Fence/Fence.h"
#include "../Graphics/Swap/Swap.h"
#include "../Graphics/Render/Render.h"
#include "../Graphics/Descriptor/Descriptor.h"
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>

// コンストラクタ
MyLib::MyLib(const Vec2& size, const Vec2& pos, MyLib* parent) : 
	allo(Swap::bufferCnt)
{
	void* tmp = (parent == nullptr) ? nullptr : parent->win->Get();
	win = std::make_shared<Window>(pos, size, tmp);

	Init();
}

// デストラクタ
MyLib::~MyLib()
{
	okmonn::UnMap(rsc.Get());
}

// 定数リソース生成
void MyLib::CreateRsc(void)
{
	D3D12_HEAP_PROPERTIES prop{};
	prop.Type = D3D12_HEAP_TYPE::D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC desc{};
	desc.DepthOrArraySize = 1;
	desc.Dimension = D3D12_RESOURCE_DIMENSION::D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Height = 1;
	desc.Layout = D3D12_TEXTURE_LAYOUT::D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.MipLevels = 1;
	desc.SampleDesc = { 1, 0 };
	desc.Width = (sizeof(Vec2f) + 0xff) & ~0xff;

	okmonn::CreateRsc(&rsc, prop, desc, nullptr, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_GENERIC_READ);
	okmonn::CBV(rsc.Get(), heap.Get());
	okmonn::Map(rsc.Get(), (void**)& data);

	data->x = float(GetWinSize().x);
	data->y = float(GetWinSize().y);
}

// 初期化
void MyLib::Init(void)
{
	okmonn::CreateHeap(&heap, D3D12_DESCRIPTOR_HEAP_TYPE::D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
		D3D12_DESCRIPTOR_HEAP_FLAGS::D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE);
	CreateRsc();

	queue  = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	for (auto& i : allo)
	{
		i  = std::make_shared<Allocator>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	}
	list   = std::make_shared<List>(allo[0], D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence  = std::make_shared<Fence>(queue);
	swap   = std::make_shared<Swap>(win, queue);
	render = std::make_shared<Render>(swap);
}

// 画面クリア
void MyLib::Clear(void)
{
	unsigned int index = swap->Get()->GetCurrentBackBufferIndex();

	//コマンド関連のリセット
	auto hr = allo[index]->Get()->Reset();
	_ASSERTE(hr == S_OK);
	hr = list->Get()->Reset(allo[index]->Get(), nullptr);
	_ASSERTE(hr == S_OK);

	//描画区画セット
	list->Viewport(GetWinSize());
	list->Scissor(GetWinSize());

	//描画ターゲット更新
	list->Barrier(render->Get(), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET);

	//描画画面クリア
	render->Clear(list);
}

// 実行
void MyLib::Execution(void)
{
	//描画ターゲット更新
	list->Barrier(render->Get(), D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT);

	auto hr = list->Get()->Close();
	_ASSERT(hr == S_OK);

	ID3D12CommandList* com[] = {
		list->Get()
	};

	//コマンド実行
	queue->Get()->ExecuteCommandLists(_countof(com), com);

	//裏・表画面反転
	swap->Get()->Present(0, 0);

	fence->Wait();
}

// 描画準備
void MyLib::SetDraw(const size_t& index)
{
	list->Get()->SetDescriptorHeaps(1, heap.GetAddressOf());

	auto handle = heap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += unsigned __int64(Device::Get().Dev()->GetDescriptorHandleIncrementSize(heap->GetDesc().Type) * index);
	list->Get()->SetGraphicsRootDescriptorTable(unsigned int(index), handle);
}

// ウィンドウサイズ取得
Vec2 MyLib::GetWinSize(void)
{
	RECT winSize{};
	GetClientRect(HWND(win->Get()), &winSize);

	return Vec2(int(winSize.right), int(winSize.bottom));
}

// コマンドリスト取得
std::weak_ptr<List> MyLib::GetList(void) const
{
	return list;
}
