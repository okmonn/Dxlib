#pragma once
#include "Vector/Vector2.h"
#include <memory>

class Window;
class Queue;
class List;

class MyLib
{
public:
	// コンストラクタ
	MyLib(const Vec2& size, const Vec2& pos = 0x80000000);
	// デストラクタ
	~MyLib();

	// メッセージの確認
	bool CheckMsg(void);

private:
	//代入禁止
	void operator=(const MyLib&) = delete;

	// クラスのインスタンス化
	void Instance(const Vec2& size, const Vec2& pos);


	// ウィンドウ
	std::shared_ptr<Window>win;

	// キュー
	std::shared_ptr<Queue>queue;

	// リスト
	std::shared_ptr<List>list;
};
