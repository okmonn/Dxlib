#include "Input.h"
#include <Windows.h>

// コンストラクタ
Input::Input() : 
	key(std::nullopt)
{
}

// デストラクタ
Input::~Input()
{
}

// キー入力
bool Input::CheckKey(const KeyCode & key)
{
	if (GetKeyState(int(key)) & 0x80)
	{
		this->key = key;
		return true;
	}

	return false;
}

// トリガー入力
bool Input::Trigger(const KeyCode & key)
{
	if (this->key != key)
	{
		return CheckKey(key);
	}
	
	return false;
}

// インスタンス変数取得
Input & Input::Get(void)
{
	static Input instance;
	return instance;
}
