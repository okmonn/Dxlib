#pragma once
#include <wrl.h>
#include <memory>

class Window;
class Queue;
struct IDXGISwapChain4;

class Swap
{
public:
	// コンストラクタ
	Swap(std::weak_ptr<Window>win, std::weak_ptr<Queue>queue);
	// デストラクタ
	~Swap();

	// スワップチェイン取得
	IDXGISwapChain4* Get(void) const;

private:
	// スワップチェインの生成
	void CreateSwap(void);


	// ウィンドウ
	std::weak_ptr<Window>win;

	// キュー
	std::weak_ptr<Queue>queue;

	// スワップチェイン
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swap;
};
