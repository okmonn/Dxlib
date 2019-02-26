#pragma once
#include "KeyCode.h"
#include <optional>

// インプット
class Input
{
public:
	// デストラクタ
	~Input();

	// キー入力
	bool CheckKey(const KeyCode& key);

	// トリガー入力
	bool Trigger(const KeyCode& key);

	// インスタンス変数取得
	static Input& Get(void);

private:
	Input();
	Input(const Input&) = delete;
	void operator=(const Input&) = delete;


	// 前の入力キーコード
	std::optional<KeyCode>key;
};
