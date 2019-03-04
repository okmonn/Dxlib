#include "Input.h"
#include <windows.h>

// コンストラクタ
Input::Input()
{
	memset(&now[0], 0, sizeof(now));
	memset(&old[0], 0, sizeof(old));
}

// デストラクタ
Input::~Input()
{
}

// キー入力
bool Input::CheckKey(const KeyCode & key)
{
	old[uint(key)] = now[uint(key)];
	now[uint(key)] = (GetKeyState(uint(key)) & 0x80);
	if (now[uint(key)])
	{
		return true;
	}

	return false;
}

// トリガー入力
bool Input::Trigger(const KeyCode & key)
{
	if (CheckKey(key) == true 
		&& now[uint(key)] != old[uint(key)])
	{
		return true;
	}

	return false;
}

// インスタンス変数取得
Input & Input::Get(void)
{
	static Input instance;
	return instance;
}
