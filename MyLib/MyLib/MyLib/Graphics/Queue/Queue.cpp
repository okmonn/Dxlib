#include "Queue.h"
#include "../Device/Device.h"
#include <d3d12.h>
#include <crtdbg.h>

// コンストラクタ
Queue::Queue(const D3D12_COMMAND_LIST_TYPE& type) : 
	queue(nullptr)
{
	CreateQueue(type);
}

// デストラクタ
Queue::~Queue()
{
}

// コマンドキュー生成
void Queue::CreateQueue(const D3D12_COMMAND_LIST_TYPE& type)
{
	D3D12_COMMAND_QUEUE_DESC desc{};
	desc.Type = type;

	auto hr = Device::Get().Dev()->CreateCommandQueue(&desc, IID_PPV_ARGS(&queue));
	_ASSERT(hr == S_OK);
}

// コマンドキュー取得
ID3D12CommandQueue* Queue::Get(void) const
{
	return queue.Get();
}
