#pragma once
#include "../etc/Define.h"
#include <memory>

class Window;
class Queue;

// スワップチェイン
class Swap
{
public:
	// コンストラクタ
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);
	// デストラクタ
	~Swap();

	// 裏・表画面の遷移
	void Present(void) const;

	// スワップチェイン取得
	IDXGISwapChain4* Get(void) const;

private:
	Swap(const Swap&) = delete;
	void operator=(const Swap&) = delete;

	// スワップチェイン生成
	long CreateSwap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);


	// スワップチェイン
	IDXGISwapChain4* swap;
};
