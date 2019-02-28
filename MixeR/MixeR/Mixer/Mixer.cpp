#include "Mixer.h"
#include <MyLib.h>

#pragma comment(lib, "MyLib.lib")

// ウィンドウサイズ
Vec2 winSize = { 640, 480 };

// コンストラクタ
Mixer::Mixer()
{
	lib = std::make_shared<MyLib>(winSize);
}

// デストラクタ
Mixer::~Mixer()
{
}

// 処理
void Mixer::Run(void)
{
	while (lib->CheckMsg() && KEY.CheckKey(KeyCode::Escape) == false)
	{

	}
}
