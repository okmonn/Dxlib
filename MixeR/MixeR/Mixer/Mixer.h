#pragma once
#include <memory>

class MyLib;

// 心臓部分
class Mixer
{
public:
	// コンストラクタ
	Mixer();
	// デストラクタ
	~Mixer();

	// 処理
	void Run(void);

private:
	Mixer(const Mixer&) = delete;
	void operator=(const Mixer&) = delete;


	// ライブラリ
	std::shared_ptr<MyLib>lib;
};
