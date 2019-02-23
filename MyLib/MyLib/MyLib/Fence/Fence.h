#pragma once
#include "../etc/Define.h"
#include <memory>

class Queue;

class Fence
{
public:
	// コンストラクタ
	Fence(std::weak_ptr<Queue>queue);
	// デストラクタ
	~Fence();

	// 待機
	void Wait(void);

private:
	// フェンス生成
	long CreateFence(void);


	// キュー
	std::weak_ptr<Queue>queue;

	// フェンス
	ID3D12Fence* fence;

	// イベントハンドル
	void* handle;

	// フェンスカウント
	uint64 cnt;
};
