#pragma once
#include "../etc/Define.h"

class Queue
{
public:
	// コンストラクタ
	Queue(const D3D12_COMMAND_LIST_TYPE& type);
	// デストラクタ
	~Queue();

	// 実行
	void Execution(ID3D12CommandList ** list, const size_t & num);

	// キュー取得
	ID3D12CommandQueue* Get(void) const;

private:
	// キュー生成
	long CreateQueue(const D3D12_COMMAND_LIST_TYPE& type);


	// キュー
	ID3D12CommandQueue* queue;
};
