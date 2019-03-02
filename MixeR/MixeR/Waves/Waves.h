#pragma once
#include <vector>
#include <memory>

class MyLib;
class Sound;
class Primitive;

// 波形
class Waves
{
public:
	// コンストラクタ
	Waves(std::weak_ptr<MyLib>lib, std::weak_ptr<Sound>sound);
	// デストラクタ
	~Waves();

	// 処理
	void Run(void);

private:
	Waves(const Waves&) = delete;
	void operator=(const Waves&) = delete;


	// ライブラリ
	std::unique_ptr<MyLib>lib;

	// サウンド
	std::weak_ptr<Sound>sound;

	// プリミティブ
	std::unique_ptr<Primitive>prim;

	// フレーム
	unsigned char flam;
};
