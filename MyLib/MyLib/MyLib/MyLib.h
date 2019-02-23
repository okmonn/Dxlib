#pragma once
#include "Vector/Vector2.h"
#include <memory>

class Window;
class Queue;
class List;
class Fence;
class Swap;
class Render;
class Depth;

class MyLib
{
public:
	// コンストラクタ
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	// デストラクタ
	~MyLib();

	// メッセージの確認
	bool CheckMsg(void) const;

	// クリア
	void Clear(void) const;

	// 実行
	void Execution(void) const;

private:
	//代入禁止
	void operator=(const MyLib&) = delete;

	// クラスのインスタンス化
	void Instance(const Vec2& pos);


	// ウィンドウサイズ
	Vec2 winSize;

	// ウィンドウ
	std::shared_ptr<Window>win;

	// キュー
	std::shared_ptr<Queue>queue;

	// リスト
	std::shared_ptr<List>list;

	// フェンス
	std::unique_ptr<Fence>fence;

	// スワップ
	std::shared_ptr<Swap>swap;

	// レンダー
	std::unique_ptr<Render>render;

	// デプス
	std::unique_ptr<Depth>depth;
};
