#include "Input.h"
#include "KeyCode.h"
#include <Windows.h>

// コンストラクタ
Input::Input()
{
	std::fill(now.begin(), now.end(), 0);
	std::fill(old.begin(), old.end(), 0);
}

// デストラクタ
Input::~Input()
{
}

// キー入力
bool Input::CheckKey(const okmonn::KeyCode& key)
{
	old[unsigned char(key)] = now[unsigned char(key)];
	now[unsigned char(key)] = (GetKeyState(unsigned char(key)) & 0x80);
	if (now[unsigned char(key)])
	{
		return true;
	}

	return false;
}

// トリガー入力
bool Input::Trigger(const okmonn::KeyCode& key)
{
	if (CheckKey(key) == true
		&& now[unsigned char(key)] != old[unsigned char(key)])
	{
		return true;
	}

	return false;
}
