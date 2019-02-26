#pragma once
#include "../etc/Define.h"
#include <memory>

class Queue;

// フェンス
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
	Fence(const Fence&) = delete;
	void operator=(const Fence&) = delete;

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
