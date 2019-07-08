#pragma once
#include "../etc/Single.h"
#include <array>

namespace okmonn {
	enum class KeyCode;
}

class Input :
	public Single<Input>
{
	friend Single<Input>;
public:
	// キー入力
	bool CheckKey(const okmonn::KeyCode& key);

	// トリガー入力
	bool Trigger(const okmonn::KeyCode& key);

private:
	// コンストラクタ
	Input();
	// デストラクタ
	~Input();

	
	// 現在の状態
	std::array<unsigned char, 256>now;

	// 過去の状態
	std::array<unsigned char, 256>old;
};
