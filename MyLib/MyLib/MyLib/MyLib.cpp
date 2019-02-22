#include "MyLib.h"
#include "Window/Window.h"
#include "etc/Release.h"
#include <Windows.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

// コンストラクタ
MyLib::MyLib(const Vec2& size, const Vec2& pos)
{
	Instance(size, pos);
}

// デストラクタ
MyLib::~MyLib()
{
}

// クラスのインスタンス化
void MyLib::Instance(const Vec2& size, const Vec2& pos)
{
	win = std::make_shared<Window>(pos, size);
}

// メッセージの確認
bool MyLib::CheckMsg(void)
{
	static MSG msg{};

	if (msg.message == WM_QUIT)
	{
		return false;
	}

	//呼び出し側スレッドが所有しているウィンドウに送信されたメッセージの保留されている物を取得
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		//仮想キーメッセージを文字メッセージに変換
		TranslateMessage(&msg);
		//1つのウィドウプロシージャにメッセージを送出する
		DispatchMessage(&msg);
	}

	return true;
}
