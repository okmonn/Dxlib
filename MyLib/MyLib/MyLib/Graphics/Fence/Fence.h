#pragma once
#include <wrl.h>
#include <memory>

struct ID3D12Fence;
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
	void CreateFence(void);


	// キュー
	std::weak_ptr<Queue>queue;

	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence>fence;

	// イベントハンドル
	void* handle;

	// カウント
	unsigned __int64 cnt;
};
