#pragma once
#include "../Vector/Vector2.h"
#include "../etc/Define.h"
#include <memory>

class Window;
class Queue;

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
	// スワップチェイン生成
	long CreateSwap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue, const Vec2& size);


	// スワップチェイン
	IDXGISwapChain4* swap;
};
