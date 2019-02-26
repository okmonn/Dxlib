#include "Queue.h"
#include "../etc/Func.h"
#include "../etc/Release.h"

// コンストラクタ
Queue::Queue(const D3D12_COMMAND_LIST_TYPE& type) :
	queue(nullptr)
{
	CreateQueue(type);
}

// デストラクタ
Queue::~Queue()
{
	Release(queue);
}

// キュー生成
long Queue::CreateQueue(const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Flags    = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE;
	desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	desc.Type     = type;

	auto hr = Dev->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	if (FAILED(hr))
	{
		func::DebugLog("キュー生成：失敗");
	}
	
	return hr;
}

// 実行
void Queue::Execution(ID3D12CommandList ** list, const size_t & num)
{
	queue->ExecuteCommandLists(uint(num), list);
}

// キュー取得
ID3D12CommandQueue * Queue::Get(void) const
{
	return queue;
}

