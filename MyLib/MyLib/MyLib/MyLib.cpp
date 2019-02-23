#include "MyLib.h"
#include "Window/Window.h"
#include "Queue/Queue.h"
#include "List/List.h"
#include "Fence/Fence.h"
#include "Swap/Swap.h"
#include "Render/Render.h"
#include "Depth/Depth.h"
#include "etc/Release.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// コンストラクタ
MyLib::MyLib(const Vec2& size, const Vec2& pos) : winSize(size)
{
#ifdef _DEBUG
	ID3D12Debug* debug = nullptr;
	D3D12GetDebugInterface(IID_PPV_ARGS(&debug));
	debug->EnableDebugLayer();
#endif

	Instance(pos);
}

// デストラクタ
MyLib::~MyLib()
{
}

// クラスのインスタンス化
void MyLib::Instance(const Vec2& pos)
{
	win    = std::make_shared<Window>(pos, winSize);
	queue  = std::make_shared<Queue>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	list   = std::make_shared<List>(D3D12_COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);
	fence  = std::make_unique<Fence>(queue);
	swap   = std::make_shared<Swap>(win, queue, winSize);
	render = std::make_unique<Render>(swap);
	depth  = std::make_unique<Depth>(winSize);
}

// メッセージの確認
bool MyLib::CheckMsg(void) const
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}

// クリア
void MyLib::Clear(void) const
{
	list->Reset();

	list->Viewport(winSize);
	list->Scissor(winSize);

	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, render->Get());

	render->Clear(list, depth->Get());

	depth->Clear(list);
}

// 実行
void MyLib::Execution(void) const
{
	list->Barrier(D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATES::D3D12_RESOURCE_STATE_PRESENT, render->Get());

	list->Close();

	ID3D12CommandList* com[] = {
		list->GetList()
	};

	queue->Execution(com, _countof(com));

	swap->Present();

	fence->Wait();
}
